// Fibonacci - iterative O(n) algorithm
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
    let mut result: i64 = 0;
    for _ in 0..1_000_000_000i64 {
        result += fibonacci_iter(50);
    }
    println!("{}", result);
}
