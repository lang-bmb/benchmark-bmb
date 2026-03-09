#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10000;
        }

        int64_t max_so_far = arr[0];
        int64_t max_diff = 0;
        for (int64_t i = 1; i < N; i++) {
            int64_t val = arr[i];
            int64_t diff = max_so_far - val;
            if (diff > max_diff) max_diff = diff;
            if (val > max_so_far) max_so_far = val;
        }
        checksum += max_diff;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
