// FASTA Benchmark
// Measures: random number generation, string building

const IM: i32 = 139968;
const IA: i32 = 3877;
const IC: i32 = 29573;

static mut SEED: i32 = 42;

fn random(max: f64) -> f64 {
    unsafe {
        SEED = (SEED * IA + IC) % IM;
        max * (SEED as f64) / (IM as f64)
    }
}

const ALU: &[u8] = b"GGCCGGGCGCGGTGGCTCACGCCTGTAATCCCAGCACTTTGGGAGGCCGAGGCGGGCGGATCACCTGAGGTCAGGAGTTCGAGACCAGCCTGGCCAACATGGTGAAACCCCGTCTCTACTAAAAATACAAAAATTAGCCGGGCGTGGTGGCGCGCGCCTGTAATCCCAGCTACTCGGGAGGCTGAGGCAGGAGAATCGCTTGAACCCGGGAGGCGGAGGTTGCAGTGAGCCGAGATCGCGCCACTGCACTCCAGCCTGGGCGACAGAGCGAGACTCCGTCTCAAAAA";

fn repeat_fasta(id: &str, desc: &str, alu: &[u8], n: usize) {
    println!(">{} {}", id, desc);
    let alu_len = alu.len();
    let mut pos = 0;
    let mut remaining = n;
    while remaining > 0 {
        let line_len = if remaining > 60 { 60 } else { remaining };
        for _ in 0..line_len {
            print!("{}", alu[pos] as char);
            pos = (pos + 1) % alu_len;
        }
        println!();
        remaining -= line_len;
    }
}

const IUB: [(u8, f64); 15] = [
    (b'a', 0.27), (b'c', 0.12), (b'g', 0.12), (b't', 0.27),
    (b'B', 0.02), (b'D', 0.02), (b'H', 0.02), (b'K', 0.02),
    (b'M', 0.02), (b'N', 0.02), (b'R', 0.02), (b'S', 0.02),
    (b'V', 0.02), (b'W', 0.02), (b'Y', 0.02),
];

const HOMOSAPIENS: [(u8, f64); 4] = [
    (b'a', 0.3029549426680), (b'c', 0.1979883004921),
    (b'g', 0.1975473066391), (b't', 0.3015094502008),
];

fn make_cumulative(table: &[(u8, f64)]) -> Vec<(u8, f64)> {
    let mut result = Vec::with_capacity(table.len());
    let mut cp = 0.0;
    for &(c, p) in table {
        cp += p;
        result.push((c, cp));
    }
    result
}

fn select_random(table: &[(u8, f64)]) -> u8 {
    let r = random(1.0);
    for &(c, cp) in table {
        if r < cp {
            return c;
        }
    }
    table.last().unwrap().0
}

fn random_fasta(id: &str, desc: &str, table: &[(u8, f64)], n: usize) {
    println!(">{} {}", id, desc);
    let cumulative = make_cumulative(table);
    let mut remaining = n;
    while remaining > 0 {
        let line_len = if remaining > 60 { 60 } else { remaining };
        for _ in 0..line_len {
            print!("{}", select_random(&cumulative) as char);
        }
        println!();
        remaining -= line_len;
    }
}

fn main() {
    let n = 1_000_000;
    repeat_fasta("ONE", "Homo sapiens alu", ALU, n * 2);
    random_fasta("TWO", "IUB ambiguity codes", &IUB, n * 3);
    random_fasta("THREE", "Homo sapiens frequency", &HOMOSAPIENS, n * 5);
}
