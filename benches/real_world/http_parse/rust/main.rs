// HTTP Parse Benchmark
// Measures: string parsing, header extraction

fn parse_request_line(input: &[u8], pos: &mut usize) -> i64 {
    let start = *pos;
    // Skip method
    while *pos < input.len() && input[*pos] != b' ' {
        *pos += 1;
    }
    if *pos < input.len() {
        *pos += 1;
    }
    // Skip path
    while *pos < input.len() && input[*pos] != b' ' {
        *pos += 1;
    }
    if *pos < input.len() {
        *pos += 1;
    }
    // Skip version until newline
    while *pos < input.len() && input[*pos] != b'\n' {
        *pos += 1;
    }
    if *pos < input.len() {
        *pos += 1;
    }
    (*pos - start) as i64
}

fn parse_header(input: &[u8], pos: &mut usize) -> i64 {
    if *pos >= input.len() || input[*pos] == b'\n' || input[*pos] == b'\r' {
        return 0;
    }

    let start = *pos;
    // Skip header name
    while *pos < input.len() && input[*pos] != b':' && input[*pos] != b'\n' {
        *pos += 1;
    }
    if *pos < input.len() && input[*pos] == b':' {
        *pos += 1;
        // Skip whitespace
        while *pos < input.len() && (input[*pos] == b' ' || input[*pos] == b'\t') {
            *pos += 1;
        }
        // Skip value
        while *pos < input.len() && input[*pos] != b'\n' {
            *pos += 1;
        }
    }
    if *pos < input.len() {
        *pos += 1;
    }
    (*pos - start) as i64
}

fn parse_request(input: &[u8]) -> i64 {
    let mut pos: usize = 0;
    let mut count: i64 = 0;

    count += parse_request_line(input, &mut pos);

    loop {
        if pos >= input.len() {
            break;
        }
        if input[pos] == b'\n' || (input[pos] == b'\r' && pos + 1 < input.len() && input[pos + 1] == b'\n') {
            break;
        }
        let header_len = parse_header(input, &mut pos);
        if header_len == 0 {
            break;
        }
        count += 1;
    }

    count
}

fn main() {
    // Generate test HTTP requests
    let mut requests = String::new();
    for i in 0..1000 {
        requests.push_str(&format!(
            "GET /path/to/resource/{} HTTP/1.1\r\nHost: example.com\r\nUser-Agent: Benchmark/1.0\r\nAccept: */*\r\nX-Request-Id: {}\r\nContent-Length: 0\r\n\r\n",
            i, i
        ));
    }

    let input = requests.as_bytes();
    let mut total: i64 = 0;

    for _ in 0..100 {
        let mut pos: usize = 0;
        while pos < input.len() {
            let start = pos;
            total += parse_request(&input[pos..]);
            // Move to next request
            while pos < input.len() && !(input[pos] == b'\r' && pos + 3 < input.len() && input[pos + 1] == b'\n' && input[pos + 2] == b'\r' && input[pos + 3] == b'\n') {
                pos += 1;
            }
            if pos < input.len() {
                pos += 4;
            }
            if pos == start {
                break;
            }
        }
    }

    println!("{}", total);
}
