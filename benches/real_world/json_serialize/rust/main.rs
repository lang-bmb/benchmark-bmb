// json-serialize - JSON serialization benchmark
// Tests string building, escaping, formatting
// Self-contained with embedded test structures

use std::fmt::Write;

/// Escape and write string to buffer
fn write_string(buf: &mut String, s: &str) {
    buf.push('"');
    for c in s.chars() {
        match c {
            '"' => buf.push_str("\\\""),
            '\\' => buf.push_str("\\\\"),
            '\n' => buf.push_str("\\n"),
            '\r' => buf.push_str("\\r"),
            '\t' => buf.push_str("\\t"),
            c if c >= ' ' && c <= '~' => buf.push(c),
            c => {
                let _ = write!(buf, "\\u{:04x}", c as u32);
            }
        }
    }
    buf.push('"');
}

/// Write integer
fn write_int(buf: &mut String, n: i64) {
    let _ = write!(buf, "{}", n);
}

/// Write float
fn write_float(buf: &mut String, d: f64) {
    let _ = write!(buf, "{:.6}", d);
}

/// Write bool
fn write_bool(buf: &mut String, b: bool) {
    buf.push_str(if b { "true" } else { "false" });
}

/// Serialize a simple object
fn serialize_person(buf: &mut String, name: &str, age: i64, city: &str, salary: f64) {
    buf.push('{');
    buf.push_str("\"name\":");
    write_string(buf, name);
    buf.push(',');
    buf.push_str("\"age\":");
    write_int(buf, age);
    buf.push(',');
    buf.push_str("\"city\":");
    write_string(buf, city);
    buf.push(',');
    buf.push_str("\"salary\":");
    write_float(buf, salary);
    buf.push('}');
}

/// Serialize array of integers
fn serialize_int_array(buf: &mut String, arr: &[i64]) {
    buf.push('[');
    for (i, &v) in arr.iter().enumerate() {
        if i > 0 {
            buf.push(',');
        }
        write_int(buf, v);
    }
    buf.push(']');
}

/// Benchmark: serialize many structures
fn run_benchmark(iterations: usize) -> usize {
    let mut total_len = 0;
    let mut buf = String::with_capacity(1024);

    for _ in 0..iterations {
        buf.clear();

        // Serialize person object
        serialize_person(&mut buf, "John Doe", 30, "New York", 50000.50);
        total_len += buf.len();

        buf.clear();

        // Serialize array
        let arr = [1i64, 2, 3, 4, 5, 6, 7, 8, 9, 10];
        serialize_int_array(&mut buf, &arr);
        total_len += buf.len();

        buf.clear();

        // Serialize with special characters
        serialize_person(&mut buf, "Alice \"The Great\"", 25, "Los\nAngeles", 60000.00);
        total_len += buf.len();
    }

    total_len
}

fn main() {
    println!("JSON Serialize Benchmark");

    // Warm up
    run_benchmark(100);

    // Benchmark
    let total = run_benchmark(10000);

    println!("Total characters: {}", total);
    println!("Sample output:");

    let mut buf = String::new();
    serialize_person(&mut buf, "Test User", 42, "Boston", 75000.00);
    println!("  Object: {}", buf);

    buf.clear();
    let arr = [1i64, 2, 3, 4, 5];
    serialize_int_array(&mut buf, &arr);
    println!("  Array: {}", buf);

    println!("Done.");
}
