// Lexer Benchmark
// Measures: character classification, state machine, string processing

#[derive(Debug, Clone, Copy, PartialEq)]
enum TokenType {
    Ident,
    Number,
    Op,
    Paren,
    Eof,
}

fn is_alpha(c: u8) -> bool {
    (c >= b'a' && c <= b'z') || (c >= b'A' && c <= b'Z') || c == b'_'
}

fn is_digit(c: u8) -> bool {
    c >= b'0' && c <= b'9'
}

fn is_whitespace(c: u8) -> bool {
    c == b' ' || c == b'\t' || c == b'\n' || c == b'\r'
}

fn tokenize(input: &[u8]) -> i64 {
    let mut count: i64 = 0;
    let mut pos = 0;
    let len = input.len();

    while pos < len {
        let c = input[pos];

        if is_whitespace(c) {
            pos += 1;
            continue;
        }

        if is_alpha(c) {
            while pos < len && (is_alpha(input[pos]) || is_digit(input[pos])) {
                pos += 1;
            }
            count += 1;
            continue;
        }

        if is_digit(c) {
            while pos < len && is_digit(input[pos]) {
                pos += 1;
            }
            count += 1;
            continue;
        }

        if c == b'+' || c == b'-' || c == b'*' || c == b'/' || c == b'=' {
            pos += 1;
            count += 1;
            continue;
        }

        if c == b'(' || c == b')' || c == b'{' || c == b'}' || c == b'[' || c == b']' {
            pos += 1;
            count += 1;
            continue;
        }

        pos += 1;
    }

    count
}

fn main() {
    // Generate test input
    let mut input = Vec::with_capacity(100_000);
    for i in 0..10_000 {
        let code = format!("fn test{} = x + {} * (y - 123);\n", i, i % 100);
        input.extend_from_slice(code.as_bytes());
    }

    // Run multiple times
    let mut total: i64 = 0;
    for _ in 0..100 {
        total += tokenize(&input);
    }
    println!("{}", total);
}
