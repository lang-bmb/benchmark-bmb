// Reverse Complement Benchmark
// Measures: array manipulation, character mapping

fn complement(c: u8) -> u8 {
    match c {
        b'A' | b'a' => b'T',
        b'T' | b't' => b'A',
        b'G' | b'g' => b'C',
        b'C' | b'c' => b'G',
        _ => c,
    }
}

fn reverse_complement(buf: &mut [u8]) {
    let len = buf.len();
    let mut i = 0;
    let mut j = len - 1;
    while i < j {
        let ci = complement(buf[i]);
        let cj = complement(buf[j]);
        buf[i] = cj;
        buf[j] = ci;
        i += 1;
        j -= 1;
    }
    if i == j {
        buf[i] = complement(buf[i]);
    }
}

fn main() {
    let len = 10_000_000;
    let mut buf = vec![0u8; len];

    // Generate DNA sequence
    let bases = [b'A', b'C', b'G', b'T'];
    for i in 0..len {
        let idx = ((i * 1103515245 + 12345) / 65536) % 4;
        buf[i] = bases[idx];
    }

    // Reverse complement multiple times
    for _ in 0..10 {
        reverse_complement(&mut buf);
    }

    // Checksum
    let mut sum: i64 = 0;
    for &b in &buf {
        sum += b as i64;
    }
    println!("{}", sum);
}
