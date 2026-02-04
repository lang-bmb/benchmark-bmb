// JSON Parse Benchmark
// Measures: string parsing, recursive descent, memory allocation

fn skip_whitespace(input: &[u8], pos: &mut usize) {
    while *pos < input.len() {
        let c = input[*pos];
        if c == b' ' || c == b'\t' || c == b'\n' || c == b'\r' {
            *pos += 1;
        } else {
            break;
        }
    }
}

fn parse_value(input: &[u8], pos: &mut usize) -> i64 {
    skip_whitespace(input, pos);
    if *pos >= input.len() {
        return 0;
    }

    let c = input[*pos];
    if c == b'{' {
        parse_object(input, pos)
    } else if c == b'[' {
        parse_array(input, pos)
    } else if c == b'"' {
        parse_string(input, pos)
    } else if c == b't' || c == b'f' {
        parse_bool(input, pos)
    } else if c == b'n' {
        parse_null(input, pos)
    } else if c == b'-' || (c >= b'0' && c <= b'9') {
        parse_number(input, pos)
    } else {
        0
    }
}

fn parse_object(input: &[u8], pos: &mut usize) -> i64 {
    *pos += 1; // skip '{'
    let mut count: i64 = 1;
    skip_whitespace(input, pos);

    if *pos < input.len() && input[*pos] == b'}' {
        *pos += 1;
        return count;
    }

    loop {
        skip_whitespace(input, pos);
        count += parse_string(input, pos);
        skip_whitespace(input, pos);
        if *pos < input.len() && input[*pos] == b':' {
            *pos += 1;
        }
        count += parse_value(input, pos);
        skip_whitespace(input, pos);

        if *pos >= input.len() {
            break;
        }
        if input[*pos] == b'}' {
            *pos += 1;
            break;
        }
        if input[*pos] == b',' {
            *pos += 1;
        }
    }
    count
}

fn parse_array(input: &[u8], pos: &mut usize) -> i64 {
    *pos += 1; // skip '['
    let mut count: i64 = 1;
    skip_whitespace(input, pos);

    if *pos < input.len() && input[*pos] == b']' {
        *pos += 1;
        return count;
    }

    loop {
        count += parse_value(input, pos);
        skip_whitespace(input, pos);

        if *pos >= input.len() {
            break;
        }
        if input[*pos] == b']' {
            *pos += 1;
            break;
        }
        if input[*pos] == b',' {
            *pos += 1;
        }
    }
    count
}

fn parse_string(input: &[u8], pos: &mut usize) -> i64 {
    if *pos >= input.len() || input[*pos] != b'"' {
        return 0;
    }
    *pos += 1;
    while *pos < input.len() && input[*pos] != b'"' {
        if input[*pos] == b'\\' {
            *pos += 1;
        }
        *pos += 1;
    }
    if *pos < input.len() {
        *pos += 1;
    }
    1
}

fn parse_number(input: &[u8], pos: &mut usize) -> i64 {
    if *pos < input.len() && input[*pos] == b'-' {
        *pos += 1;
    }
    while *pos < input.len() && input[*pos] >= b'0' && input[*pos] <= b'9' {
        *pos += 1;
    }
    if *pos < input.len() && input[*pos] == b'.' {
        *pos += 1;
        while *pos < input.len() && input[*pos] >= b'0' && input[*pos] <= b'9' {
            *pos += 1;
        }
    }
    1
}

fn parse_bool(input: &[u8], pos: &mut usize) -> i64 {
    if *pos + 4 <= input.len() && &input[*pos..*pos + 4] == b"true" {
        *pos += 4;
        return 1;
    }
    if *pos + 5 <= input.len() && &input[*pos..*pos + 5] == b"false" {
        *pos += 5;
        return 1;
    }
    0
}

fn parse_null(input: &[u8], pos: &mut usize) -> i64 {
    if *pos + 4 <= input.len() && &input[*pos..*pos + 4] == b"null" {
        *pos += 4;
        return 1;
    }
    0
}

fn main() {
    // Generate test JSON
    let mut json = String::from("{\"items\":[");
    for i in 0..1000 {
        if i > 0 {
            json.push(',');
        }
        json.push_str(&format!(
            "{{\"id\":{},\"name\":\"item{}\",\"value\":{}.{},\"active\":{}}}",
            i,
            i,
            i * 10,
            i % 100,
            if i % 2 == 0 { "true" } else { "false" }
        ));
    }
    json.push_str("]}");

    let input = json.as_bytes();
    let mut total: i64 = 0;

    for _ in 0..1000 {
        let mut pos: usize = 0;
        total += parse_value(input, &mut pos);
    }
    println!("{}", total);
}
