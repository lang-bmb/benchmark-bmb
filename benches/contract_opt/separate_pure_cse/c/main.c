// Separate compilation benchmark: No purity info across units
// Without LTO, compiler cannot know compute_heavy() is pure.
// Each call must be made — no CSE possible.

#include <stdio.h>
#include <stdint.h>

// Forward declaration — no purity info available
extern int64_t compute_heavy(int64_t x);

int main() {
    int64_t total = 0;
    for (int64_t i = 0; i < 10000000; i++) {
        // Two calls with same argument — compiler CANNOT CSE without LTO
        int64_t a = compute_heavy(42);
        int64_t b = compute_heavy(42);
        total += a + b;
    }
    printf("%lld\n", (long long)total);
    return 0;
}
