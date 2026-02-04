// Sum of Squares Benchmark
// Measures: arithmetic operations, loop performance
// Matches BMB/C: sum_squares(100000) x 1000 iterations

fn sum_squares(n: i64) -> i64 {
    let mut acc: i64 = 0;
    for i in 1..=n {
        acc += i * i;
    }
    acc
}

fn main() {
    // Sum squares from 1 to 100000, 1000 iterations
    let mut result: i64 = 0;
    for _ in 0..1000 {
        result += sum_squares(100000);
    }
    println!("{}", result);
}
