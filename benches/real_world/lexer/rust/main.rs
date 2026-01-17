// lexer - Token generation benchmark
// Tests character processing, state machine, keyword matching
// Self-contained with embedded source code

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
    Unknown,
}

struct Lexer<'a> {
    src: &'a [u8],
    pos: usize,
}

const KEYWORDS: &[&str] = &[
    "fn", "let", "if", "else", "while", "for", "return",
    "true", "false", "null", "struct", "enum", "match",
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

        // Comments
        if c == b'-' && self.peek_next() == b'-' {
            while self.peek() != 0 && self.peek() != b'\n' {
                self.advance();
            }
            return TokenType::Comment;
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

        // Numbers
        if c.is_ascii_digit() {
            while self.peek().is_ascii_digit() || self.peek() == b'.' {
                self.advance();
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
        if (c == b'=' || c == b'!' || c == b'<' || c == b'>' || c == b'&' || c == b'|')
            && (self.peek_next() == b'=' || self.peek_next() == b'&' || self.peek_next() == b'|')
        {
            self.advance();
            self.advance();
            return TokenType::Operator;
        }

        // Operators (1-char)
        if b"+-*/%=<>!&|".contains(&c) {
            self.advance();
            return TokenType::Operator;
        }

        // Punctuation
        if b"(){}[];:,.".contains(&c) {
            self.advance();
            return TokenType::Punct;
        }

        // Unknown
        self.advance();
        TokenType::Unknown
    }
}

const TEST_SOURCE: &str = r#"fn fibonacci(n: i64) -> i64 =
    if n <= 1 { n }
    else { fibonacci(n - 1) + fibonacci(n - 2) };

fn main() -> i64 = {
    let result = fibonacci(35);
    -- This is a comment
    let x = 42;
    let y = 3.14159;
    let s = "Hello, World!";
    if x > 10 && y < 100.0 {
        return result;
    } else {
        return 0;
    }
};
"#;

fn count_tokens(src: &str) -> [usize; 9] {
    let mut counts = [0usize; 9];
    let mut lex = Lexer::new(src);

    loop {
        let tok = lex.next_token();
        if tok == TokenType::Eof {
            break;
        }
        counts[tok as usize] += 1;
    }

    counts
}

fn main() {
    println!("Lexer Benchmark");

    // Test small source
    let counts = count_tokens(TEST_SOURCE);

    println!("Small source:");
    println!("  Identifiers: {}", counts[TokenType::Ident as usize]);
    println!("  Numbers: {}", counts[TokenType::Number as usize]);
    println!("  Keywords: {}", counts[TokenType::Keyword as usize]);
    println!("  Strings: {}", counts[TokenType::String as usize]);
    println!("  Operators: {}", counts[TokenType::Operator as usize]);
    println!("  Punctuation: {}", counts[TokenType::Punct as usize]);
    println!("  Comments: {}", counts[TokenType::Comment as usize]);
    println!();

    // Benchmark with larger source
    let large_source: String = TEST_SOURCE.repeat(100);
    let counts = count_tokens(&large_source);

    let total: usize = counts[1..8].iter().sum();
    println!("Large source (100x):");
    println!("  Total tokens: {}", total);

    println!("\nDone.");
}
