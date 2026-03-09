// 0/1 Knapsack benchmark — 1D DP array access
// Measures: 1D array access, conditional updates, loop performance
// Workload: 2000 items, capacity 5000, 50 iterations

fn knapsack(n: usize, capacity: usize, weights: &[i64], values: &[i64], dp: &mut [i64]) -> i64 {
    for j in 0..=capacity {
        dp[j] = 0;
    }
    for i in 0..n {
        let wi = weights[i] as usize;
        let vi = values[i];
        let mut j = capacity;
        while j >= wi {
            let take = dp[j - wi] + vi;
            if take > dp[j] {
                dp[j] = take;
            }
            j -= 1;
        }
    }
    dp[capacity]
}

fn main() {
    let n: usize = 2000;
    let cap: usize = 5000;
    let iters: i64 = 50;

    let mut weights = vec![0i64; n];
    let mut values = vec![0i64; n];
    let mut dp = vec![0i64; cap + 1];

    let mut checksum: i64 = 0;
    for iter in 0..iters {
        let mut seed: i64 = 777 + iter;
        for i in 0..n {
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            weights[i] = (seed % 50) + 1;
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            values[i] = (seed % 100) + 1;
        }
        checksum += knapsack(n, cap, &weights, &values, &mut dp);
    }

    println!("{}", checksum);
}
