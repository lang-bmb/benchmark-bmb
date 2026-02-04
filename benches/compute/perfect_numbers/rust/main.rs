// Perfect Numbers Benchmark
// Measures: nested loops, divisor calculation

fn sum_of_divisors(n: i64) -> i64 {
    let mut sum: i64 = 1;
    let mut i: i64 = 2;
    while i * i <= n {
        if n % i == 0 {
            sum += i;
            if i != n / i {
                sum += n / i;
            }
        }
        i += 1;
    }
    sum
}

fn main() {
    let mut count: i64 = 0;
    for n in 2..50_000_000i64 {
        if sum_of_divisors(n) == n {
            count += 1;
        }
    }
    println!("{}", count);
}
