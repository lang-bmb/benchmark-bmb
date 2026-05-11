// Fibonacci iterative — in-process timing + DCE barrier (Cycle 2686)
// Mirrors BMB main_inproc.bmb: 100M iterations, black_box, time_ns
#include <stdio.h>
#include <stdint.h>
#include <time.h>

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
static int64_t time_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (int64_t)(ts.tv_sec * 1000000000LL + ts.tv_nsec);
}
#endif

static volatile int64_t black_sink;
static int64_t black_box(int64_t v) { black_sink = v; return black_sink; }

int64_t fibonacci_iter(int64_t n) {
    int64_t a = 0;
    int64_t b = 1;
    for (int64_t i = 0; i < n; i++) {
        int64_t temp = a + b;
        a = b;
        b = temp;
    }
    return a;
}

int main(void) {
    int64_t warmup = black_box(50);
    (void)black_box(fibonacci_iter(warmup));

    int64_t t0 = time_ns();
    int64_t result = 0;
    for (int64_t i = 0; i < 100000000LL; i++) {
        int64_t n = black_box(50);
        result += black_box(fibonacci_iter(n));
    }
    int64_t t1 = time_ns();
    int64_t elapsed_us = (t1 - t0) / 1000;

    printf("%lld\n", (long long)result);
    printf("%lld\n", (long long)elapsed_us);
    return 0;
}
