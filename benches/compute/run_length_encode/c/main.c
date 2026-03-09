// Run-Length Encoding — encode + decode cycle
// Measures: sequential scan, conditional grouping
// Workload: N=200K elements, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 200000;
    int64_t ITERS = 500;
    // Encode buffer: pairs of (value, count), worst case N pairs
    int64_t* data = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* enc_val = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* enc_cnt = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* decoded = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate random data with many runs (values 0-4)
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            data[i] = seed % 5;
        }

        // Encode: compress runs into (value, count) pairs
        int64_t enc_len = 0;
        int64_t run_val = data[0];
        int64_t run_cnt = 1;
        for (int64_t i = 1; i < N; i++) {
            if (data[i] == run_val) {
                run_cnt++;
            } else {
                enc_val[enc_len] = run_val;
                enc_cnt[enc_len] = run_cnt;
                enc_len++;
                run_val = data[i];
                run_cnt = 1;
            }
        }
        // Flush last run
        enc_val[enc_len] = run_val;
        enc_cnt[enc_len] = run_cnt;
        enc_len++;

        // Decode: expand back to original array
        int64_t pos = 0;
        for (int64_t i = 0; i < enc_len; i++) {
            int64_t v = enc_val[i];
            int64_t c = enc_cnt[i];
            for (int64_t j = 0; j < c; j++) {
                decoded[pos] = v;
                pos++;
            }
        }

        checksum += decoded[0] + decoded[N - 1] + enc_len;
    }

    printf("%lld\n", (long long)checksum);
    free(data);
    free(enc_val);
    free(enc_cnt);
    free(decoded);
    return 0;
}
