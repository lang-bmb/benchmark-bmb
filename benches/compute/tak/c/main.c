// Takeuchi Function (TAK) Benchmark
// Measures: recursion, function call overhead

#include <stdio.h>
#include <stdint.h>

int64_t tak(int64_t x, int64_t y, int64_t z) {
    if (y >= x) return z;
    return tak(
        tak(x - 1, y, z),
        tak(y - 1, z, x),
        tak(z - 1, x, y)
    );
}

int main() {
    // 50000 iterations for stable measurement (target: ~150ms after LICM)
    int64_t result = 0;
    for (int i = 0; i < 50000; i++) {
        result += tak(24, 16, 8);
    }
    printf("%lld\n", (long long)result);
    return 0;
}
