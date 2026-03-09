// Huffman encoding benchmark — frequency counting + priority queue + tree build
// Measures: array access, sorting, tree construction, encoding
// Workload: 100K character messages, 200 iterations

const ALPHA: usize = 26;

fn heap_swap(freq: &mut [i64], idx: &mut [i64], a: usize, b: usize) {
    freq.swap(a, b);
    idx.swap(a, b);
}

fn heap_up(freq: &mut [i64], idx: &mut [i64], mut i: usize) {
    while i > 0 {
        let p = (i - 1) / 2;
        if freq[i] < freq[p] {
            heap_swap(freq, idx, i, p);
            i = p;
        } else {
            break;
        }
    }
}

fn heap_down(freq: &mut [i64], idx: &mut [i64], size: usize, mut i: usize) {
    loop {
        let mut smallest = i;
        let l = 2 * i + 1;
        let r = 2 * i + 2;
        if l < size && freq[l] < freq[smallest] { smallest = l; }
        if r < size && freq[r] < freq[smallest] { smallest = r; }
        if smallest == i { break; }
        heap_swap(freq, idx, i, smallest);
        i = smallest;
    }
}

fn huffman_encode(msg: &[i64], len: usize) -> i64 {
    let mut counts = [0i64; ALPHA];
    for i in 0..len {
        counts[msg[i] as usize] += 1;
    }

    let mut heap_freq = [0i64; ALPHA * 2];
    let mut heap_idx = [0i64; ALPHA * 2];
    let mut heap_size: usize = 0;

    for i in 0..ALPHA {
        if counts[i] > 0 {
            heap_freq[heap_size] = counts[i];
            heap_idx[heap_size] = i as i64;
            heap_up(&mut heap_freq, &mut heap_idx, heap_size);
            heap_size += 1;
        }
    }

    let mut total_bits: i64 = 0;
    while heap_size > 1 {
        let f1 = heap_freq[0];
        heap_size -= 1;
        heap_freq[0] = heap_freq[heap_size];
        heap_idx[0] = heap_idx[heap_size];
        heap_down(&mut heap_freq, &mut heap_idx, heap_size, 0);

        let f2 = heap_freq[0];
        heap_size -= 1;
        heap_freq[0] = heap_freq[heap_size];
        heap_idx[0] = heap_idx[heap_size];
        heap_down(&mut heap_freq, &mut heap_idx, heap_size, 0);

        let combined = f1 + f2;
        total_bits += combined;
        heap_freq[heap_size] = combined;
        heap_idx[heap_size] = -1;
        heap_up(&mut heap_freq, &mut heap_idx, heap_size);
        heap_size += 1;
    }

    total_bits
}

fn main() {
    let len: usize = 100000;
    let iters: i64 = 200;
    let mut msg = vec![0i64; len];

    let mut checksum: i64 = 0;
    for iter in 0..iters {
        let mut seed: i64 = 9999 + iter;
        for i in 0..len {
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            let r = seed % 100;
            let ch = if r < 40 { seed % 5 }
                     else if r < 70 { 5 + seed % 5 }
                     else { 10 + seed % 16 };
            msg[i] = ch;
        }
        checksum += huffman_encode(&msg, len);
    }

    println!("{}", checksum);
}
