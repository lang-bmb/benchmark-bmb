// Merge sort benchmark — divide-and-conquer + array merging
// Measures: recursive splitting, sequential merge, memory copy patterns
// Workload: 500K elements, 100 iterations

const N: usize = 500000;
const ITERS: i64 = 100;

fn merge(arr: &mut [i64], tmp: &mut [i64], lo: usize, mid: usize, hi: usize) {
    for i in lo..=hi { tmp[i] = arr[i]; }
    let mut i = lo;
    let mut j = mid + 1;
    let mut k = lo;
    while i <= mid && j <= hi {
        if tmp[i] <= tmp[j] { arr[k] = tmp[i]; i += 1; }
        else { arr[k] = tmp[j]; j += 1; }
        k += 1;
    }
    while i <= mid { arr[k] = tmp[i]; i += 1; k += 1; }
    while j <= hi { arr[k] = tmp[j]; j += 1; k += 1; }
}

fn mergesort(arr: &mut [i64], tmp: &mut [i64], lo: usize, hi: usize) {
    if lo >= hi { return; }
    let mid = lo + (hi - lo) / 2;
    mergesort(arr, tmp, lo, mid);
    mergesort(arr, tmp, mid + 1, hi);
    merge(arr, tmp, lo, mid, hi);
}

fn main() {
    let mut arr = vec![0i64; N];
    let mut tmp = vec![0i64; N];

    let mut checksum: i64 = 0;
    for iter in 0..ITERS {
        let mut seed: i64 = 31415 + iter;
        for i in 0..N {
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            arr[i] = seed;
        }
        mergesort(&mut arr, &mut tmp, 0, N - 1);
        checksum += arr[0] + arr[N / 2] + arr[N - 1];
    }
    println!("{}", checksum);
}
