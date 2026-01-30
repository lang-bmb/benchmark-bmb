// Fibonacci - FAIR COMPARISON benchmark
// Uses iterative O(n) algorithm matching the C/BMB versions exactly.
// Measures: loop iteration, integer arithmetic, accumulator pattern

fn fibonacci_iter(n: i64) -> i64 {
    let mut a: i64 = 0;
    let mut b: i64 = 1;
    for _ in 0..n {
        let temp = a + b;
        a = b;
        b = temp;
    }
    a
}

fn main() {
    // Run fibonacci(50) 1000000000 times for stable measurement (target: ~120ms after LICM)
    let mut result: i64 = 0;
    for _ in 0..1000000000 {
        result += fibonacci_iter(50);
    }
    println!("{}", result);
}
