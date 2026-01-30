// Sieve of Eratosthenes - Prime number benchmark
// Measures: array operations, loop performance

fn sieve(n: usize) -> i64 {
    let mut arr = vec![true; n + 1];

    arr[0] = false;
    arr[1] = false;

    // Sieve
    let mut i = 2;
    while i * i <= n {
        if arr[i] {
            let mut j = i * i;
            while j <= n {
                arr[j] = false;
                j += i;
            }
        }
        i += 1;
    }

    // Count primes
    let mut count: i64 = 0;
    for i in 2..=n {
        if arr[i] {
            count += 1;
        }
    }

    count
}

fn main() {
    // 1500 iterations for stable measurement (target: ~140ms)
    let mut result: i64 = 0;
    for _ in 0..1500 {
        result += sieve(100000);
    }
    println!("{}", result);
}
