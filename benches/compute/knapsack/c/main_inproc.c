// 0/1 Knapsack with in-process timing — Cycle 2662
#include <stdio.h>
#include <stdlib.h>
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

static int64_t knapsack(int64_t n, int64_t capacity, const int64_t* weights, const int64_t* values, int64_t* dp) {
    for (int64_t j = 0; j <= capacity; j++) dp[j] = 0;
    for (int64_t i = 0; i < n; i++) {
        for (int64_t j = capacity; j >= weights[i]; j--) {
            int64_t take = dp[j - weights[i]] + values[i];
            if (take > dp[j]) dp[j] = take;
        }
    }
    return dp[capacity];
}

int main() {
    int64_t N = 2000, CAP = 5000, ITERS = 50;
    int64_t* weights = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* values  = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* dp      = (int64_t*)malloc((CAP + 1) * sizeof(int64_t));

    int64_t t0 = time_ns();
    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 777 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            weights[i] = (seed % 50) + 1;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            values[i] = (seed % 100) + 1;
        }
        checksum += knapsack(N, CAP, weights, values, dp);
    }
    int64_t t1 = time_ns();
    int64_t elapsed_us = (t1 - t0) / 1000;
    printf("%lld\n%lld\n", (long long)checksum, (long long)elapsed_us);
    free(weights); free(values); free(dp);
    return 0;
}
