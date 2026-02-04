// Tak Function Benchmark (Takeuchi)
// Measures: deep recursion, function call overhead

fn tak(x: i64, y: i64, z: i64) -> i64 {
    if y < x {
        tak(tak(x - 1, y, z), tak(y - 1, z, x), tak(z - 1, x, y))
    } else {
        z
    }
}

fn main() {
    let mut result: i64 = 0;
    for _ in 0..1000 {
        result += tak(18, 12, 6);
    }
    println!("{}", result);
}
