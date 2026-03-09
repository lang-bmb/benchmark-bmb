// Counting sort benchmark — O(n+k) non-comparison sort
// Measures: sequential memory access, counting, prefix sum, scatter
// Workload: 500K elements, range 0-9999, 200 iterations

fn counting_sort(arr: &[i64], out: &mut [i64], k: usize) {
    let n = arr.len();
    let mut count = vec![0i64; k];
    // Count occurrences
    for i in 0..n {
        count[arr[i] as usize] += 1;
    }
    // Prefix sum
    for i in 1..k {
        count[i] += count[i - 1];
    }
    // Scatter (reverse for stability)
    for i in (0..n).rev() {
        let val = arr[i] as usize;
        count[val] -= 1;
        out[count[val] as usize] = val as i64;
    }
}

fn main() {
    let n: usize = 500_000;
    let k: usize = 10_000;
    let iters: i64 = 200;
    let mut arr = vec![0i64; n];
    let mut out = vec![0i64; n];

    let mut checksum: i64 = 0;
    for iter in 0..iters {
        let mut seed: i64 = 54321 + iter;
        for i in 0..n {
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            arr[i] = seed % k as i64;
        }
        counting_sort(&arr, &mut out, k);
        checksum += out[0] + out[n / 2] + out[n - 1];
    }

    println!("{}", checksum);
}
