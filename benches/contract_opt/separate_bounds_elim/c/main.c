// C: No purity info → must call hash_key every iteration
// Even with the body visible, C compiler may not hoist all three calls.

#include <stdio.h>
#include <stdint.h>

// Separate compilation unit — no body visible
extern int64_t hash_key(int64_t key);

int main() {
    int64_t total = 0;
    for (int64_t i = 0; i < 20000000; i++) {
        total += hash_key(100) + hash_key(200) + hash_key(300);
    }
    printf("%lld\n", (long long)total);
    return 0;
}
