// Range Narrowing - C baseline
// C compiler may or may not narrow range without explicit hints
#include <stdio.h>
#include <stdint.h>

static int64_t to_byte(int64_t x) {
    if (x < 0) return 0;
    if (x >= 256) return 255;
    return x;
}

static int64_t process_pixel(int64_t r, int64_t g, int64_t b) {
    int64_t rr = to_byte(r);
    int64_t gg = to_byte(g);
    int64_t bb = to_byte(b);
    return rr * 65536 + gg * 256 + bb;
}

int main(void) {
    int64_t acc = 0;
    for (int64_t n = 1000000; n > 0; n--) {
        acc += process_pixel(n % 300, n % 500, n % 700);
    }
    printf("%lld\n", (long long)acc);
    return 0;
}
