// Digital Root Benchmark
// Measures: integer arithmetic, nested loops

#[inline]
fn digit_sum(mut n: i64) -> i64 {
    let mut acc: i64 = 0;
    while n > 0 {
        let d = n % 10;
        let q = n / 10;
        acc += d;
        n = q;
    }
    acc
}

fn digital_root(mut n: i64) -> i64 {
    while n >= 10 {
        n = digit_sum(n);
    }
    n
}

fn main() {
    let mut sum: i64 = 0;
    for i in 1..10_000_000i64 {
        sum += digital_root(i * 12345);
    }
    println!("{}", sum);
}
