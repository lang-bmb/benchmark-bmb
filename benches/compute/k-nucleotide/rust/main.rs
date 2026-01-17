// k-nucleotide - DNA sequence pattern counting benchmark
// Benchmarks Game standard algorithm
// Counts k-mer frequencies using hash table

use std::collections::HashMap;
use std::io::{self, BufRead};

/// Count k-mers of length k in sequence
fn count_kmers(seq: &[u8], k: usize) -> HashMap<Vec<u8>, usize> {
    let mut counts = HashMap::new();
    if seq.len() >= k {
        for window in seq.windows(k) {
            *counts.entry(window.to_vec()).or_insert(0) += 1;
        }
    }
    counts
}

/// Print frequency table sorted by count desc, then key asc
fn print_freq(seq: &[u8], k: usize) {
    let counts = count_kmers(seq, k);
    let total = seq.len() - k + 1;

    // Collect and sort
    let mut entries: Vec<_> = counts.into_iter().collect();
    entries.sort_by(|a, b| {
        b.1.cmp(&a.1).then_with(|| a.0.cmp(&b.0))
    });

    for (kmer, count) in entries {
        let pct = 100.0 * count as f64 / total as f64;
        let kmer_str: String = kmer.iter().map(|&c| c as char).collect();
        println!("{} {:.3}", kmer_str, pct);
    }
    println!();
}

/// Print count for specific pattern
fn print_count(seq: &[u8], pattern: &str) {
    let pattern_bytes: Vec<u8> = pattern.bytes().map(|c| c.to_ascii_uppercase()).collect();
    let k = pattern_bytes.len();
    let counts = count_kmers(seq, k);
    let count = counts.get(&pattern_bytes).copied().unwrap_or(0);
    println!("{}\t{}", count, pattern);
}

fn main() -> io::Result<()> {
    let stdin = io::stdin();
    let mut sequence = Vec::new();
    let mut in_three = false;

    // Find and read sequence THREE
    for line_result in stdin.lock().lines() {
        let line = line_result?;

        if line.starts_with('>') {
            if line.contains("THREE") {
                in_three = true;
            } else {
                in_three = false;
            }
        } else if in_three && !line.starts_with(';') {
            for c in line.bytes() {
                if c.is_ascii_alphabetic() {
                    sequence.push(c.to_ascii_uppercase());
                }
            }
        }
    }

    // Output frequency tables for k=1 and k=2
    print_freq(&sequence, 1);
    print_freq(&sequence, 2);

    // Output specific pattern counts
    print_count(&sequence, "GGT");
    print_count(&sequence, "GGTA");
    print_count(&sequence, "GGTATT");
    print_count(&sequence, "GGTATTTTAATT");
    print_count(&sequence, "GGTATTTTAATTTATAGT");

    Ok(())
}
