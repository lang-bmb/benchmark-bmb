// Binary Size Benchmark
// Measures: Executable size for equivalent functionality
//
// This benchmark is run differently than others:
// - We measure the size of the compiled executable
// - Contains the same functionality as other languages for fair comparison

fn abs_val(x: i64) -> i64 { if x < 0 { -x } else { x } }

fn gcd(a: i64, b: i64) -> i64 {
    if b == 0 { a } else { gcd(b, a % b) }
}

fn fibonacci(n: i64) -> i64 {
    if n <= 1 { n } else { fibonacci(n - 1) + fibonacci(n - 2) }
}

fn is_prime_check(n: i64, d: i64) -> bool {
    if d * d > n { return true; }
    if n % d == 0 { return false; }
    is_prime_check(n, d + 2)
}

fn is_prime(n: i64) -> bool {
    if n < 2 { return false; }
    if n == 2 { return true; }
    if n % 2 == 0 { return false; }
    is_prime_check(n, 3)
}

fn main() {
    let result = gcd(48, 18) + fibonacci(10) + if is_prime(17) { 1 } else { 0 };
    println!("{}", result);
}
