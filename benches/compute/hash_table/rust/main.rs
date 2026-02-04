// Hash Table Benchmark
// Measures: hash function, array access, collision handling

use std::collections::HashMap;

fn main() {
    let n = 1_000_000;
    let mut map: HashMap<i64, i64> = HashMap::with_capacity(n);

    // Insert
    for i in 0..n as i64 {
        map.insert(i * 7 + 13, i);
    }

    // Lookup
    let mut sum: i64 = 0;
    for i in 0..n as i64 {
        if let Some(&v) = map.get(&(i * 7 + 13)) {
            sum += v;
        }
    }

    // Delete half
    for i in 0..(n / 2) as i64 {
        map.remove(&(i * 7 + 13));
    }

    // Final size + sum
    println!("{} {}", map.len(), sum);
}
