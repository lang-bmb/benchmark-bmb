// reverse-complement - DNA strand complement benchmark
// Benchmarks Game standard algorithm
// Reads FASTA format, outputs reverse complement

use std::io::{self, BufRead, Write, BufWriter};

const LINE_WIDTH: usize = 60;

/// Get complement of a nucleotide (IUPAC codes)
fn complement(c: u8) -> u8 {
    match c {
        // Standard bases
        b'A' => b'T', b'a' => b't',
        b'T' => b'A', b't' => b'a',
        b'G' => b'C', b'g' => b'c',
        b'C' => b'G', b'c' => b'g',
        b'U' => b'A', b'u' => b'a',  // RNA

        // IUPAC ambiguity codes
        b'M' => b'K', b'm' => b'k',  // A or C -> T or G
        b'K' => b'M', b'k' => b'm',  // T or G -> A or C
        b'R' => b'Y', b'r' => b'y',  // A or G -> T or C
        b'Y' => b'R', b'y' => b'r',  // T or C -> A or G
        b'S' => b'S', b's' => b's',  // G or C (self)
        b'W' => b'W', b'w' => b'w',  // A or T (self)
        b'V' => b'B', b'v' => b'b',  // A, C, or G -> T, G, or C
        b'B' => b'V', b'b' => b'v',  // T, G, or C -> A, C, or G
        b'H' => b'D', b'h' => b'd',  // A, C, or T -> T, G, or A
        b'D' => b'H', b'd' => b'h',  // A, G, or T -> T, C, or A
        b'N' => b'N', b'n' => b'n',  // Any (self)

        _ => c,  // Unknown - keep as is
    }
}

/// Reverse complement a sequence in place
fn reverse_complement(seq: &mut [u8]) {
    let len = seq.len();
    if len == 0 { return; }

    let mut i = 0;
    let mut j = len - 1;

    while i < j {
        let tmp = complement(seq[i]);
        seq[i] = complement(seq[j]);
        seq[j] = tmp;
        i += 1;
        j -= 1;
    }

    if i == j {
        seq[i] = complement(seq[i]);
    }
}

/// Output sequence in FASTA format (LINE_WIDTH per line)
fn output_sequence<W: Write>(out: &mut W, seq: &[u8]) -> io::Result<()> {
    for chunk in seq.chunks(LINE_WIDTH) {
        out.write_all(chunk)?;
        out.write_all(b"\n")?;
    }
    Ok(())
}

fn main() -> io::Result<()> {
    let stdin = io::stdin();
    let stdout = io::stdout();
    let mut out = BufWriter::new(stdout.lock());

    let mut header = String::new();
    let mut sequence: Vec<u8> = Vec::with_capacity(1024);

    for line_result in stdin.lock().lines() {
        let line = line_result?;

        if line.starts_with('>') {
            // New sequence - output previous if any
            if !header.is_empty() {
                writeln!(out, "{}", header)?;
                reverse_complement(&mut sequence);
                output_sequence(&mut out, &sequence)?;
            }
            sequence.clear();
            header = line;
        } else if !line.starts_with(';') {
            // Sequence data (skip comments)
            for c in line.bytes() {
                if !c.is_ascii_whitespace() {
                    sequence.push(c);
                }
            }
        }
    }

    // Output last sequence
    if !header.is_empty() {
        writeln!(out, "{}", header)?;
        reverse_complement(&mut sequence);
        output_sequence(&mut out, &sequence)?;
    }

    Ok(())
}
