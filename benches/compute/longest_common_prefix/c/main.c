// Longest Common Prefix benchmark — sequential string comparison
// Measures: memory access patterns, sequential comparison, branch prediction
// Workload: 20000 strings of length 50, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 20000
#define STR_LEN 50
#define STRIDE 50
#define ITERS 1000

static int64_t lcp_len(const int64_t* ptr_a, const int64_t* ptr_b, int64_t str_len) {
    int64_t result = str_len;
    int64_t k = 0;
    while (k < str_len) {
        if (ptr_a[k] == ptr_b[k]) {
            k++;
        } else {
            result = k;
            k = str_len;
        }
    }
    return result;
}

int main() {
    int64_t* buf = (int64_t*)malloc((int64_t)N * STRIDE * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate N strings of STR_LEN chars using PRNG
        int64_t seed = 42 + iter;
        for (int64_t i = 0; i < N; i++) {
            for (int64_t j = 0; j < STR_LEN; j++) {
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                buf[i * STRIDE + j] = seed % 26;
            }
        }

        // Sum LCP lengths of all consecutive pairs
        int64_t total = 0;
        for (int64_t i = 0; i < N - 1; i++) {
            int64_t off_a = i * STRIDE;
            int64_t off_b = (i + 1) * STRIDE;
            total += lcp_len(buf + off_a, buf + off_b, STR_LEN);
        }
        checksum += total;
    }

    printf("%lld\n", (long long)checksum);
    free(buf);
    return 0;
}
