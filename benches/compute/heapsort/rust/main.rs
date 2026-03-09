// Heapsort benchmark — in-place heap sort
// Measures: heap operations, array swaps, cache-unfriendly access
// Workload: 500K elements, 100 iterations

const N: usize = 500000;
const ITERS: i64 = 100;

fn sift_down(arr: &mut [i64], n: usize, mut i: usize) {
    loop {
        let mut largest = i;
        let l = 2 * i + 1;
        let r = 2 * i + 2;
        if l < n && arr[l] > arr[largest] { largest = l; }
        if r < n && arr[r] > arr[largest] { largest = r; }
        if largest == i { break; }
        arr.swap(i, largest);
        i = largest;
    }
}

fn heapsort(arr: &mut [i64], n: usize) {
    let mut i = n / 2;
    while i > 0 {
        i -= 1;
        sift_down(arr, n, i);
    }
    let mut i = n - 1;
    while i > 0 {
        arr.swap(0, i);
        sift_down(arr, i, 0);
        i -= 1;
    }
}

fn main() {
    let mut arr = vec![0i64; N];

    let mut checksum: i64 = 0;
    for iter in 0..ITERS {
        let mut seed: i64 = 27182 + iter;
        for i in 0..N {
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            arr[i] = seed;
        }
        heapsort(&mut arr, N);
        checksum += arr[0] + arr[N / 2] + arr[N - 1];
    }
    println!("{}", checksum);
}
