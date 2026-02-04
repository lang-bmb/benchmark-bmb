// Sieve of Eratosthenes Benchmark
// Measures: array access, branching

fn main() {
    let n: usize = 10_000_000;
    let mut sieve = vec![true; n + 1];
    sieve[0] = false;
    sieve[1] = false;

    let mut i: usize = 2;
    while i * i <= n {
        if sieve[i] {
            let mut j = i * i;
            while j <= n {
                sieve[j] = false;
                j += i;
            }
        }
        i += 1;
    }

    let mut count: i64 = 0;
    for i in 0..=n {
        if sieve[i] {
            count += 1;
        }
    }
    println!("{}", count);
}
