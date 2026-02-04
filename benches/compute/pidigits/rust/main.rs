// Pi Digits Benchmark (simplified version)
// Measures: arbitrary precision arithmetic simulation

fn main() {
    // Simplified pi calculation using Machin's formula approximation
    // This version uses fixed-point arithmetic for fair comparison
    let iterations = 10_000_000;
    let mut sum: i64 = 0;

    // Leibniz formula simulation
    for i in 0..iterations {
        let sign = if i % 2 == 0 { 1i64 } else { -1i64 };
        let term = sign * 1000000 / (2 * i + 1);
        sum += term;
    }

    // Result should be approximately pi/4 * 1000000
    println!("{}", sum);
}
