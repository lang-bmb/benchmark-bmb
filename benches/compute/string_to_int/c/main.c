// String to Int (atoi) — parse integers from digit arrays
// Measures: character processing, multiplication, sequential scan
// Workload: N=500000 strings, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t my_atoi(const int64_t* buf, int64_t len) {
    int64_t result = 0;
    for (int64_t i = 0; i < len; i++) {
        result = result * 10 + buf[i];
    }
    return result;
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 1000;
    int64_t MAXDIGITS = 10;
    int64_t* buf = (int64_t*)malloc(MAXDIGITS * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t val = seed % 1000000000;
            int64_t tmp = val;
            int64_t len = 0;
            while (tmp > 0) {
                buf[len++] = tmp % 10;
                tmp /= 10;
            }
            // Reverse digits
            int64_t lo = 0, hi = len - 1;
            while (lo < hi) {
                int64_t t = buf[lo];
                buf[lo] = buf[hi];
                buf[hi] = t;
                lo++;
                hi--;
            }
            checksum += my_atoi(buf, len);
        }
    }

    printf("%lld\n", (long long)checksum);
    free(buf);
    return 0;
}
