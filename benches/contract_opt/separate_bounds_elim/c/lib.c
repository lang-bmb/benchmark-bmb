#include <stdint.h>

int64_t hash_key(int64_t key) {
    int64_t h = key;
    for (int i = 0; i < 80; i++) {
        h = h ^ (h << 13);
        h = h ^ (h >> 7);
        h = h ^ (h << 17);
        h = h & 1073741823;
    }
    return h;
}
