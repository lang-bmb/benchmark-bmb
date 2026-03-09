// Array Unique Count — count unique elements using sorted scan
// Measures: sorting (insertion sort on small arrays), sequential comparison
// Workload: N=5000, 50000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 5000;
    int64_t ITERS = 50000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* tmp = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % (N * 2);
        }

        for (int64_t i = 0; i < N; i++) tmp[i] = arr[i];

        // Insertion sort
        for (int64_t i = 1; i < N; i++) {
            int64_t key = tmp[i];
            int64_t j = i - 1;
            while (j >= 0 && tmp[j] > key) {
                tmp[j + 1] = tmp[j];
                j--;
            }
            tmp[j + 1] = key;
        }

        int64_t unique = 1;
        for (int64_t i = 1; i < N; i++) {
            if (tmp[i] != tmp[i - 1]) unique++;
        }
        checksum += unique;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    free(tmp);
    return 0;
}
