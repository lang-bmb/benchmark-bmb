// Division-by-Zero Check - C baseline
// C has no contract system, must check manually or not at all
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t safe_div(int64_t a, int64_t b) {
    if (b == 0) { fprintf(stderr, "divzero\n"); exit(1); }
    return a / b;
}

static int64_t safe_mod(int64_t a, int64_t b) {
    if (b == 0) { fprintf(stderr, "divzero\n"); exit(1); }
    return a % b;
}

static int64_t div_chain(int64_t x, int64_t d) {
    int64_t a = safe_div(x, d);
    int64_t b = safe_mod(x, d);
    int64_t c = safe_div(a + b, d);
    return c;
}

int main(void) {
    int64_t acc = 0;
    for (int64_t n = 1000000; n > 0; n--) {
        acc += div_chain(n * 100 + 42, 7);
    }
    printf("%lld\n", (long long)acc);
    return 0;
}
