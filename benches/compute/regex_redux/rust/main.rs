// Regex Redux Benchmark (simplified)
// Measures: pattern matching, string processing

fn match_agggtaaa(buf: &[u8], pos: usize) -> bool {
    if pos + 8 > buf.len() {
        return false;
    }
    let pattern = b"AGGGTAAA";
    let pattern_lower = b"agggtaaa";
    for i in 0..8 {
        let c = buf[pos + i];
        if c != pattern[i] && c != pattern_lower[i] {
            return false;
        }
    }
    true
}

fn match_tttaccct(buf: &[u8], pos: usize) -> bool {
    if pos + 8 > buf.len() {
        return false;
    }
    let pattern = b"TTTACCCT";
    let pattern_lower = b"tttaccct";
    for i in 0..8 {
        let c = buf[pos + i];
        if c != pattern[i] && c != pattern_lower[i] {
            return false;
        }
    }
    true
}

fn main() {
    let seq_len = 100_000;

    // Generate DNA sequence
    let mut buf = vec![0u8; seq_len];
    let bases = [b'A', b'C', b'G', b'T'];
    for i in 0..seq_len {
        let idx = ((i * 1103515245 + 12345) / 65536) % 4;
        buf[i] = bases[idx];
    }

    // Insert known pattern
    buf[100..108].copy_from_slice(b"agggtaaa");

    // Count patterns
    let mut count = 0i64;
    for i in 0..seq_len {
        if match_agggtaaa(&buf, i) {
            count += 1;
        }
        if match_tttaccct(&buf, i) {
            count += 1;
        }
    }

    println!("agggtaaa|tttaccct {}", count);
}
