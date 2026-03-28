// Purity optimization benchmark (C version)
// C compiler can analyze purity through interprocedural analysis
// when everything is in one file — this is a fair comparison

#include <stdio.h>
#include <stdint.h>

int64_t expensive_pure(int64_t x) {
    int64_t acc = 1;
    for (int64_t i = 0; i < x; i++) {
        int64_t term = (i * i) / (i + 1);
        int64_t extra = (i > 5) ? (i * 3 + 7) / (i + 2) : i + 1;
        acc += term + extra;
    }
    return acc;
}

int64_t compute_with_redundancy(int64_t x) {
    int64_t a = expensive_pure(x);
    int64_t b = expensive_pure(x);
    int64_t c = expensive_pure(x);
    return a + b + c;
}

int64_t loop_with_invariant(int64_t n, int64_t constant) {
    int64_t acc = 0;
    for (int64_t i = 0; i < n; i++) {
        int64_t pure_result = expensive_pure(constant);
        acc += pure_result;
    }
    return acc;
}

int main() {
    int64_t pure_test = 0;
    for (int64_t n = 100000; n > 0; n--) {
        pure_test += compute_with_redundancy(n / 100);
    }

    int64_t loop_test = loop_with_invariant(100000, 50);

    printf("%lld\n", (long long)(pure_test + loop_test));
    return 0;
}
