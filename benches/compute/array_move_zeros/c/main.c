// Array Move Zeros — move all zeros to end maintaining order
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
        // Generate array with ~20% zeros
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 5; // 0..4, ~20% zeros
        }

        // Move zeros to end, maintain order of non-zeros
        int64_t write_pos = 0;
        for (int64_t i = 0; i < N; i++) {
            if (arr[i] != 0) {
                arr[write_pos] = arr[i];
                write_pos++;
            }
        }
        // Fill remaining with zeros
        for (int64_t i = write_pos; i < N; i++) {
            arr[i] = 0;
        }

        checksum += write_pos;
        checksum += arr[0] + arr[N/2] + arr[N-1];
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
