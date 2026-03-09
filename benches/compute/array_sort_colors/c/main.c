// Array Sort Colors — counting sort for 3 values (0, 1, 2)
// Measures: register carry (c0, c1, c2 counts), sequential fill
// Workload: N=2000000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate array of 0,1,2
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 3;
        }

        // Count occurrences
        int64_t c0 = 0, c1 = 0, c2 = 0;
        for (int64_t i = 0; i < N; i++) {
            if (arr[i] == 0) c0++;
            else if (arr[i] == 1) c1++;
            else c2++;
        }

        // Fill array
        int64_t idx = 0;
        for (int64_t i = 0; i < c0; i++) arr[idx++] = 0;
        for (int64_t i = 0; i < c1; i++) arr[idx++] = 1;
        for (int64_t i = 0; i < c2; i++) arr[idx++] = 2;

        checksum += c0 + c1 * 2 + c2 * 3;
        checksum += arr[0] + arr[N/2] + arr[N-1];
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
