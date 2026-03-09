// Levenshtein edit distance benchmark — 2D DP array access
// Measures: 2D array access patterns, min operations, loop performance
// Workload: 500-char strings, 200 iterations
// DP array pre-allocated once outside loop (measures pure computation)

fn levenshtein(s: &[i64], t: &[i64], dp: &mut [i64]) -> i64 {
    let slen = s.len();
    let tlen = t.len();
    let cols = tlen + 1;

    for i in 0..=slen {
        dp[i * cols] = i as i64;
    }
    for j in 0..=tlen {
        dp[j] = j as i64;
    }

    for i in 1..=slen {
        for j in 1..=tlen {
            let cost: i64 = if s[i - 1] == t[j - 1] { 0 } else { 1 };
            let del = dp[(i - 1) * cols + j] + 1;
            let ins = dp[i * cols + (j - 1)] + 1;
            let sub = dp[(i - 1) * cols + (j - 1)] + cost;
            let mut m = del;
            if ins < m { m = ins; }
            if sub < m { m = sub; }
            dp[i * cols + j] = m;
        }
    }
    dp[slen * cols + tlen]
}

fn main() {
    let len: usize = 500;
    let iters: i64 = 200;

    let mut s = vec![0i64; len];
    let mut t = vec![0i64; len];
    let mut dp = vec![0i64; (len + 1) * (len + 1)];

    let mut checksum: i64 = 0;
    for iter in 0..iters {
        let mut seed: i64 = 42 + iter;
        for i in 0..len {
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            s[i] = seed % 26;
        }
        for i in 0..len {
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            t[i] = seed % 26;
        }
        checksum += levenshtein(&s, &t, &mut dp);
    }

    println!("{}", checksum);
}
