// lex-bootstrap - BMB lexer throughput benchmark
// Measures: Token generation for BMB source code
// Uses actual BMB syntax patterns from bootstrap compiler

use std::time::Instant;

#[derive(Debug, Clone, Copy, PartialEq)]
enum TokenType {
    Eof,
    Ident,
    Number,
    String,
    Keyword,
    Operator,
    Punct,
    Comment,
    Arrow,     // ->
    FatArrow,  // =>
    Unknown,
}

struct Lexer<'a> {
    src: &'a [u8],
    pos: usize,
}

const KEYWORDS: &[&str] = &[
    "fn", "let", "if", "then", "else", "true", "false",
    "and", "or", "not", "pre", "post", "ret",
    "struct", "enum", "match", "new", "mut", "while",
    "for", "in", "return", "var", "type", "impl",
    "pub", "mod", "use", "as", "where", "trait",
];

fn is_keyword(s: &str) -> bool {
    KEYWORDS.contains(&s)
}

impl<'a> Lexer<'a> {
    fn new(src: &'a str) -> Self {
        Lexer {
            src: src.as_bytes(),
            pos: 0,
        }
    }

    fn peek(&self) -> u8 {
        if self.pos < self.src.len() {
            self.src[self.pos]
        } else {
            0
        }
    }

    fn peek_next(&self) -> u8 {
        if self.pos + 1 < self.src.len() {
            self.src[self.pos + 1]
        } else {
            0
        }
    }

    fn advance(&mut self) {
        if self.pos < self.src.len() {
            self.pos += 1;
        }
    }

    fn skip_whitespace(&mut self) {
        while self.pos < self.src.len() && self.peek().is_ascii_whitespace() {
            self.advance();
        }
    }

    fn next_token(&mut self) -> TokenType {
        self.skip_whitespace();

        if self.pos >= self.src.len() {
            return TokenType::Eof;
        }

        let c = self.peek();

        // BMB comments: --
        if c == b'-' && self.peek_next() == b'-' {
            while self.peek() != 0 && self.peek() != b'\n' {
                self.advance();
            }
            return TokenType::Comment;
        }

        // Arrow: ->
        if c == b'-' && self.peek_next() == b'>' {
            self.advance();
            self.advance();
            return TokenType::Arrow;
        }

        // Fat arrow: =>
        if c == b'=' && self.peek_next() == b'>' {
            self.advance();
            self.advance();
            return TokenType::FatArrow;
        }

        // Identifiers and keywords
        if c.is_ascii_alphabetic() || c == b'_' {
            let start = self.pos;
            while self.peek().is_ascii_alphanumeric() || self.peek() == b'_' {
                self.advance();
            }
            let ident = std::str::from_utf8(&self.src[start..self.pos]).unwrap_or("");
            return if is_keyword(ident) {
                TokenType::Keyword
            } else {
                TokenType::Ident
            };
        }

        // Numbers (including floats)
        if c.is_ascii_digit() {
            while self.peek().is_ascii_digit() {
                self.advance();
            }
            if self.peek() == b'.' && self.peek_next().is_ascii_digit() {
                self.advance();
                while self.peek().is_ascii_digit() {
                    self.advance();
                }
            }
            return TokenType::Number;
        }

        // Strings
        if c == b'"' {
            self.advance();
            while self.peek() != 0 && self.peek() != b'"' {
                if self.peek() == b'\\' {
                    self.advance();
                }
                self.advance();
            }
            if self.peek() == b'"' {
                self.advance();
            }
            return TokenType::String;
        }

        // Operators (2-char)
        if (c == b'=' || c == b'!' || c == b'<' || c == b'>' || c == b'&' || c == b'|' || c == b':')
            && (self.peek_next() == b'=' || self.peek_next() == b'&' || self.peek_next() == b'|' || self.peek_next() == b':')
        {
            self.advance();
            self.advance();
            return TokenType::Operator;
        }

        // Operators (1-char)
        if b"+-*/%=<>!&|:.".contains(&c) {
            self.advance();
            return TokenType::Operator;
        }

        // Punctuation
        if b"(){}[];,".contains(&c) {
            self.advance();
            return TokenType::Punct;
        }

        // Unknown
        self.advance();
        TokenType::Unknown
    }
}

const SAMPLE_SOURCE: &str = r#"-- BMB function definition
fn fibonacci(n: i64) -> i64
  pre n >= 0
  post ret >= 0
= if n <= 1 then n
  else fibonacci(n - 1) + fibonacci(n - 2);

-- Type definitions
struct Token {
    kind: i64,
    start: i64,
    end_pos: i64
}

enum Option<T> {
    Some(T),
    None
}

-- Pattern matching
fn process(opt: Option<i64>) -> i64 =
    match opt {
        Some(x) => x * 2,
        None => 0
    };

-- Let bindings
fn compute(a: i64, b: i64) -> i64 = {
    let x = a + b;
    let y = a - b;
    let z = x * y;
    z + 1
};
"#;

fn count_tokens(src: &str) -> usize {
    let mut lex = Lexer::new(src);
    let mut count = 0;
    loop {
        let tok = lex.next_token();
        if tok == TokenType::Eof {
            break;
        }
        count += 1;
    }
    count
}

fn main() {
    println!("Lex Bootstrap Benchmark");
    println!("Lexer for BMB source code\n");

    // Test small source
    let small_tokens = count_tokens(SAMPLE_SOURCE);
    println!("Sample source:");
    println!("  Length: {} bytes", SAMPLE_SOURCE.len());
    println!("  Tokens: {}\n", small_tokens);

    // Benchmark with larger source
    let large_source: String = SAMPLE_SOURCE.repeat(500);
    let large_len = large_source.len();

    let start = Instant::now();
    let large_tokens = count_tokens(&large_source);
    let elapsed = start.elapsed();

    let elapsed_secs = elapsed.as_secs_f64();
    let throughput = (large_len as f64 / 1024.0) / elapsed_secs;

    println!("Large source (500x):");
    println!("  Length: {} bytes ({:.1} KB)", large_len, large_len as f64 / 1024.0);
    println!("  Tokens: {}", large_tokens);
    println!("  Time: {:.3} seconds", elapsed_secs);
    println!("  Throughput: {:.1} KB/s", throughput);

    println!("\nDone.");
}
