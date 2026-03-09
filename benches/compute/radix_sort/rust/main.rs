// Radix sort benchmark — counting sort + bit extraction
// Measures: array traversal, counting, memory write patterns
// Workload: 500K elements, 8-byte keys, 200 iterations

const N: usize = 500000;
const RADIX: usize = 256;
const ITERS: i64 = 200;

fn radix_sort(arr: &mut [i64], tmp: &mut [i64], n: usize) {
    let mut count = [0i64; RADIX];
    for pass in 0..4u32 {
        let shift = pass * 8;
        for i in 0..RADIX { count[i] = 0; }
        for i in 0..n {
            let byte_val = ((arr[i] >> shift) & 0xFF) as usize;
            count[byte_val] += 1;
        }
        for i in 1..RADIX { count[i] += count[i - 1]; }
        for i in (0..n).rev() {
            let byte_val = ((arr[i] >> shift) & 0xFF) as usize;
            count[byte_val] -= 1;
            tmp[count[byte_val] as usize] = arr[i];
        }
        for i in 0..n { arr[i] = tmp[i]; }
    }
}

fn main() {
    let mut arr = vec![0i64; N];
    let mut tmp = vec![0i64; N];

    let mut checksum: i64 = 0;
    for iter in 0..ITERS {
        let mut seed: i64 = 54321 + iter;
        for i in 0..N {
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            arr[i] = seed;
        }
        radix_sort(&mut arr, &mut tmp, N);
        checksum += arr[0] + arr[N / 2] + arr[N - 1];
    }
    println!("{}", checksum);
}
