// Quicksort benchmark — Lomuto partition, in-place
// Measures: array read/write in hot loop, recursion, branch prediction
// Workload: N=10000 array, 200 iterations, LCG PRNG

fn partition(arr: &mut [i64], lo: usize, hi: usize) -> usize {
    let pivot = arr[hi];
    let mut i = lo;
    for j in lo..hi {
        if arr[j] <= pivot {
            arr.swap(i, j);
            i += 1;
        }
    }
    arr.swap(i, hi);
    i
}

fn quicksort(arr: &mut [i64], lo: usize, hi: usize) {
    if lo < hi {
        let p = partition(arr, lo, hi);
        if p > lo {
            quicksort(arr, lo, p - 1);
        }
        quicksort(arr, p + 1, hi);
    }
}

fn main() {
    let n: usize = 10000;
    let iters: i64 = 200;
    let mut arr = vec![0i64; n];

    let mut checksum: i64 = 0;
    for iter in 0..iters {
        // Fill with LCG pseudo-random (same seed each iteration)
        let mut seed: i64 = 12345 + iter;
        for i in 0..n {
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            arr[i] = seed % (n as i64);
        }
        quicksort(&mut arr, 0, n - 1);
        // Checksum: sum first 10 elements
        for i in 0..10 {
            checksum += arr[i];
        }
    }

    println!("{}", checksum);
}
