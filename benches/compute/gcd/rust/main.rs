// GCD Benchmark - Euclidean algorithm
// Measures: integer division, recursion/iteration

fn gcd(mut a: i64, mut b: i64) -> i64 {
    while b != 0 {
        let t = b;
        b = a % b;
        a = t;
    }
    a
}

fn main() {
    let mut sum: i64 = 0;
    for i in 1..50_000_000i64 {
        sum += gcd(i, i + 7);
    }
    println!("{}", sum);
}
