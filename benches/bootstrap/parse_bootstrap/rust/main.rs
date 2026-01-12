// parse-bootstrap - BMB parser throughput benchmark
// Measures: AST construction from BMB source code
// Parses function definitions, expressions, statements

use std::time::Instant;

#[derive(Default)]
struct ParseStats {
    functions: usize,
    let_bindings: usize,
    if_exprs: usize,
    binary_ops: usize,
    calls: usize,
    idents: usize,
    numbers: usize,
    blocks: usize,
    structs: usize,
    enums: usize,
    matches: usize,
}

struct Parser<'a> {
    src: &'a [u8],
    pos: usize,
    stats: ParseStats,
}

impl<'a> Parser<'a> {
    fn new(src: &'a str) -> Self {
        Parser {
            src: src.as_bytes(),
            pos: 0,
            stats: ParseStats::default(),
        }
    }

    fn peek(&self) -> u8 {
        if self.pos < self.src.len() { self.src[self.pos] } else { 0 }
    }

    fn peek_n(&self, n: usize) -> u8 {
        if self.pos + n < self.src.len() { self.src[self.pos + n] } else { 0 }
    }

    fn advance(&mut self) {
        if self.pos < self.src.len() { self.pos += 1; }
    }

    fn is_ws(c: u8) -> bool { c == b' ' || c == b'\t' || c == b'\n' || c == b'\r' }
    fn is_alpha(c: u8) -> bool { c.is_ascii_alphabetic() }
    fn is_digit(c: u8) -> bool { c.is_ascii_digit() }
    fn is_alnum(c: u8) -> bool { c.is_ascii_alphanumeric() || c == b'_' }

    fn skip_ws(&mut self) {
        while self.pos < self.src.len() {
            if Self::is_ws(self.peek()) {
                self.advance();
            } else if self.peek() == b'-' && self.peek_n(1) == b'-' {
                while self.peek() != 0 && self.peek() != b'\n' { self.advance(); }
            } else {
                break;
            }
        }
    }

    fn match_keyword(&mut self, kw: &[u8]) -> bool {
        self.skip_ws();
        if self.pos + kw.len() > self.src.len() { return false; }
        if &self.src[self.pos..self.pos + kw.len()] != kw { return false; }
        if self.pos + kw.len() < self.src.len() && Self::is_alnum(self.src[self.pos + kw.len()]) {
            return false;
        }
        self.pos += kw.len();
        true
    }

    fn skip_to_char(&mut self, c: u8) {
        while self.peek() != 0 && self.peek() != c { self.advance(); }
        if self.peek() == c { self.advance(); }
    }

    fn skip_identifier(&mut self) {
        self.skip_ws();
        while Self::is_alnum(self.peek()) { self.advance(); }
    }

    fn skip_balanced(&mut self, open: u8, close: u8) {
        let mut depth = 1;
        self.advance();
        while self.pos < self.src.len() && depth > 0 {
            let c = self.peek();
            if c == open { depth += 1; }
            else if c == close { depth -= 1; }
            self.advance();
        }
    }

    fn parse_primary(&mut self) {
        self.skip_ws();
        let c = self.peek();

        if c == b'(' {
            self.advance();
            self.parse_expr();
            self.skip_ws();
            if self.peek() == b')' { self.advance(); }
        } else if c == b'{' {
            self.parse_block();
        } else if Self::is_digit(c) {
            while Self::is_digit(self.peek()) || self.peek() == b'.' { self.advance(); }
            self.stats.numbers += 1;
        } else if Self::is_alpha(c) || c == b'_' {
            self.skip_identifier();
            self.stats.idents += 1;
            self.skip_ws();
            if self.peek() == b'(' {
                self.stats.calls += 1;
                self.skip_balanced(b'(', b')');
            }
        }
    }

    fn parse_expr(&mut self) {
        self.skip_ws();

        if self.match_keyword(b"if") {
            self.stats.if_exprs += 1;
            self.parse_expr();
            self.skip_ws();
            if self.match_keyword(b"then") || self.peek() == b'{' {
                self.parse_expr();
            }
            self.skip_ws();
            if self.match_keyword(b"else") {
                self.parse_expr();
            }
            return;
        }

        if self.match_keyword(b"match") {
            self.stats.matches += 1;
            self.parse_expr();
            self.skip_ws();
            if self.peek() == b'{' {
                self.skip_balanced(b'{', b'}');
            }
            return;
        }

        self.parse_primary();

        self.skip_ws();
        while matches!(self.peek(), b'+' | b'-' | b'*' | b'/' | b'<' | b'>' | b'=' | b'&' | b'|') {
            self.stats.binary_ops += 1;
            self.advance();
            if matches!(self.peek(), b'=' | b'>' | b'&' | b'|') { self.advance(); }
            self.parse_primary();
            self.skip_ws();
        }
    }

    fn parse_block(&mut self) {
        self.skip_ws();
        if self.peek() != b'{' { return; }
        self.stats.blocks += 1;
        self.advance();

        while self.peek() != 0 && self.peek() != b'}' {
            self.skip_ws();
            if self.match_keyword(b"let") {
                self.stats.let_bindings += 1;
                self.skip_identifier();
                self.skip_ws();
                if self.peek() == b':' { self.skip_to_char(b'='); }
                if self.peek() == b'=' { self.advance(); }
                self.parse_expr();
                self.skip_ws();
                if self.peek() == b';' { self.advance(); }
            } else if self.peek() == b'}' {
                break;
            } else {
                self.parse_expr();
                self.skip_ws();
                if self.peek() == b';' { self.advance(); }
            }
        }
        if self.peek() == b'}' { self.advance(); }
    }

    fn parse_function(&mut self) {
        if !self.match_keyword(b"fn") { return; }
        self.stats.functions += 1;

        self.skip_identifier();
        self.skip_ws();

        if self.peek() == b'(' { self.skip_balanced(b'(', b')'); }

        self.skip_ws();
        if self.peek() == b'-' && self.peek_n(1) == b'>' {
            self.advance(); self.advance();
            self.skip_identifier();
            if self.peek() == b'<' { self.skip_balanced(b'<', b'>'); }
        }

        self.skip_ws();
        while self.match_keyword(b"pre") || self.match_keyword(b"post") {
            self.parse_expr();
            self.skip_ws();
        }

        self.skip_ws();
        if self.peek() == b'=' {
            self.advance();
            self.parse_expr();
        }

        self.skip_ws();
        if self.peek() == b';' { self.advance(); }
    }

    fn parse_struct(&mut self) {
        if !self.match_keyword(b"struct") { return; }
        self.stats.structs += 1;
        self.skip_identifier();
        self.skip_ws();
        if self.peek() == b'<' { self.skip_balanced(b'<', b'>'); }
        self.skip_ws();
        if self.peek() == b'{' { self.skip_balanced(b'{', b'}'); }
    }

    fn parse_enum(&mut self) {
        if !self.match_keyword(b"enum") { return; }
        self.stats.enums += 1;
        self.skip_identifier();
        self.skip_ws();
        if self.peek() == b'<' { self.skip_balanced(b'<', b'>'); }
        self.skip_ws();
        if self.peek() == b'{' { self.skip_balanced(b'{', b'}'); }
    }

    fn parse_program(&mut self) {
        while self.pos < self.src.len() {
            self.skip_ws();
            if self.pos >= self.src.len() { break; }

            let old_pos = self.pos;
            if self.peek() == b'f' && self.peek_n(1) == b'n' && !Self::is_alnum(self.peek_n(2)) {
                self.parse_function();
            } else if self.peek() == b's' && self.peek_n(1) == b't' && self.peek_n(2) == b'r' {
                self.parse_struct();
            } else if self.peek() == b'e' && self.peek_n(1) == b'n' && self.peek_n(2) == b'u' {
                self.parse_enum();
            }
            // Ensure we always make progress
            if self.pos == old_pos {
                self.advance();
            }
        }
    }
}

const SAMPLE_SOURCE: &str = r#"-- BMB function definitions
fn fibonacci(n: i64) -> i64
  pre n >= 0
  post ret >= 0
= if n <= 1 then n
  else fibonacci(n - 1) + fibonacci(n - 2);

struct Token {
    kind: i64,
    start: i64,
    end_pos: i64
}

enum Option<T> {
    Some(T),
    None
}

fn compute(a: i64, b: i64) -> i64 = {
    let x = a + b;
    let y = a - b;
    x * y
};

fn process(opt: Option<i64>) -> i64 =
    match opt {
        Some(x) => x * 2,
        None => 0
    };
"#;

fn main() {
    println!("Parse Bootstrap Benchmark");
    println!("Parser for BMB source code\n");

    // Test small source
    let mut p = Parser::new(SAMPLE_SOURCE);
    p.parse_program();

    println!("Sample source:");
    println!("  Length: {} bytes", SAMPLE_SOURCE.len());
    println!("  Functions: {}", p.stats.functions);
    println!("  Structs: {}", p.stats.structs);
    println!("  Enums: {}", p.stats.enums);
    println!("  Let bindings: {}", p.stats.let_bindings);
    println!("  If expressions: {}", p.stats.if_exprs);
    println!("  Match expressions: {}", p.stats.matches);
    println!();

    // Benchmark with larger source (100x for reasonable benchmark time)
    let large_source: String = SAMPLE_SOURCE.repeat(100);
    let large_len = large_source.len();

    let start = Instant::now();
    let mut p = Parser::new(&large_source);
    p.parse_program();
    let elapsed = start.elapsed();

    let elapsed_secs = elapsed.as_secs_f64();
    let throughput = (large_len as f64 / 1024.0) / elapsed_secs;

    println!("Large source (100x):");
    println!("  Length: {} bytes ({:.1} KB)", large_len, large_len as f64 / 1024.0);
    println!("  Functions: {}", p.stats.functions);
    println!("  Total nodes: {}",
             p.stats.functions + p.stats.structs + p.stats.enums +
             p.stats.let_bindings + p.stats.if_exprs + p.stats.matches);
    println!("  Time: {:.3} seconds", elapsed_secs);
    println!("  Throughput: {:.1} KB/s", throughput);

    println!("\nDone.");
}
