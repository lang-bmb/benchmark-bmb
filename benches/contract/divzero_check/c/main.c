// Division-by-Zero Check - C baseline
// C has no contract system, must check manually or not at all
#include <stdio.h>
#include <stdlib.h>

static long safe_div(long a, long b) {
    if (b == 0) { fprintf(stderr, "divzero\n"); exit(1); }
    return a / b;
}

static long safe_mod(long a, long b) {
    if (b == 0) { fprintf(stderr, "divzero\n"); exit(1); }
    return a % b;
}

static long div_chain(long x, long d) {
    long a = safe_div(x, d);
    long b = safe_mod(x, d);
    long c = safe_div(a + b, d);
    return c;
}

int main(void) {
    long acc = 0;
    for (long n = 1000000; n > 0; n--) {
        acc += div_chain(n * 100 + 42, 7);
    }
    printf("%ld\n", acc);
    return 0;
}
