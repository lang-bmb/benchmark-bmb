#include <stdio.h>
#include <stdint.h>

extern int64_t expensive_validate(int64_t x);

int main() {
    int64_t total = 0;
    for (int64_t i = 0; i < 10000000; i++) {
        int64_t val = expensive_validate(i);
        total += val;
        // Unused call — compiler CANNOT eliminate (might have side effects)
        expensive_validate(i + 1);
    }
    printf("%lld\n", (long long)total);
    return 0;
}
