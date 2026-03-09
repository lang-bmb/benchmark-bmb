// Array Remove Element — remove all occurrences of val, return new length
// Measures: two-pointer, register carry (write_pos)
// Workload: N=2000000, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 1000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate array with values 0..9
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10;
        }

        // Remove all occurrences of val=3
        int64_t val = 3;
        int64_t write_pos = 0;
        for (int64_t i = 0; i < N; i++) {
            if (arr[i] != val) {
                arr[write_pos] = arr[i];
                write_pos++;
            }
        }

        checksum += write_pos;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
