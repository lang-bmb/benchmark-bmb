#include <stdio.h>
#include <stdint.h>

extern int64_t expensive_lookup(int64_t key);

int main() {
    int64_t key = 42;
    int64_t total = 0;
    // Cannot hoist expensive_lookup(key) out of loop — no purity info
    for (int64_t i = 0; i < 50000000; i++) {
        total += expensive_lookup(key) + i;
    }
    printf("%lld\n", (long long)total);
    return 0;
}
