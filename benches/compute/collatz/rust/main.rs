// Collatz Conjecture Benchmark
// Measures: branching, integer operations, loop performance

fn collatz_length(mut n: i64) -> i64 {
    let mut steps: i64 = 0;
    while n > 1 {
        if n % 2 == 0 {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        steps += 1;
    }
    steps
}

fn sum_collatz_lengths(start: i64, end: i64) -> i64 {
    let mut acc: i64 = 0;
    for i in start..=end {
        acc += collatz_length(i);
    }
    acc
}

fn main() {
    let mut result: i64 = 0;
    for _ in 0..10 {
        result += sum_collatz_lengths(1, 10000);
    }
    println!("{}", result);
}
