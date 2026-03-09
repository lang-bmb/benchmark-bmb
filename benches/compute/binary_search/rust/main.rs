// Binary search benchmark — O(log n) search on sorted array
// Measures: branch prediction, cache access patterns, integer comparison
// Workload: 1M elements, 5M lookups per iteration, 20 iterations

fn binary_search(arr: &[i64], target: i64) -> i64 {
    let mut lo: i64 = 0;
    let mut hi: i64 = arr.len() as i64 - 1;
    while lo <= hi {
        let mid = lo + (hi - lo) / 2;
        if arr[mid as usize] == target {
            return mid;
        } else if arr[mid as usize] < target {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    -1
}

fn main() {
    let n: usize = 1_000_000;
    let lookups: i64 = 5_000_000;
    let iters: i64 = 20;

    // Fill sorted array: arr[i] = i * 3
    let arr: Vec<i64> = (0..n as i64).map(|i| i * 3).collect();

    let mut checksum: i64 = 0;
    for iter in 0..iters {
        let mut seed: i64 = 42 + iter;
        for _ in 0..lookups {
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            let target = (seed % n as i64) * 3;
            let idx = binary_search(&arr, target);
            checksum += idx;
        }
    }

    println!("{}", checksum);
}
