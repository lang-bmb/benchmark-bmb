// Prime Counting Benchmark
// Measures: nested loops, modulo operation

fn is_prime(n: i64) -> bool {
    if n < 2 {
        return false;
    }
    let mut d: i64 = 2;
    while d * d <= n {
        if n % d == 0 {
            return false;
        }
        d += 1;
    }
    true
}

fn count_primes(n: i64) -> i64 {
    let mut count: i64 = 0;
    let mut i: i64 = 2;
    while i <= n {
        if is_prime(i) {
            count += 1;
        }
        i += 1;
    }
    count
}

fn main() {
    let mut result: i64 = 0;
    for _ in 0..40 {
        result += count_primes(50000);
    }
    println!("{}", result);
}
