#include <stdint.h>

int64_t expensive_lookup(int64_t key) {
    int64_t h = key;
    for (int i = 0; i < 50; i++) {
        h = h ^ (h << 13);
        h = h ^ (h >> 7);
        h = h ^ (h << 17);
    }
    return h & 255;
}
