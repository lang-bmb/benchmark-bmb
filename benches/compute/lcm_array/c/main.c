// LCM Array — compute LCM of all elements using GCD
// Measures: modulo, multiplication, data-dependent iteration
// Workload: N=100000, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t gcd(int64_t a, int64_t b) {
    while (b != 0) { int64_t t = b; b = a % b; a = t; }
    return a;
}

int64_t lcm(int64_t a, int64_t b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    int64_t N = 100000;
    int64_t ITERS = 5000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t modp = 1000000007;

    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        arr[i] = (seed % 100) + 1;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t result = arr[0];
        for (int64_t i = 1; i < N; i++) {
            result = lcm(result, arr[i]);
            result %= modp;
        }
        checksum = (checksum + result) % modp;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
