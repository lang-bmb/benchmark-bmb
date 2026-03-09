// Hash Table Benchmark
// Measures: hash function, array access, collision handling
// Uses simple open-addressing with linear probing (matches C version)

const N: i64 = 100000;
const TABLE_SIZE: usize = 131072; // Power of 2, > 1.3 * N

#[derive(Clone, Copy)]
struct Entry {
    key: i64,
    value: i64,
    state: i32, // 0=empty, 1=occupied, 2=deleted
}

struct HashMap {
    entries: Vec<Entry>,
    count: i64,
}

#[inline]
fn random_next(seed: i64) -> i64 {
    (seed * 1103515245 + 12345) % 2147483648
}

#[inline]
fn hash_i64(key: i64) -> i64 {
    let mul = (key as u64).wrapping_mul(0x517cc1b727220a95u64);
    let h = mul as i64;
    h ^ (h >> 32)
}

impl HashMap {
    fn new() -> Self {
        HashMap {
            entries: vec![Entry { key: 0, value: 0, state: 0 }; TABLE_SIZE],
            count: 0,
        }
    }

    fn insert(&mut self, key: i64, value: i64) -> i64 {
        let hash = hash_i64(key);
        let mask = (TABLE_SIZE as i64) - 1;
        let mut idx = (hash & mask) as usize;

        for _ in 0..TABLE_SIZE {
            let e = &self.entries[idx];
            if e.state == 0 || e.state == 2 {
                self.entries[idx] = Entry { key, value, state: 1 };
                self.count += 1;
                return 0;
            } else if e.state == 1 && e.key == key {
                let old = self.entries[idx].value;
                self.entries[idx].value = value;
                return old;
            }
            idx = (idx + 1) & (mask as usize);
        }
        0
    }

    fn get(&self, key: i64) -> Option<i64> {
        let hash = hash_i64(key);
        let mask = (TABLE_SIZE as i64) - 1;
        let mut idx = (hash & mask) as usize;

        for _ in 0..TABLE_SIZE {
            let e = &self.entries[idx];
            if e.state == 0 {
                return None;
            } else if e.state == 1 && e.key == key {
                return Some(e.value);
            }
            idx = (idx + 1) & (mask as usize);
        }
        None
    }

    fn remove(&mut self, key: i64) -> Option<i64> {
        let hash = hash_i64(key);
        let mask = (TABLE_SIZE as i64) - 1;
        let mut idx = (hash & mask) as usize;

        for _ in 0..TABLE_SIZE {
            let e = &self.entries[idx];
            if e.state == 0 {
                return None;
            } else if e.state == 1 && e.key == key {
                let old = self.entries[idx].value;
                self.entries[idx].state = 2;
                self.count -= 1;
                return Some(old);
            }
            idx = (idx + 1) & (mask as usize);
        }
        None
    }
}

fn benchmark_insert(m: &mut HashMap, n: i64, mut seed: i64) -> i64 {
    for _ in 0..n {
        let key = seed % 1000000;
        let value = key * 7;
        m.insert(key, value);
        seed = random_next(seed);
    }
    seed
}

fn benchmark_lookup(m: &HashMap, n: i64, mut seed: i64) -> i64 {
    let mut found: i64 = 0;
    for _ in 0..n {
        let key = seed % 1000000;
        if m.get(key).is_some() {
            found += 1;
        }
        seed = random_next(seed);
    }
    found
}

fn benchmark_delete(m: &mut HashMap, n: i64, mut seed: i64) -> i64 {
    let mut deleted: i64 = 0;
    for _ in 0..n {
        let key = seed % 1000000;
        if m.remove(key).is_some() {
            deleted += 1;
        }
        seed = random_next(seed);
    }
    deleted
}

fn main() {
    let seed: i64 = 42;
    let mut total_found: i64 = 0;

    // 30 iterations for stable measurement
    for _ in 0..30 {
        let mut m = HashMap::new();
        benchmark_insert(&mut m, N, seed);
        total_found += benchmark_lookup(&m, N, seed);
        benchmark_delete(&mut m, N / 2, random_next(seed));
    }

    // Print final results (from one more iteration)
    let mut m = HashMap::new();

    // Phase 1: Insert operations
    benchmark_insert(&mut m, N, seed);
    println!("{}", m.count);

    // Phase 2: Lookup operations (same seed = same keys)
    let found = benchmark_lookup(&m, N, seed);
    println!("{}", found);

    // Phase 3: Delete half the entries (different seed)
    benchmark_delete(&mut m, N / 2, random_next(seed));
    println!("{}", m.count);
}
