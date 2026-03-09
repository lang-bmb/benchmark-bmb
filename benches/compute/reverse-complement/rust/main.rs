// Reverse Complement Benchmark
// Measures: array manipulation, character mapping
// Self-contained: generates synthetic DNA sequence internally

fn make_complement_table() -> [u8; 256] {
    let mut table = [0u8; 256];
    // Initialize all to self
    for i in 0..256 {
        table[i] = i as u8;
    }

    // Standard bases
    table[b'A' as usize] = b'T'; table[b'a' as usize] = b't';
    table[b'T' as usize] = b'A'; table[b't' as usize] = b'a';
    table[b'G' as usize] = b'C'; table[b'g' as usize] = b'c';
    table[b'C' as usize] = b'G'; table[b'c' as usize] = b'g';
    table[b'U' as usize] = b'A'; table[b'u' as usize] = b'a';

    // IUPAC ambiguity codes
    table[b'M' as usize] = b'K'; table[b'm' as usize] = b'k';
    table[b'K' as usize] = b'M'; table[b'k' as usize] = b'm';
    table[b'R' as usize] = b'Y'; table[b'r' as usize] = b'y';
    table[b'Y' as usize] = b'R'; table[b'y' as usize] = b'r';
    table[b'S' as usize] = b'S'; table[b's' as usize] = b's';
    table[b'W' as usize] = b'W'; table[b'w' as usize] = b'w';
    table[b'V' as usize] = b'B'; table[b'v' as usize] = b'b';
    table[b'B' as usize] = b'V'; table[b'b' as usize] = b'v';
    table[b'H' as usize] = b'D'; table[b'h' as usize] = b'd';
    table[b'D' as usize] = b'H'; table[b'd' as usize] = b'h';
    table[b'N' as usize] = b'N'; table[b'n' as usize] = b'n';

    table
}

fn reverse_complement(table: &[u8; 256], buf: &mut [u8]) {
    let len = buf.len();
    let mut i: usize = 0;
    let mut j: usize = len - 1;
    while i < j {
        let ci = table[buf[i] as usize];
        let cj = table[buf[j] as usize];
        buf[i] = cj;
        buf[j] = ci;
        i += 1;
        j -= 1;
    }
    if i == j {
        buf[i] = table[buf[i] as usize];
    }
}

fn main() {
    let table = make_complement_table();
    let len: usize = 10_000_000;
    let mut buf = vec![0u8; len];

    // Generate DNA sequence
    let bases = [b'A', b'C', b'G', b'T'];
    for i in 0..len {
        let seed = (i as u64).wrapping_mul(1103515245).wrapping_add(12345);
        let idx = ((seed / 65536) % 4) as usize;
        buf[i] = bases[idx];
    }

    // Reverse complement multiple times
    for _ in 0..10 {
        reverse_complement(&table, &mut buf);
    }

    // Checksum
    let mut sum: i64 = 0;
    for &b in &buf {
        sum += b as i64;
    }
    println!("{}", sum);
}
