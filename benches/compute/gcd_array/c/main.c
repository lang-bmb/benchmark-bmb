// GCD Array — compute GCD of entire array using Euclidean algorithm
// Measures: integer arithmetic, branch prediction, sequential access
// Workload: N=100000 array, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t gcd(int64_t a, int64_t b) {
    while (b != 0) {
        int64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

static int64_t gcd_array(const int64_t* arr, int64_t n) {
    int64_t result = arr[0];
    for (int64_t i = 1; i < n; i++) {
        result = gcd(result, arr[i]);
        if (result == 1) return 1;
    }
    return result;
}

int main() {
    int64_t N = 100000;
    int64_t ITERS = 10000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = (seed % 1000000) + 1;
        }
        checksum += gcd_array(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
