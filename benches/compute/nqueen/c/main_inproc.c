// N-Queens with in-process timing + DCE/IPC barrier
// Cycle 2661: black_box-equivalent for fair BMB comparison
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

// Match BMB bmb_black_box: volatile sink prevents constant folding
static volatile int64_t black_sink;
static int64_t black_box(int64_t v) { black_sink = v; return black_sink; }

int64_t solve(int64_t n, int64_t row, int64_t cols, int64_t diag1, int64_t diag2) {
    if (row == n) return 1;
    int64_t all_ones = (1LL << n) - 1;
    int64_t available = all_ones & (~cols) & (~diag1) & (~diag2);
    int64_t count = 0;
    while (available) {
        int64_t pos = available & (-available);
        available -= pos;
        int64_t new_cols = cols | pos;
        int64_t new_diag1 = (diag1 | pos) << 1;
        int64_t new_diag2 = (diag2 | pos) >> 1;
        count += solve(n, row + 1, new_cols, new_diag1, new_diag2);
    }
    return count;
}

int64_t nqueens(int64_t n) { return solve(n, 0, 0, 0, 0); }

int main() {
    // Warmup
    int64_t warm_n = black_box(15);
    int64_t warmup = black_box(nqueens(warm_n));
    (void)warmup;

    int64_t t0 = time_ns();
    int64_t result = 0;
    for (int i = 0; i < 10; i++) {
        int64_t n = black_box(15);
        int64_t c = nqueens(n);
        result += black_box(c);
    }
    int64_t t1 = time_ns();
    int64_t elapsed_us = (t1 - t0) / 1000;
    printf("%lld\n", (long long)result);
    printf("%lld\n", (long long)elapsed_us);
    return 0;
}
