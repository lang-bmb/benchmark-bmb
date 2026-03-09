// Range Narrowing - C baseline
// C compiler may or may not narrow range without explicit hints
#include <stdio.h>

static long long to_byte(long long x) {
    if (x < 0) return 0;
    if (x >= 256) return 255;
    return x;
}

static long long process_pixel(long long r, long long g, long long b) {
    long long rr = to_byte(r);
    long long gg = to_byte(g);
    long long bb = to_byte(b);
    return rr * 65536 + gg * 256 + bb;
}

int main(void) {
    long long acc = 0;
    for (long long n = 1000000; n > 0; n--) {
        acc += process_pixel(n % 300, n % 500, n % 700);
    }
    printf("%lld\n", acc);
    return 0;
}
