#include <stdio.h>
#include <stdint.h>

extern int64_t get_threshold(int64_t config_id);
extern int64_t get_scale_factor(int64_t mode);

int main() {
    int64_t total = 0;
    for (int64_t i = 0; i < 100000000; i++) {
        int64_t threshold = get_threshold(7);
        int64_t scale = get_scale_factor(3);
        total += (i & threshold) * scale;
    }
    printf("%lld\n", (long long)total);
    return 0;
}
