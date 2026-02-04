// CSV Parse Benchmark
// Measures: string splitting, field extraction

fn parse_csv_line(line: &[u8]) -> i64 {
    let mut count: i64 = 0;
    let mut in_field = false;
    let mut in_quote = false;

    for &c in line {
        if in_quote {
            if c == b'"' {
                in_quote = false;
            }
        } else {
            match c {
                b'"' => {
                    in_quote = true;
                    in_field = true;
                }
                b',' => {
                    if in_field {
                        count += 1;
                    }
                    in_field = false;
                }
                b'\n' | b'\r' => {
                    if in_field {
                        count += 1;
                    }
                    in_field = false;
                }
                _ => {
                    in_field = true;
                }
            }
        }
    }

    if in_field {
        count += 1;
    }
    count
}

fn main() {
    // Generate test CSV
    let mut csv = String::new();
    for i in 0..10_000 {
        csv.push_str(&format!(
            "{},\"name{}\",{}.{},{}\n",
            i,
            i,
            i * 10,
            i % 100,
            if i % 2 == 0 { "true" } else { "false" }
        ));
    }

    let input = csv.as_bytes();
    let mut total: i64 = 0;

    for _ in 0..100 {
        total += parse_csv_line(input);
    }

    println!("{}", total);
}
