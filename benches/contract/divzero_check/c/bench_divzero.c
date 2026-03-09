// Division Check Benchmark - C equivalent of BMB contract benchmark
// C with manual divzero checking (equivalent to --safe, no contract)
#include <stdio.h>
#include <stdlib.h>

typedef long long i64;

__attribute__((noinline)) static i64 safe_div(i64 a, i64 b) {
    if (b == 0) { fprintf(stderr, "divzero\n"); exit(1); }
    return a / b;
}

__attribute__((noinline)) static i64 safe_mod(i64 a, i64 b) {
    if (b == 0) { fprintf(stderr, "divzero\n"); exit(1); }
    return a % b;
}

__attribute__((noinline)) static i64 unchecked_div(i64 a, i64 b) { return a / b; }
__attribute__((noinline)) static i64 unchecked_mod(i64 a, i64 b) { return a % b; }

static i64 get_divisor(i64 n) {
    i64 r = n % 7;
    return (r == 0) ? 1 : r;
}

static i64 div_chain_checked(i64 x, i64 d) {
    i64 a = safe_div(x, d);
    i64 b = safe_mod(x, d);
    return safe_div(a + b, d);
}

static i64 div_chain_unchecked(i64 x, i64 d) {
    i64 a = unchecked_div(x, d);
    i64 b = unchecked_mod(x, d);
    return unchecked_div(a + b, d);
}

int main(int argc, char** argv) {
    int checked = (argc > 1 && argv[1][0] == 'c');
    i64 acc = 0;
    for (i64 n = 100000000; n > 0; n--) {
        i64 d = get_divisor(n);
        i64 r;
        if (checked) {
            r = div_chain_checked(n * 100 + 42, d);
        } else {
            r = div_chain_unchecked(n * 100 + 42, d);
        }
        acc += r;
    }
    printf("%lld\n", acc);
    return 0;
}
