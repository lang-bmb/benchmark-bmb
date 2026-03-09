// XOR Cipher — encrypt/decrypt array with repeating key
// Measures: sequential access, bitwise XOR, modular arithmetic
// Workload: N=1000000 array, 3000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t xor_encrypt(int64_t* arr, int64_t n, int64_t* key, int64_t keylen) {
    int64_t checksum = 0;
    for (int64_t i = 0; i < n; i++) {
        int64_t k = key[i % keylen];
        arr[i] ^= k;
        checksum += arr[i];
    }
    return checksum;
}

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 3000;
    int64_t KEYLEN = 16;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* key = (int64_t*)malloc(KEYLEN * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < KEYLEN; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        key[i] = seed;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t j = 0; j < N; j++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[j] = seed;
        }
        checksum += xor_encrypt(arr, N, key, KEYLEN);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    free(key);
    return 0;
}
