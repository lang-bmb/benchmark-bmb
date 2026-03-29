#include <stdint.h>

int64_t get_threshold(int64_t config_id) {
    int64_t h = config_id * 2654435761LL;
    for (int i = 0; i < 30; i++) {
        h = h ^ (h >> 16);
        h = h * 2246822507LL;
        h = h ^ (h >> 13);
        h = h * 3266489917LL;
        h = h ^ (h >> 16);
    }
    return (h & 255) + 1;
}

int64_t get_scale_factor(int64_t mode) {
    int64_t s = mode;
    for (int i = 0; i < 20; i++) {
        s = (s * 48271) & 2147483647LL;
    }
    return (s & 15) + 1;
}
