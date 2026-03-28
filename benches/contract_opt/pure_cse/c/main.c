// Pure CSE Benchmark — C version (no contract optimization)
// C has no way to declare function purity for noinline functions
// All 3 calls in triple_hash MUST execute; loop_hash cannot hoist

#include <stdio.h>
#include <stdint.h>

// Library function: pure but noinline — C cannot detect purity of recursive functions
__attribute__((noinline))
int64_t compute_hash_iter(int64_t seed, int64_t data, int64_t i, int64_t acc) {
    if (i >= 100) return acc;
    int64_t step1 = acc + data + i * seed;
    int64_t next = (step1 * 31 + 17) % 1000000007;
    return compute_hash_iter(seed, data, i + 1, next);
}

__attribute__((noinline))
int64_t compute_hash(int64_t seed, int64_t data) {
    return compute_hash_iter(seed, data, 0, seed);
}

// Pattern 1: Triple redundant call — C must call all 3
int64_t triple_hash(int64_t seed, int64_t data) {
    int64_t h1 = compute_hash(seed, data);
    int64_t h2 = compute_hash(seed, data);
    int64_t h3 = compute_hash(seed, data);
    return h1 + h2 + h3;
}

// Pattern 2: Loop with invariant — C cannot hoist
int64_t loop_hash(int64_t n, int64_t seed, int64_t data) {
    int64_t acc = 0;
    for (int64_t i = 0; i < n; i++) {
        acc += compute_hash(seed, data);
    }
    return acc;
}

int main() {
    int64_t acc = 0;
    for (int64_t n = 100000; n > 0; n--) {
        int64_t seed = (n % 50) + 1;
        int64_t data = (n % 100) + 1;
        // 10 redundant calls — C must execute all 10
        int64_t h1 = compute_hash(seed, data);
        int64_t h2 = compute_hash(seed, data);
        int64_t h3 = compute_hash(seed, data);
        int64_t h4 = compute_hash(seed, data);
        int64_t h5 = compute_hash(seed, data);
        int64_t h6 = compute_hash(seed, data);
        int64_t h7 = compute_hash(seed, data);
        int64_t h8 = compute_hash(seed, data);
        int64_t h9 = compute_hash(seed, data);
        int64_t h10 = compute_hash(seed, data);
        acc += h1+h2+h3+h4+h5+h6+h7+h8+h9+h10;
    }
    printf("%lld\n", (long long)acc);
    return 0;
}
