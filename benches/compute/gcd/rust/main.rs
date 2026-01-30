// GCD (Greatest Common Divisor) Benchmark
// Measures: loops, modulo operations, integer arithmetic

fn gcd(mut a: i64, mut b: i64) -> i64 {
    while b != 0 {
        let t = b;
        b = a % b;
        a = t;
    }
    a
}

fn sum_gcds(n: i64) -> i64 {
    let mut acc: i64 = 0;
    for i in 1..=n {
        for j in 1..=n {
            acc += gcd(i, j);
        }
    }
    acc
}

fn main() {
    // 100 iterations for stable measurement (target: ~130ms)
    let mut result: i64 = 0;
    for _ in 0..100 {
        result += sum_gcds(300);
    }
    println!("{}", result);
}
