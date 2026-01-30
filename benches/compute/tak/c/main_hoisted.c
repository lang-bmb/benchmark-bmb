// Takeuchi Function Benchmark - LICM Equivalent
// Manual application of Loop-Invariant Code Motion

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
    // LICM: hoist constant call and multiply
    int64_t single_result = tak(24, 16, 8);
    int64_t result = single_result * 10;

    printf("%lld\n", (long long)result);
    return 0;
}
