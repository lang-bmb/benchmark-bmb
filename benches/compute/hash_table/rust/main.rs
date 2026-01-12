// Hash Table benchmark - Rust implementation
// Measures: HashMap insert, lookup, and delete operations

use std::collections::HashMap;

const N: i64 = 100000;

fn random_next(seed: i64) -> i64 {
    (seed.wrapping_mul(1103515245).wrapping_add(12345)) % 2147483648
}

fn benchmark_insert(m: &mut HashMap<i64, i64>, n: i64, mut seed: i64) -> i64 {
    for _ in 0..n {
        let key = seed % 1000000;
        let value = key * 7;
        m.insert(key, value);
        seed = random_next(seed);
    }
    seed
}

fn benchmark_lookup(m: &HashMap<i64, i64>, n: i64, mut seed: i64) -> i64 {
    let mut found = 0;
    for _ in 0..n {
        let key = seed % 1000000;
        if m.get(&key).is_some() {
            found += 1;
        }
        seed = random_next(seed);
    }
    found
}

fn benchmark_delete(m: &mut HashMap<i64, i64>, n: i64, mut seed: i64) -> i64 {
    let mut deleted = 0;
    for _ in 0..n {
        let key = seed % 1000000;
        if m.remove(&key).is_some() {
            deleted += 1;
        }
        seed = random_next(seed);
    }
    deleted
}

fn main() {
    let seed: i64 = 42;

    let mut m: HashMap<i64, i64> = HashMap::new();

    // Phase 1: Insert operations
    let _seed1 = benchmark_insert(&mut m, N, seed);
    let len1 = m.len() as i64;
    println!("{}", len1);

    // Phase 2: Lookup operations (same seed = same keys)
    let found = benchmark_lookup(&m, N, seed);
    println!("{}", found);

    // Phase 3: Delete half the entries (different seed)
    let _deleted = benchmark_delete(&mut m, N / 2, random_next(seed));
    let len2 = m.len() as i64;
    println!("{}", len2);

    // Return value (implicit)
}
