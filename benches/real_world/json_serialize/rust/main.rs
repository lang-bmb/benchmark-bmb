// JSON Serialize Benchmark
// Measures: string building, number formatting

fn main() {
    let mut total_len: i64 = 0;

    for _ in 0..1000 {
        let mut output = String::with_capacity(100_000);
        output.push_str("{\"items\":[");

        for i in 0..1000 {
            if i > 0 {
                output.push(',');
            }
            output.push_str("{\"id\":");
            output.push_str(&i.to_string());
            output.push_str(",\"name\":\"item");
            output.push_str(&i.to_string());
            output.push_str("\",\"value\":");
            output.push_str(&(i * 10).to_string());
            output.push('.');
            output.push_str(&(i % 100).to_string());
            output.push_str(",\"active\":");
            output.push_str(if i % 2 == 0 { "true" } else { "false" });
            output.push('}');
        }

        output.push_str("]}");
        total_len += output.len() as i64;
    }

    println!("{}", total_len);
}
