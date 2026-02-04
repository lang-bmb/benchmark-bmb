// Sieve of Eratosthenes Benchmark
// Measures: array access, branching
// Matches BMB/C: sieve(100000) x 1500 iterations

fn sieve(n: usize) -> i64 {
    let mut arr = vec![1u8; n + 1];
    arr[0] = 0;
    arr[1] = 0;

    let mut i = 2;
    while i * i <= n {
        if arr[i] == 1 {
            let mut j = i * i;
            while j <= n {
                arr[j] = 0;
                j += i;
            }
        }
        i += 1;
    }

    let mut count: i64 = 0;
    for i in 2..=n {
        if arr[i] == 1 {
            count += 1;
        }
    }
    count
}

fn main() {
    // 1500 iterations to match BMB/C
    let mut result: i64 = 0;
    for _ in 0..1500 {
        result += sieve(100000);
    }
    println!("{}", result);
}
