// String Hash — FNV-1a style hash over i64 arrays
// Measures: sequential access, multiply, XOR
// Workload: N=100000 strings of length 100, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t fnv_hash(const int64_t* data, int64_t len) {
    int64_t hash = 2166136261;
    for (int64_t i = 0; i < len; i++) {
        hash = (hash ^ data[i]) * 16777619;
    }
    return hash;
}

int main() {
    int64_t NSTRINGS = 100000;
    int64_t SLEN = 100;
    int64_t ITERS = 1000;
    int64_t* data = (int64_t*)malloc(NSTRINGS * SLEN * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < NSTRINGS * SLEN; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        data[i] = seed % 256;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < NSTRINGS; i++) {
            checksum += fnv_hash(data + i * SLEN, SLEN);
        }
    }

    printf("%lld\n", (long long)checksum);
    free(data);
    return 0;
}
