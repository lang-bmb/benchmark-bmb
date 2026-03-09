// Bitcount benchmark — population count (Hamming weight)
// Measures: bitwise operations, loop performance, branch prediction
// Workload: count bits in 10M numbers, 30 iterations

// Brian Kernighan's bit counting (no count_ones — fair comparison)
fn popcount_manual(x: i64) -> i64 {
    let mut count: i64 = 0;
    let mut u = x as u64;
    while u != 0 {
        u &= u - 1;
        count += 1;
    }
    count
}

fn main() {
    let n: i64 = 10000000;
    let iters: i64 = 30;

    let mut checksum: i64 = 0;
    for iter in 0..iters {
        let mut seed: i64 = 54321 + iter;
        let mut sum: i64 = 0;
        for _ in 0..n {
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            sum += popcount_manual(seed);
        }
        checksum += sum;
    }

    println!("{}", checksum);
}
