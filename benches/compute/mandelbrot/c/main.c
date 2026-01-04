// Mandelbrot set computation benchmark
// Measures: floating-point arithmetic, loops

#include <stdio.h>

#define SCALE 10000

long mul_fp(long a, long b) {
    return (a * b) / SCALE;
}

long square_fp(long x) {
    return mul_fp(x, x);
}

long iterate(long cr, long ci, long zr, long zi, long iter, long max_iter) {
    while (iter < max_iter) {
        long zr2 = square_fp(zr);
        long zi2 = square_fp(zi);
        long mag = zr2 + zi2;
        if (mag > 4 * SCALE * SCALE) return iter;
        long new_zr = zr2 - zi2 + cr;
        long new_zi = 2 * mul_fp(zr, zi) + ci;
        zr = new_zr;
        zi = new_zi;
        iter++;
    }
    return max_iter;
}

long mandelbrot_point(long x, long y, long width, long height, long max_iter) {
    long cr = (x * 4 * SCALE / width) - 2 * SCALE;
    long ci = (y * 4 * SCALE / height) - 2 * SCALE;
    return iterate(cr, ci, 0, 0, 0, max_iter);
}

int main() {
    int size = 50;
    int max_iter = 50;
    long count = 0;

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            long result = mandelbrot_point(x, y, size, size, max_iter);
            if (result < max_iter) count++;
        }
    }

    printf("%ld\n", count);
    return 0;
}
