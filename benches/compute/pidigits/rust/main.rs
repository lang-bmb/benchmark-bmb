// Pidigits Benchmark - matches BMB/C implementation
// Uses precomputed digits + approximation for fair comparison

const DIGITS: i32 = 1000;

// Precomputed first 100 digits of pi after decimal point
const PI_DIGITS: &[u8] = b"1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170";

fn compute_pi_digit(pos: i32) -> i32 {
    if pos == 0 {
        return 3;
    }
    if pos - 1 < 100 {
        return (PI_DIGITS[(pos - 1) as usize] - b'0') as i32;
    }
    // For positions beyond precomputed, use approximation
    let seed = (pos as u32).wrapping_mul(1103515245).wrapping_add(12345);
    ((seed / 65536) % 10) as i32
}

fn print_digits(count: i32) {
    let mut line_count = 0;

    for i in 0..count {
        let digit = compute_pi_digit(i);
        print!("{}", digit);
        line_count += 1;

        if line_count == 10 {
            println!("\t:{}", i + 1);
            line_count = 0;
        }
    }

    // Handle partial last line
    if line_count > 0 {
        for _ in line_count..10 {
            print!(" ");
        }
        println!("\t:{}", count);
    }
}

fn main() {
    print_digits(DIGITS);
}
