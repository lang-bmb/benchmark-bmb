// Collatz Conjecture Benchmark
// Measures: branching, integer arithmetic

fn collatz_length(mut n: i64) -> i64 {
    let mut len: i64 = 0;
    while n != 1 {
        if n % 2 == 0 {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        len += 1;
    }
    len
}

fn main() {
    let mut max_len: i64 = 0;
    let mut max_n: i64 = 0;
    for n in 1..10_000_000i64 {
        let len = collatz_length(n);
        if len > max_len {
            max_len = len;
            max_n = n;
        }
    }
    println!("{} {}", max_n, max_len);
}
