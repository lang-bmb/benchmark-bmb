// Mandelbrot with in-process timing — Cycle 2695
// Fixed-point integer arithmetic (scale=10000)
// 측정: t1 - t0 알고리즘 본질 시간 (process startup 제거)

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#ifdef _WIN32
  #include <windows.h>
  static int64_t time_ns(void) {
    static LARGE_INTEGER freq = {0};
    if (freq.QuadPart == 0) QueryPerformanceFrequency(&freq);
    LARGE_INTEGER c; QueryPerformanceCounter(&c);
    int64_t s = c.QuadPart / freq.QuadPart;
    int64_t r = c.QuadPart % freq.QuadPart;
    return s * 1000000000LL + (r * 1000000000LL) / freq.QuadPart;
  }
#else
  #include <time.h>
  static int64_t time_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (int64_t)(ts.tv_sec * 1000000000LL + ts.tv_nsec);
  }
#endif

#define SCALE 10000LL
#define THRESHOLD 400000000LL

static inline int64_t mul_fp(int64_t a, int64_t b) {
    return (a * b) / SCALE;
}

static inline int64_t square_fp(int64_t x) {
    return mul_fp(x, x);
}

static int64_t iterate(int64_t cr, int64_t ci, int64_t max_iter) {
    int64_t zr = 0, zi = 0, iter = 0;
    while (iter < max_iter) {
        int64_t zr2 = square_fp(zr);
        int64_t zi2 = square_fp(zi);
        int64_t mag = zr2 + zi2;
        if (mag > THRESHOLD) return iter;
        int64_t new_zr = zr2 - zi2 + cr;
        int64_t new_zi = 2 * mul_fp(zr, zi) + ci;
        zr = new_zr;
        zi = new_zi;
        iter++;
    }
    return max_iter;
}

static int64_t mandelbrot_point(int64_t x, int64_t y, int64_t width, int64_t height, int64_t max_iter) {
    int64_t cr = (x * 4 * SCALE / width) - 2 * SCALE;
    int64_t ci = (y * 4 * SCALE / height) - 2 * SCALE;
    return iterate(cr, ci, max_iter);
}

int main() {
    int size = 2000;
    int max_iter = 100;

    int64_t t0 = time_ns();
    int64_t count = 0;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            int64_t result = mandelbrot_point(x, y, size, size, max_iter);
            if (result < max_iter) count++;
        }
    }
    int64_t t1 = time_ns();
    int64_t elapsed_us = (t1 - t0) / 1000;
    printf("%" PRId64 "\n%" PRId64 "\n", count, elapsed_us);
    return 0;
}
