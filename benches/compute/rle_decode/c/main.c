// Run-Length Decoding — decode compressed pairs to output buffer
// Measures: sequential read/write, variable-length expansion, memory throughput
// Workload: 200K compressed pairs, ~200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t rle_decode(int64_t* pairs, int64_t npairs, uint8_t* out) {
    int64_t pos = 0;
    for (int64_t i = 0; i < npairs; i++) {
        int64_t count = pairs[i * 2];
        int64_t value = pairs[i * 2 + 1];
        uint8_t val_u8 = (uint8_t)(value % 256);
        for (int64_t j = 0; j < count; j++) {
            out[pos] = val_u8;
            pos++;
        }
    }
    return pos;
}

int main() {
    int64_t NPAIRS = 200000;
    int64_t ITERS = 200;
    int64_t* pairs = (int64_t*)malloc(NPAIRS * 2 * sizeof(int64_t));
    // Max output: each pair has count 1..16, so max = NPAIRS * 16
    int64_t max_out = NPAIRS * 16;
    uint8_t* out = (uint8_t*)malloc(max_out);

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 77777 + iter;
        for (int64_t i = 0; i < NPAIRS; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t count = (seed % 16) + 1;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t value = seed % 256;
            pairs[i * 2] = count;
            pairs[i * 2 + 1] = value;
        }
        int64_t decoded_len = rle_decode(pairs, NPAIRS, out);
        // Checksum: decoded length + sample bytes
        checksum += decoded_len;
        if (decoded_len > 0) {
            checksum += out[0] + out[decoded_len / 2] + out[decoded_len - 1];
        }
    }

    printf("%lld\n", (long long)checksum);
    free(pairs);
    free(out);
    return 0;
}
