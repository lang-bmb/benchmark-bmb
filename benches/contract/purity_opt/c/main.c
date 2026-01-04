// Purity optimization benchmark (C version - no automatic CSE)
// Compiler may optimize some cases, but not as reliably as contract-based

#include <stdio.h>

long expensive_pure(long x) {
    long acc = 1;
    for (long i = 0; i < x; i++) {
        acc += (i * i) / (i + 1);
    }
    return acc;
}

long compute_with_redundancy(long x) {
    long a = expensive_pure(x);  // First call
    long b = expensive_pure(x);  // Compiler may or may not eliminate
    long c = expensive_pure(x);  // Compiler may or may not eliminate
    return a + b + c;
}

long loop_with_invariant(long n, long constant) {
    long acc = 0;
    for (long i = 0; i < n; i++) {
        // Loop invariant - compiler may or may not hoist
        long pure_result = expensive_pure(constant);
        acc += pure_result;
    }
    return acc;
}

int main() {
    long pure_test = 0;
    for (int n = 1000; n > 0; n--) {
        pure_test += compute_with_redundancy(n / 10);
    }

    long loop_test = loop_with_invariant(1000, 50);

    printf("%ld\n", pure_test + loop_test);
    return 0;
}
