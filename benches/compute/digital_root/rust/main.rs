// Digital Root Benchmark
// Measures: modulo operations, division, loops

fn digit_sum(mut n: i64) -> i64 {
    let mut acc: i64 = 0;
    while n > 0 {
        acc += n % 10;
        n /= 10;
    }
    acc
}

fn digital_root(mut n: i64) -> i64 {
    while n >= 10 {
        n = digit_sum(n);
    }
    n
}

fn sum_digital_roots(n: i64) -> i64 {
    let mut acc: i64 = 0;
    for i in 1..=n {
        acc += digital_root(i);
    }
    acc
}

fn main() {
    let mut result: i64 = 0;
    for _ in 0..50 {
        result += sum_digital_roots(100000);
    }
    println!("{}", result);
}
