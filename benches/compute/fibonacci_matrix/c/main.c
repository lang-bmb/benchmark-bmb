// Fibonacci Matrix — compute Fibonacci via 2x2 matrix exponentiation
// Measures: multiply, modulo, binary exponentiation
// Workload: fib(10^18 mod 10^9+7), 5000000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct { int64_t m[2][2]; } Mat;

Mat mat_mul(Mat a, Mat b, int64_t mod) {
    Mat c;
    c.m[0][0] = (a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0]) % mod;
    c.m[0][1] = (a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1]) % mod;
    c.m[1][0] = (a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0]) % mod;
    c.m[1][1] = (a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1]) % mod;
    return c;
}

int64_t fib_mod(int64_t n, int64_t mod) {
    if (n <= 1) return n % mod;
    Mat result = {{{1, 0}, {0, 1}}};
    Mat base = {{{1, 1}, {1, 0}}};
    int64_t e = n;
    while (e > 0) {
        if (e & 1) result = mat_mul(result, base, mod);
        base = mat_mul(base, base, mod);
        e >>= 1;
    }
    return result.m[0][1];
}

int main() {
    int64_t ITERS = 5000000;
    int64_t mod = 1000000007;
    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t n = 1000000000000000000LL + iter;
        checksum = (checksum + fib_mod(n, mod)) % mod;
    }
    printf("%lld\n", (long long)checksum);
    return 0;
}
