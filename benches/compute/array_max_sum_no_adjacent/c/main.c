// Array Max Sum No Adjacent — maximum sum of non-adjacent elements (house robber)
// Measures: register carry (include, exclude), sequential scan
// Workload: N=2000000 array, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t max_sum_no_adj(int64_t* arr, int64_t n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    int64_t incl = arr[0];
    int64_t excl = 0;
    for (int64_t i = 1; i < n; i++) {
        int64_t val = arr[i];
        int64_t new_incl = excl + val;
        int64_t new_excl = incl > excl ? incl : excl;
        incl = new_incl;
        excl = new_excl;
    }
    return incl > excl ? incl : excl;
}

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 1000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 100;
        }
        checksum += max_sum_no_adj(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
