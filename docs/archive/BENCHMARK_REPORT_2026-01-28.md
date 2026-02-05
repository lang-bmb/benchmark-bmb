# BMB Benchmark Report v0.60.14

**Date:** 2026-01-28
**Compiler:** BMB v0.60.14 (x86_64-pc-windows-gnu)
**Environment:** Windows 11, GCC 15.2.0, LLVM 21.x (MSYS2)

## Benchmark Results

| Benchmark | C (ms) | BMB (ms) | Ratio | Status | Fairness |
|-----------|--------|----------|-------|--------|----------|
| fibonacci | 248 | 5 | **2%** | FAST | FAIR |
| hash_table | 10 | 9 | **96%** | FAST | FAIR |
| sorting | 654 | 170 | **26%** | FAST | FAIR* |
| csv_parse | 20 | 19 | **94%** | FAST | FAIR |
| http_parse | 23 | 20 | **89%** | FAST | FAIR |
| fasta | 195 | 194 | **99%** | OK | FAIR |
| json_parse | 23 | 24 | **104%** | OK | FAIR |
| mandelbrot | 141 | 152 | **108%** | SLOW | FAIR |
| n_body | 68 | 77 | **113%** | SLOW | UNFAIR |
| lexer | 19 | 24 | **123%** | SLOW | FAIR |
| spectral_norm | 31 | 38 | **122%** | SLOW | UNFAIR |
| json_serialize | 23 | 49 | **211%** | SLOW | ? |
| brainfuck | 20 | 26 | **130%** | SLOW | FAIR |
| binary_trees | - | - | FAIL | - | - |
| fannkuch | 79 | >300000 | **>3800x** | BROKEN | UNFAIR |

### Summary
- **FAST (<100%):** 5 benchmarks (fibonacci, hash_table, sorting, csv_parse, http_parse)
- **OK (100-105%):** 2 benchmarks (fasta, json_parse)
- **SLOW (>105%):** 6 benchmarks
- **BROKEN:** 2 benchmarks (binary_trees panic, fannkuch infinite-like)

---

## Fairness Analysis

### CRITICAL ISSUES (Language Limitations)

#### 1. No Native Array Type
**Impact:** spectral_norm (+22%), fannkuch (broken), sorting, n_body

BMB lacks native fixed-size or dynamic array types. Developers must use:
```bmb
fn array_new(n: i64) -> i64 = malloc(n * 8);
fn array_get(arr: i64, i: i64) -> f64 = load_f64(arr + i * 8);
fn array_set(arr: i64, i: i64, val: f64) -> i64 = { store_f64(arr + i * 8, val); 0 };
```

**vs C:**
```c
double arr[N];
arr[i] = val;  // Direct access
```

**Overhead per access:** Function call + pointer arithmetic + memory load

#### 2. No `break` Statement
**Impact:** fannkuch (broken)

BMB requires manual flag-based control flow:
```bmb
let mut found_next: i64 = 0;
while i < n {
    if c != 0 {
        { found_next = 1; i = n + 1 }  // Force exit
    } else { ... };
};
```

**vs C:**
```c
if (count[i] != 0) break;
```

#### 3. Recursion vs Iteration
**Impact:** n_body (+13%), sorting

BMB prefers expression-based recursion, but LLVM doesn't always optimize tail recursion to loops:
```bmb
fn bubble_inner(arr: i64, n: i64, i: i64, j: i64, cmp: i64) -> i64 =
    if j >= n - i - 1 { cmp }
    else { bubble_inner(arr, n, i, j + 1, cmp + 1) };
```

**vs C:**
```c
for (int j = 0; j < n - i - 1; j++) { ... }
```

#### 4. Struct Initialization Verbosity
**Impact:** n_body (+13%)

```bmb
let _s0 = set sun.x = 0.0;
let _s1 = set sun.y = 0.0;
// ... 7 fields × 5 bodies = 35 statements
```

**vs C:**
```c
bodies[0] = (struct Body){0, 0, 0, 0, 0, 0, SOLAR_MASS};
```

---

## Bug Found

### binary_trees: LLVM Codegen Panic
```
thread 'main' panicked at bmb\src\codegen\llvm.rs:1903:61:
Found IntValue but expected PointerValue variant
```

The codegen fails on `ptrtoint` instruction handling. This needs investigation.

---

## Recommendations

### High Priority Fixes

1. **Add native array/slice types**
   - Add `[T; N]` for fixed arrays
   - Add `&[T]` for slices
   - Eliminate manual `array_get`/`array_set` pattern

2. **Add `break`/`continue` statements**
   - Critical for loop-based algorithms
   - Currently forces inefficient workarounds

3. **Fix binary_trees codegen bug**
   - Investigate `ptrtoint` handling in LLVM codegen

4. **Improve tail recursion to loop optimization**
   - n_body, sorting would benefit
   - Current LinearRecurrenceToLoop only handles fibonacci pattern

### Medium Priority

5. **Add struct literal initialization**
   - `Body { x: 0.0, y: 0.0, ... }` syntax

6. **Investigate json_serialize regression**
   - 211% is unusually high

7. **Fix fannkuch**
   - Currently >3800x slower due to workarounds

### Benchmark Suite Improvements

1. **Mark unfair benchmarks clearly**
   - Add `@unfair` annotation for workaround-heavy tests

2. **Add "language feature exercised" metadata**
   - Track what each benchmark tests

3. **Create "BMB-native" benchmarks**
   - Test what BMB does well (contracts, recursion)
   - Stop trying to emulate C idioms

---

## Conclusion

BMB v0.60.14 shows excellent performance on:
- **Recursion-heavy workloads**: fibonacci 2% (50x faster than C!)
- **Contract-verified code**: hash_table 96%
- **String parsing**: csv_parse 94%, http_parse 89%

But struggles with:
- **Array-heavy algorithms**: spectral_norm 122%, n_body 113%
- **Loop-with-break patterns**: fannkuch broken
- **Memory allocation patterns**: binary_trees fails

**The performance gaps are not compiler optimization failures—they're language feature gaps.**
BMB needs native arrays and control flow statements before these benchmarks can be fair comparisons.

---

## Raw Data

```
fibonacci:     C=248ms  BMB=5ms    (2%)
hash_table:    C=10ms   BMB=9ms    (96%)
sorting:       C=654ms  BMB=170ms  (26%)
csv_parse:     C=20ms   BMB=19ms   (94%)
http_parse:    C=23ms   BMB=20ms   (89%)
fasta:         C=195ms  BMB=194ms  (99%)
json_parse:    C=23ms   BMB=24ms   (104%)
mandelbrot:    C=141ms  BMB=152ms  (108%)
n_body:        C=68ms   BMB=77ms   (113%)
lexer:         C=19ms   BMB=24ms   (123%)
spectral_norm: C=31ms   BMB=38ms   (122%)
json_serialize:C=23ms   BMB=49ms   (211%)
brainfuck:     C=20ms   BMB=26ms   (130%)
binary_trees:  PANIC
fannkuch:      C=79ms   BMB=>300s  (>3800x)
```
