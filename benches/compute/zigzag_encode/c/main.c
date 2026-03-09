// Zigzag Encode/Decode — protobuf-style zigzag encoding
// Measures: bit manipulation, shift operations, sequential access
// Workload: N=1000000 array, 3000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static inline int64_t zigzag_encode(int64_t x) {
    return (x << 1) ^ (x >> 63);
}

static inline int64_t zigzag_decode(int64_t x) {
    return (x >> 1) ^ -(x & 1);
}

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 3000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* enc = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    int64_t checksum = 0;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed - 1073741823;
        }
        for (int64_t i = 0; i < N; i++) {
            enc[i] = zigzag_encode(arr[i]);
        }
        int64_t sum = 0;
        for (int64_t i = 0; i < N; i++) {
            sum += zigzag_decode(enc[i]);
        }
        checksum += sum;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    free(enc);
    return 0;
}
