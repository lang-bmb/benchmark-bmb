// Mandelbrot set computation benchmark
// Measures: floating-point arithmetic, loops

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define SCALE 10000LL

int64_t mul_fp(int64_t a, int64_t b) {
    return (a * b) / SCALE;
}

int64_t square_fp(int64_t x) {
    return mul_fp(x, x);
}

int64_t iterate(int64_t cr, int64_t ci, int64_t zr, int64_t zi, int64_t iter, int64_t max_iter) {
    while (iter < max_iter) {
        int64_t zr2 = square_fp(zr);
        int64_t zi2 = square_fp(zi);
        int64_t mag = zr2 + zi2;
        if (mag > 4 * SCALE * SCALE) return iter;
        int64_t new_zr = zr2 - zi2 + cr;
        int64_t new_zi = 2 * mul_fp(zr, zi) + ci;
        zr = new_zr;
        zi = new_zi;
        iter++;
    }
    return max_iter;
}

int64_t mandelbrot_point(int64_t x, int64_t y, int64_t width, int64_t height, int64_t max_iter) {
    int64_t cr = (x * 4 * SCALE / width) - 2 * SCALE;
    int64_t ci = (y * 4 * SCALE / height) - 2 * SCALE;
    return iterate(cr, ci, 0, 0, 0, max_iter);
}

int main() {
    int size = 2000;
    int max_iter = 100;
    int64_t count = 0;

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            int64_t result = mandelbrot_point(x, y, size, size, max_iter);
            if (result < max_iter) count++;
        }
    }

    printf("%" PRId64 "\n", count);
    return 0;
}
