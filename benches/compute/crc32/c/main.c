// CRC32 benchmark — table-driven CRC32 computation
// Measures: table lookup, bitwise operations, byte extraction
// Workload: 1MB pseudo-random data, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void build_crc_table(int64_t* table) {
    int64_t poly = 3988292384LL;  // 0xEDB88320
    int64_t mask32 = 4294967295LL;  // 0xFFFFFFFF
    for (int64_t i = 0; i < 256; i++) {
        int64_t crc = i;
        for (int64_t j = 0; j < 8; j++) {
            if ((crc & 1) == 1) {
                crc = (crc >> 1) ^ poly;
            } else {
                crc = crc >> 1;
            }
        }
        table[i] = crc & mask32;
    }
}

static int64_t crc32_compute(int64_t* table, int64_t* data, int64_t len) {
    int64_t mask32 = 4294967295LL;  // 0xFFFFFFFF
    int64_t crc = mask32;
    for (int64_t i = 0; i < len; i++) {
        int64_t val = data[i];
        // Extract 4 bytes from each i64 value
        int64_t b0 = val & 255;
        int64_t b1 = (val >> 8) & 255;
        int64_t b2 = (val >> 16) & 255;
        int64_t b3 = (val >> 24) & 255;
        // Process byte 0
        int64_t idx0 = (crc ^ b0) & 255;
        crc = (crc >> 8) ^ table[idx0];
        crc = crc & mask32;
        // Process byte 1
        int64_t idx1 = (crc ^ b1) & 255;
        crc = (crc >> 8) ^ table[idx1];
        crc = crc & mask32;
        // Process byte 2
        int64_t idx2 = (crc ^ b2) & 255;
        crc = (crc >> 8) ^ table[idx2];
        crc = crc & mask32;
        // Process byte 3
        int64_t idx3 = (crc ^ b3) & 255;
        crc = (crc >> 8) ^ table[idx3];
        crc = crc & mask32;
    }
    return crc ^ mask32;
}

int main() {
    int64_t data_len = 262144;  // 256K entries * 4 bytes each = 1MB processed
    int64_t iters = 500;
    int64_t* table = (int64_t*)malloc(256 * sizeof(int64_t));
    build_crc_table(table);
    int64_t* data = (int64_t*)malloc(data_len * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        // Fill data with pseudo-random values
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < data_len; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            data[i] = seed;
        }
        int64_t crc = crc32_compute(table, data, data_len);
        checksum += crc;
    }

    printf("%lld\n", (long long)checksum);
    free(table);
    free(data);
    return 0;
}
