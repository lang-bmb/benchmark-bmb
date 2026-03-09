// K-Nucleotide Benchmark
// Measures: hash table, string processing
// Self-contained: generates synthetic DNA sequence internally

use std::collections::HashMap;

const SEQ_LEN: usize = 100_000;

fn generate_dna() -> Vec<u8> {
    let bases = [b'A', b'C', b'G', b'T'];
    let mut dna = Vec::with_capacity(SEQ_LEN);
    for i in 0..SEQ_LEN {
        let seed = (i as u64).wrapping_mul(1103515245).wrapping_add(12345);
        let idx = ((seed / 65536) % 4) as usize;
        dna.push(bases[idx]);
    }
    dna
}

fn count_kmers(seq: &[u8], k: usize) -> HashMap<Vec<u8>, i64> {
    let mut map: HashMap<Vec<u8>, i64> = HashMap::new();
    for i in 0..=(seq.len() - k) {
        let kmer = seq[i..i + k].to_vec();
        *map.entry(kmer).or_insert(0) += 1;
    }
    map
}

fn print_freq(seq: &[u8], k: usize) {
    let map = count_kmers(seq, k);
    let total = (seq.len() - k + 1) as f64;

    let mut entries: Vec<(Vec<u8>, i64)> = map.into_iter().collect();
    // Sort descending by count, then ascending by key
    entries.sort_by(|a, b| {
        b.1.cmp(&a.1).then_with(|| a.0.cmp(&b.0))
    });

    for (kmer, count) in &entries {
        let pct = 100.0 * (*count as f64) / total;
        let key = std::str::from_utf8(kmer).unwrap();
        println!("{} {:.3}", key, pct);
    }
    println!();
}

fn print_count(seq: &[u8], pattern: &[u8]) {
    let k = pattern.len();
    let map = count_kmers(seq, k);
    let count = map.get(pattern).copied().unwrap_or(0);
    let key = std::str::from_utf8(pattern).unwrap();
    println!("{}\t{}", count, key);
}

fn main() {
    let seq = generate_dna();

    // Output frequency tables for k=1 and k=2
    print_freq(&seq, 1);
    print_freq(&seq, 2);

    // Output specific pattern counts
    print_count(&seq, b"GGT");
    print_count(&seq, b"GGTA");
    print_count(&seq, b"GGTATT");
    print_count(&seq, b"GGTATTTTAATT");
    print_count(&seq, b"GGTATTTTAATTTATAGT");
}
