// Hash Table benchmark - C implementation
// Measures: hash table insert, lookup, and delete operations
// Uses simple open-addressing with linear probing

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define N 100000
#define TABLE_SIZE 131072  // Power of 2, > 1.3 * N

typedef struct {
    int64_t key;
    int64_t value;
    int state;  // 0=empty, 1=occupied, 2=deleted
} Entry;

typedef struct {
    Entry* entries;
    int64_t count;
    int64_t capacity;
} HashMap;

// v0.60.58: Added static inline for fair comparison with BMB's @inline
static inline int64_t random_next(int64_t seed) {
    return (seed * 1103515245 + 12345) % 2147483648;
}

// v0.60.51: Match BMB's hash behavior exactly
// - Unsigned multiplication (wrapping semantics)
// - Signed shift (arithmetic right shift)
// v0.60.58: Added static inline for fair comparison
static inline int64_t hash_i64(int64_t key) {
    uint64_t mul = (uint64_t)key * 0x517cc1b727220a95ULL;
    int64_t h = (int64_t)mul;
    return h ^ (h >> 32);
}

HashMap* hashmap_new(void) {
    HashMap* m = (HashMap*)malloc(sizeof(HashMap));
    m->entries = (Entry*)calloc(TABLE_SIZE, sizeof(Entry));
    m->count = 0;
    m->capacity = TABLE_SIZE;
    return m;
}

void hashmap_free(HashMap* m) {
    free(m->entries);
    free(m);
}

int64_t hashmap_insert(HashMap* m, int64_t key, int64_t value) {
    int64_t hash = hash_i64(key);
    int64_t mask = m->capacity - 1;
    int64_t idx = hash & mask;

    for (int64_t i = 0; i < m->capacity; i++) {
        Entry* e = &m->entries[idx];
        if (e->state == 0 || e->state == 2) {
            e->key = key;
            e->value = value;
            e->state = 1;
            m->count++;
            return 0;
        } else if (e->state == 1 && e->key == key) {
            int64_t old = e->value;
            e->value = value;
            return old;
        }
        idx = (idx + 1) & mask;
    }
    return 0;
}

int64_t hashmap_get(HashMap* m, int64_t key) {
    int64_t hash = hash_i64(key);
    int64_t mask = m->capacity - 1;
    int64_t idx = hash & mask;

    for (int64_t i = 0; i < m->capacity; i++) {
        Entry* e = &m->entries[idx];
        if (e->state == 0) {
            return INT64_MIN;
        } else if (e->state == 1 && e->key == key) {
            return e->value;
        }
        idx = (idx + 1) & mask;
    }
    return INT64_MIN;
}

int64_t hashmap_remove(HashMap* m, int64_t key) {
    int64_t hash = hash_i64(key);
    int64_t mask = m->capacity - 1;
    int64_t idx = hash & mask;

    for (int64_t i = 0; i < m->capacity; i++) {
        Entry* e = &m->entries[idx];
        if (e->state == 0) {
            return INT64_MIN;
        } else if (e->state == 1 && e->key == key) {
            int64_t old = e->value;
            e->state = 2;
            m->count--;
            return old;
        }
        idx = (idx + 1) & mask;
    }
    return INT64_MIN;
}

int64_t benchmark_insert(HashMap* m, int64_t n, int64_t seed) {
    for (int64_t i = 0; i < n; i++) {
        int64_t key = seed % 1000000;
        int64_t value = key * 7;
        hashmap_insert(m, key, value);
        seed = random_next(seed);
    }
    return seed;
}

int64_t benchmark_lookup(HashMap* m, int64_t n, int64_t seed) {
    int64_t found = 0;
    for (int64_t i = 0; i < n; i++) {
        int64_t key = seed % 1000000;
        if (hashmap_get(m, key) != INT64_MIN) {
            found++;
        }
        seed = random_next(seed);
    }
    return found;
}

int64_t benchmark_delete(HashMap* m, int64_t n, int64_t seed) {
    int64_t deleted = 0;
    for (int64_t i = 0; i < n; i++) {
        int64_t key = seed % 1000000;
        if (hashmap_remove(m, key) != INT64_MIN) {
            deleted++;
        }
        seed = random_next(seed);
    }
    return deleted;
}

int main(void) {
    int64_t seed = 42;
    int64_t total_found = 0;

    // 30 iterations for stable measurement (target: ~125ms)
    for (int iter = 0; iter < 30; iter++) {
        HashMap* m = hashmap_new();
        benchmark_insert(m, N, seed);
        total_found += benchmark_lookup(m, N, seed);
        benchmark_delete(m, N / 2, random_next(seed));
        hashmap_free(m);
    }

    // Print final results (from one more iteration)
    HashMap* m = hashmap_new();

    // Phase 1: Insert operations
    benchmark_insert(m, N, seed);
    printf("%lld\n", (long long)m->count);

    // Phase 2: Lookup operations (same seed = same keys)
    int64_t found = benchmark_lookup(m, N, seed);
    printf("%lld\n", (long long)found);

    // Phase 3: Delete half the entries (different seed)
    benchmark_delete(m, N / 2, random_next(seed));
    printf("%lld\n", (long long)m->count);

    hashmap_free(m);

    return 0;
}
