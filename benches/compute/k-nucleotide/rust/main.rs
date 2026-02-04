// K-Nucleotide Benchmark
// Measures: hash table, string processing

use std::collections::HashMap;

fn main() {
    // Generate test DNA sequence
    let len = 100_000;
    let mut dna = Vec::with_capacity(len);
    let bases = [b'A', b'C', b'G', b'T'];

    for i in 0..len {
        let idx = ((i * 1103515245 + 12345) / 65536) % 4;
        dna.push(bases[idx]);
    }

    // Count 1-mers
    let mut counts: HashMap<u8, i64> = HashMap::new();
    for &b in &dna {
        *counts.entry(b).or_insert(0) += 1;
    }

    // Count 2-mers
    let mut counts2: HashMap<[u8; 2], i64> = HashMap::new();
    for w in dna.windows(2) {
        let key = [w[0], w[1]];
        *counts2.entry(key).or_insert(0) += 1;
    }

    // Output
    let mut total: i64 = 0;
    for (_, &c) in &counts {
        total += c;
    }
    for (_, &c) in &counts2 {
        total += c;
    }
    println!("{}", total);
}
