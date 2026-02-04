// Mandelbrot Set Benchmark (fixed-point version)
// Measures: integer arithmetic, nested loops
// Matches BMB/C implementation for fair comparison

const SCALE: i64 = 10000;

#[inline]
fn mul_fp(a: i64, b: i64) -> i64 {
    (a * b) / SCALE
}

#[inline]
fn square_fp(x: i64) -> i64 {
    mul_fp(x, x)
}

fn iterate(cr: i64, ci: i64, mut zr: i64, mut zi: i64, mut iter: i64, max_iter: i64) -> i64 {
    let threshold = 4 * SCALE * SCALE;
    while iter < max_iter {
        let zr2 = square_fp(zr);
        let zi2 = square_fp(zi);
        let mag = zr2 + zi2;
        if mag > threshold {
            return iter;
        }
        let new_zr = zr2 - zi2 + cr;
        let new_zi = 2 * mul_fp(zr, zi) + ci;
        zr = new_zr;
        zi = new_zi;
        iter += 1;
    }
    max_iter
}

fn mandelbrot_point(x: i64, y: i64, width: i64, height: i64, max_iter: i64) -> i64 {
    let cr = (x * 4 * SCALE / width) - 2 * SCALE;
    let ci = (y * 4 * SCALE / height) - 2 * SCALE;
    iterate(cr, ci, 0, 0, 0, max_iter)
}

fn main() {
    let size: i64 = 2000;
    let max_iter: i64 = 100;
    let mut count: i64 = 0;

    for y in 0..size {
        for x in 0..size {
            let result = mandelbrot_point(x, y, size, size, max_iter);
            if result < max_iter {
                count += 1;
            }
        }
    }
    println!("{}", count);
}
