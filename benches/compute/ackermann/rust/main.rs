// Ackermann Function Benchmark
// Measures: deep recursion, function call overhead

fn ackermann(m: i64, n: i64) -> i64 {
    if m == 0 {
        n + 1
    } else if n == 0 {
        ackermann(m - 1, 1)
    } else {
        ackermann(m - 1, ackermann(m, n - 1))
    }
}

fn main() {
    let mut result: i64 = 0;
    for _ in 0..1000 {
        result += ackermann(3, 10);
    }
    println!("{}", result);
}
