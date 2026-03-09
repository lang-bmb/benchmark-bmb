// Longest Common Subsequence benchmark — 2D dynamic programming
// Measures: 2D array access, max operations, string comparison
// Workload: 1000-char strings, 200 iterations

const SLEN: usize = 1000;
const ITERS: i64 = 200;

fn lcs(s: &[i64], slen: usize, t: &[i64], tlen: usize, dp: &mut [i64]) -> i64 {
    let cols = tlen + 1;
    for i in 0..=slen { dp[i * cols] = 0; }
    for j in 0..=tlen { dp[j] = 0; }
    for i in 1..=slen {
        for j in 1..=tlen {
            if s[i - 1] == t[j - 1] {
                dp[i * cols + j] = dp[(i - 1) * cols + (j - 1)] + 1;
            } else {
                let a = dp[(i - 1) * cols + j];
                let b = dp[i * cols + (j - 1)];
                dp[i * cols + j] = if a > b { a } else { b };
            }
        }
    }
    dp[slen * cols + tlen]
}

fn main() {
    let mut s = vec![0i64; SLEN];
    let mut t = vec![0i64; SLEN];
    let mut dp = vec![0i64; (SLEN + 1) * (SLEN + 1)];

    let mut checksum: i64 = 0;
    for iter in 0..ITERS {
        let mut seed: i64 = 65535 + iter;
        for i in 0..SLEN {
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            s[i] = seed % 26;
        }
        for i in 0..SLEN {
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            t[i] = seed % 26;
        }
        checksum += lcs(&s, SLEN, &t, SLEN, &mut dp);
    }
    println!("{}", checksum);
}
