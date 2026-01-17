// http-parse - HTTP request parsing benchmark
// Tests protocol parsing, header extraction, string matching
// Self-contained with embedded test requests

#[derive(Debug, Clone, Copy, PartialEq)]
enum HttpMethod {
    Get,
    Post,
    Put,
    Delete,
    Head,
    Options,
    Unknown,
}

#[derive(Debug)]
struct HttpRequest {
    method: HttpMethod,
    path_start: usize,
    path_len: usize,
    version_major: u8,
    version_minor: u8,
    header_count: usize,
    content_length: usize,
    host_start: usize,
    host_len: usize,
}

impl Default for HttpRequest {
    fn default() -> Self {
        HttpRequest {
            method: HttpMethod::Unknown,
            path_start: 0,
            path_len: 0,
            version_major: 1,
            version_minor: 1,
            header_count: 0,
            content_length: 0,
            host_start: 0,
            host_len: 0,
        }
    }
}

fn skip_ws(s: &[u8], mut pos: usize) -> usize {
    while pos < s.len() && (s[pos] == b' ' || s[pos] == b'\t') {
        pos += 1;
    }
    pos
}

fn find_char(s: &[u8], mut pos: usize, c: u8) -> usize {
    while pos < s.len() && s[pos] != c {
        pos += 1;
    }
    pos
}

fn find_eol(s: &[u8], mut pos: usize) -> usize {
    while pos < s.len() {
        if s[pos] == b'\n' {
            return pos;
        }
        if s[pos] == b'\r' && pos + 1 < s.len() && s[pos + 1] == b'\n' {
            return pos;
        }
        pos += 1;
    }
    pos
}

fn skip_eol(s: &[u8], mut pos: usize) -> usize {
    if pos < s.len() && s[pos] == b'\r' {
        pos += 1;
    }
    if pos < s.len() && s[pos] == b'\n' {
        pos += 1;
    }
    pos
}

fn str_eq_ignore_case(s: &[u8], pos: usize, m: &[u8]) -> bool {
    if pos + m.len() > s.len() {
        return false;
    }
    for i in 0..m.len() {
        let c1 = s[pos + i].to_ascii_lowercase();
        let c2 = m[i].to_ascii_lowercase();
        if c1 != c2 {
            return false;
        }
    }
    true
}

fn parse_method(s: &[u8], pos: usize) -> HttpMethod {
    if str_eq_ignore_case(s, pos, b"GET") {
        HttpMethod::Get
    } else if str_eq_ignore_case(s, pos, b"POST") {
        HttpMethod::Post
    } else if str_eq_ignore_case(s, pos, b"PUT") {
        HttpMethod::Put
    } else if str_eq_ignore_case(s, pos, b"DELETE") {
        HttpMethod::Delete
    } else if str_eq_ignore_case(s, pos, b"HEAD") {
        HttpMethod::Head
    } else if str_eq_ignore_case(s, pos, b"OPTIONS") {
        HttpMethod::Options
    } else {
        HttpMethod::Unknown
    }
}

fn parse_int(s: &[u8], mut pos: usize, end: usize) -> usize {
    let mut result = 0usize;
    while pos < end && s[pos] >= b'0' && s[pos] <= b'9' {
        result = result * 10 + (s[pos] - b'0') as usize;
        pos += 1;
    }
    result
}

fn parse_request(s: &[u8]) -> HttpRequest {
    let mut req = HttpRequest::default();
    let len = s.len();
    let mut pos = 0;

    // Parse request line: METHOD PATH HTTP/X.Y
    req.method = parse_method(s, pos);

    // Skip to first space (after method)
    pos = find_char(s, pos, b' ');
    pos = skip_ws(s, pos);

    // Parse path
    req.path_start = pos;
    pos = find_char(s, pos, b' ');
    req.path_len = pos - req.path_start;

    pos = skip_ws(s, pos);

    // Parse HTTP version
    if pos + 8 <= len && &s[pos..pos + 5] == b"HTTP/" {
        req.version_major = s[pos + 5] - b'0';
        if pos + 8 <= len && s[pos + 6] == b'.' {
            req.version_minor = s[pos + 7] - b'0';
        }
    }

    // Skip to end of request line
    pos = find_eol(s, pos);
    pos = skip_eol(s, pos);

    // Parse headers
    while pos < len {
        let line_start = pos;
        let eol = find_eol(s, pos);

        // Empty line = end of headers
        if eol == line_start {
            break;
        }

        req.header_count += 1;

        // Find colon
        let colon = find_char(s, pos, b':');
        if colon < eol {
            let name_len = colon - pos;

            // Check for specific headers
            if name_len == 4 && str_eq_ignore_case(s, pos, b"host") {
                let val_start = skip_ws(s, colon + 1);
                req.host_start = val_start;
                req.host_len = eol - val_start;
            } else if name_len == 14 && str_eq_ignore_case(s, pos, b"content-length") {
                let val_start = skip_ws(s, colon + 1);
                req.content_length = parse_int(s, val_start, eol);
            }
        }

        pos = skip_eol(s, eol);
    }

    req
}

const TEST_REQUESTS: &[&str] = &[
    "GET /index.html HTTP/1.1\r\n\
     Host: example.com\r\n\
     User-Agent: Mozilla/5.0\r\n\
     Accept: text/html\r\n\
     Connection: keep-alive\r\n\
     \r\n",
    "POST /api/users HTTP/1.1\r\n\
     Host: api.example.com\r\n\
     Content-Type: application/json\r\n\
     Content-Length: 42\r\n\
     Authorization: Bearer token123\r\n\
     \r\n",
    "PUT /api/resource/123 HTTP/1.1\r\n\
     Host: api.example.com\r\n\
     Content-Type: application/json\r\n\
     Content-Length: 256\r\n\
     \r\n",
    "DELETE /api/users/456 HTTP/1.1\r\n\
     Host: api.example.com\r\n\
     Authorization: Bearer token456\r\n\
     \r\n",
    "GET /static/style.css HTTP/1.1\r\n\
     Host: cdn.example.com\r\n\
     Accept: text/css\r\n\
     Cache-Control: max-age=3600\r\n\
     \r\n",
];

fn run_benchmark(iterations: usize) -> (usize, usize) {
    let mut total_headers = 0;
    let mut total_content_len = 0;

    for _ in 0..iterations {
        for req_str in TEST_REQUESTS {
            let req = parse_request(req_str.as_bytes());
            total_headers += req.header_count;
            total_content_len += req.content_length;
        }
    }

    (total_headers, total_content_len)
}

fn method_name(m: HttpMethod) -> &'static str {
    match m {
        HttpMethod::Get => "GET",
        HttpMethod::Post => "POST",
        HttpMethod::Put => "PUT",
        HttpMethod::Delete => "DELETE",
        HttpMethod::Head => "HEAD",
        HttpMethod::Options => "OPTIONS",
        HttpMethod::Unknown => "UNKNOWN",
    }
}

fn main() {
    println!("HTTP Parse Benchmark\n");

    // Parse sample request
    let req = parse_request(TEST_REQUESTS[0].as_bytes());

    println!("Sample request:");
    println!("  Method: {}", method_name(req.method));
    println!("  Path length: {}", req.path_len);
    println!(
        "  Version: HTTP/{}.{}",
        req.version_major, req.version_minor
    );
    println!("  Headers: {}", req.header_count);
    println!();

    // Benchmark
    let (total_headers, total_content_len) = run_benchmark(10000);

    println!("Benchmark (10000 iterations x 5 requests):");
    println!("  Total headers parsed: {}", total_headers);
    println!("  Total content-length: {}", total_content_len);

    println!("\nDone.");
}
