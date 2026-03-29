#include <stdint.h>

int64_t expensive_validate(int64_t x) {
    int64_t h = x;
    for (int i = 0; i < 200; i++) {
        h = ((h * 6364136223846793005LL + 1442695040888963407LL) >> 33) & 2147483647LL;
    }
    return h;
}
