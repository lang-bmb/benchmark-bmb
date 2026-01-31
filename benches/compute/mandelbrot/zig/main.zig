// Mandelbrot set computation benchmark
// Measures: fixed-point arithmetic, loops
// Uses same algorithm as C/BMB version

const std = @import("std");

const SCALE: i64 = 10000;

fn mul_fp(a: i64, b: i64) i64 {
    return @divTrunc(a * b, SCALE);
}

fn square_fp(x: i64) i64 {
    return mul_fp(x, x);
}

fn iterate(cr: i64, ci: i64, initial_zr: i64, initial_zi: i64, initial_iter: i64, max_iter: i64) i64 {
    var zr = initial_zr;
    var zi = initial_zi;
    var iter = initial_iter;

    while (iter < max_iter) {
        const zr2 = square_fp(zr);
        const zi2 = square_fp(zi);
        const mag = zr2 + zi2;
        if (mag > 4 * SCALE * SCALE) return iter;
        const new_zr = zr2 - zi2 + cr;
        const new_zi = 2 * mul_fp(zr, zi) + ci;
        zr = new_zr;
        zi = new_zi;
        iter += 1;
    }
    return max_iter;
}

fn mandelbrot_point(x: i64, y: i64, width: i64, height: i64, max_iter: i64) i64 {
    const cr = @divTrunc(x * 4 * SCALE, width) - 2 * SCALE;
    const ci = @divTrunc(y * 4 * SCALE, height) - 2 * SCALE;
    return iterate(cr, ci, 0, 0, 0, max_iter);
}

pub fn main() !void {
    const stdout = std.io.getStdOut().writer();

    const size: i64 = 2000;
    const max_iter: i64 = 100;
    var count: i64 = 0;

    var y: i64 = 0;
    while (y < size) : (y += 1) {
        var x: i64 = 0;
        while (x < size) : (x += 1) {
            const result = mandelbrot_point(x, y, size, size, max_iter);
            if (result < max_iter) count += 1;
        }
    }

    try stdout.print("{d}\n", .{count});
}
