// Prime Counting Benchmark
// Measures: nested loops, modulo operation

fn is_prime(n: i64) -> bool {
    if n < 2 {
        return false;
    }
    if n == 2 {
        return true;
    }
    if n % 2 == 0 {
        return false;
    }
    let mut i: i64 = 3;
    while i * i <= n {
        if n % i == 0 {
            return false;
        }
        i += 2;
    }
    true
}

fn main() {
    let mut count: i64 = 0;
    for i in 2..1_000_000i64 {
        if is_prime(i) {
            count += 1;
        }
    }
    println!("{}", count);
}
