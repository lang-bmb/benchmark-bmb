// Sum of Squares Benchmark
// Measures: simple loop, integer arithmetic

fn main() {
    let mut sum: i64 = 0;
    for i in 1..100_000_000i64 {
        sum += i * i;
    }
    println!("{}", sum);
}
