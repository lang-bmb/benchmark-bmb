// Boundary Sum — sum elements at ascending/descending boundaries
// Measures: register-carry (prev, direction detection), sequential scan
// Workload: N=2000000, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000, ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0, seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10000;
        }
        int64_t sum = 0;
        int64_t prev = arr[0];
        for (int64_t i = 1; i < N; i++) {
            int64_t cur = arr[i];
            int64_t diff = cur - prev;
            if (diff > 0) sum += cur;
            else sum -= cur;
            prev = cur;
        }
        checksum += sum % 1000000007;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
