// fasta - DNA sequence generation benchmark
// Benchmarks Game standard algorithm with LCG random

use std::io::{self, Write, BufWriter};

const IM: i32 = 139968;
const IA: i32 = 3877;
const IC: i32 = 29573;
const LINE_WIDTH: usize = 60;

static mut SEED: i32 = 42;

fn random_num(max: f64) -> f64 {
    unsafe {
        SEED = (SEED * IA + IC) % IM;
        max * (SEED as f64) / (IM as f64)
    }
}

struct AminoAcid {
    c: u8,
    p: f64,
}

fn make_cumulative(table: &mut [AminoAcid]) {
    let mut cp = 0.0;
    for aa in table.iter_mut() {
        cp += aa.p;
        aa.p = cp;
    }
}

fn select_random(table: &[AminoAcid]) -> u8 {
    let r = random_num(1.0);
    for aa in table {
        if r < aa.p {
            return aa.c;
        }
    }
    table.last().unwrap().c
}

fn make_random_fasta<W: Write>(
    out: &mut W,
    id: &str,
    desc: &str,
    table: &[AminoAcid],
    n: usize,
) -> io::Result<()> {
    writeln!(out, ">{} {}", id, desc)?;

    let mut line = [0u8; LINE_WIDTH];
    let mut pos = 0;

    for _ in 0..n {
        line[pos] = select_random(table);
        pos += 1;
        if pos == LINE_WIDTH {
            out.write_all(&line)?;
            out.write_all(b"\n")?;
            pos = 0;
        }
    }
    if pos > 0 {
        out.write_all(&line[..pos])?;
        out.write_all(b"\n")?;
    }
    Ok(())
}

fn make_repeat_fasta<W: Write>(
    out: &mut W,
    id: &str,
    desc: &str,
    alu: &[u8],
    n: usize,
) -> io::Result<()> {
    writeln!(out, ">{} {}", id, desc)?;

    let alu_len = alu.len();
    let mut k = 0;
    let mut line = [0u8; LINE_WIDTH];
    let mut pos = 0;

    for _ in 0..n {
        line[pos] = alu[k];
        k = (k + 1) % alu_len;
        pos += 1;
        if pos == LINE_WIDTH {
            out.write_all(&line)?;
            out.write_all(b"\n")?;
            pos = 0;
        }
    }
    if pos > 0 {
        out.write_all(&line[..pos])?;
        out.write_all(b"\n")?;
    }
    Ok(())
}

fn main() -> io::Result<()> {
    let args: Vec<String> = std::env::args().collect();
    let n: usize = if args.len() > 1 {
        args[1].parse().unwrap_or(1000)
    } else {
        1000
    };

    let mut iub = vec![
        AminoAcid { c: b'a', p: 0.27 }, AminoAcid { c: b'c', p: 0.12 },
        AminoAcid { c: b'g', p: 0.12 }, AminoAcid { c: b't', p: 0.27 },
        AminoAcid { c: b'B', p: 0.02 }, AminoAcid { c: b'D', p: 0.02 },
        AminoAcid { c: b'H', p: 0.02 }, AminoAcid { c: b'K', p: 0.02 },
        AminoAcid { c: b'M', p: 0.02 }, AminoAcid { c: b'N', p: 0.02 },
        AminoAcid { c: b'R', p: 0.02 }, AminoAcid { c: b'S', p: 0.02 },
        AminoAcid { c: b'V', p: 0.02 }, AminoAcid { c: b'W', p: 0.02 },
        AminoAcid { c: b'Y', p: 0.02 },
    ];

    let mut homosapiens = vec![
        AminoAcid { c: b'a', p: 0.3029549426680 },
        AminoAcid { c: b'c', p: 0.1979883004921 },
        AminoAcid { c: b'g', p: 0.1975473066391 },
        AminoAcid { c: b't', p: 0.3015094502008 },
    ];

    make_cumulative(&mut iub);
    make_cumulative(&mut homosapiens);

    let alu = b"GGCCGGGCGCGGTGGCTCACGCCTGTAATCCCAGCACTTTG\
                GGAGGCCGAGGCGGGCGGATCACCTGAGGTCAGGAGTTCGA\
                GACCAGCCTGGCCAACATGGTGAAACCCCGTCTCTACTAAA\
                AATACAAAAATTAGCCGGGCGTGGTGGCGCGCGCCTGTAAT\
                CCCAGCTACTCGGGAGGCTGAGGCAGGAGAATCGCTTGAAC\
                CCGGGAGGCGGAGGTTGCAGTGAGCCGAGATCGCGCCACTG\
                CACTCCAGCCTGGGCGACAGAGCGAGACTCCGTCTCAAAAA";

    let stdout = io::stdout();
    let mut out = BufWriter::new(stdout.lock());

    make_repeat_fasta(&mut out, "ONE", "Homo sapiens alu", alu, n * 2)?;
    make_random_fasta(&mut out, "TWO", "IUB ambiguity codes", &iub, n * 3)?;
    make_random_fasta(&mut out, "THREE", "Homo sapiens frequency", &homosapiens, n * 5)?;

    Ok(())
}
