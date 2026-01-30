// Takeuchi Function (TAK) Benchmark
// Measures: recursion, function call overhead

fn tak(x: i64, y: i64, z: i64) -> i64 {
    if y >= x {
        z
    } else {
        tak(
            tak(x - 1, y, z),
            tak(y - 1, z, x),
            tak(z - 1, x, y),
        )
    }
}

fn main() {
    // 50000 iterations for stable measurement (target: ~150ms after LICM)
    let mut result: i64 = 0;
    for _ in 0..50000 {
        result += tak(24, 16, 8);
    }
    println!("{}", result);
}
