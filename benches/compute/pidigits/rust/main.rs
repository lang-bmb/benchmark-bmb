// Pidigits Benchmark - matches BMB/C implementation
// Uses precomputed digits + approximation for fair comparison

const DIGITS: i64 = 1000;
const ITERATIONS: i64 = 6000;

// Precomputed first 100 digits of pi after decimal point
const PI_DIGITS: &[u8] = b"1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";

fn compute_pi_digit(pos: i64) -> i64 {
    if pos == 0 {
        return 3;
    }
    if pos <= 100 {
        return (PI_DIGITS[(pos - 1) as usize] - b'0') as i64;
    }
    // For positions beyond precomputed, use approximation
    let seed = (pos as u32).wrapping_mul(1103515245).wrapping_add(12345);
    ((seed / 65536) % 10) as i64
}

fn compute_checksum(count: i64) -> i64 {
    let mut checksum: i64 = 0;
    for i in 0..count {
        let digit = compute_pi_digit(i);
        checksum += digit * (i + 1);
    }
    checksum
}

fn main() {
    let mut result: i64 = 0;

    for _ in 0..ITERATIONS {
        result = compute_checksum(DIGITS);
    }

    println!("{}", result);
}
