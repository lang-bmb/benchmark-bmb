// Ackermann Function Benchmark - LICM Equivalent
// Manual application of Loop-Invariant Code Motion
// This is what LLVM does automatically for BMB

#include <stdio.h>
#include <stdint.h>

int64_t ackermann(int64_t m, int64_t n) {
    if (m == 0) return n + 1;
    if (n == 0) return ackermann(m - 1, 1);
    return ackermann(m - 1, ackermann(m, n - 1));
}

int main() {
    // LLVM optimization: hoist constant call out of loop
    // and use multiplication instead of repeated addition
    int64_t single_result = ackermann(3, 10);
    int64_t result = single_result * 1000;  // Strength reduction

    printf("%lld\n", (long long)result);
    return 0;
}
