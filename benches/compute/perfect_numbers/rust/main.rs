// Perfect Numbers Benchmark
// Measures: divisor finding, accumulation, nested loops

fn sum_divisors(n: i64) -> i64 {
    let mut acc: i64 = 0;
    let mut d: i64 = 1;
    while d < n {
        if n % d == 0 {
            acc += d;
        }
        d += 1;
    }
    acc
}

fn is_perfect(n: i64) -> bool {
    if n <= 1 {
        return false;
    }
    sum_divisors(n) == n
}

fn count_perfect(n: i64) -> i64 {
    let mut count: i64 = 0;
    let mut i: i64 = 2;
    while i <= n {
        if is_perfect(i) {
            count += 1;
        }
        i += 1;
    }
    count
}

fn main() {
    let mut result: i64 = 0;
    for _ in 0..10 {
        result += count_perfect(10000);
    }
    println!("{}", result);
}
