# BMB Benchmark Report - Cycle 30 Comprehensive Analysis

## Summary

**Version:** v0.60.45 (with opt + scalarizer)
**Date:** 2026-01-30

This report provides a comprehensive analysis of the BMB benchmark suite, including performance results, benchmark fairness issues, and areas for improvement.

---

## Performance Results

### Compute Benchmarks (BMB vs C -O3)

| Benchmark | BMB (ms) | C (ms) | Ratio | Status |
|-----------|----------|--------|-------|--------|
| spectral_norm | 38 | 32 | 119% | ✓ OK |
| binary_trees | 87 | 83 | 105% | ✓ EXCELLENT |
| mandelbrot | 146 | 141 | 104% | ✓ EXCELLENT |
| fannkuch | 73 | 68 | 107% | ✓ OK |
| n_body | 78 | 68 | 115% | ✓ OK |
| fibonacci* | 7 | 263 | **3%** | ⚠️ UNFAIR (algorithm differs) |
| hash_table* | 11 | 38 | **29%** | ⚠️ BUGGY (delete not working) |
| fasta | LINK FAIL | - | - | ❌ BROKEN |

### Real-World Benchmarks (Corrected: C -O3)

| Benchmark | BMB (ms) | C -O3 (ms) | C -O0 (ms) | Ratio (vs -O3) | Status |
|-----------|----------|------------|------------|----------------|--------|
| brainfuck | 5 | 47 | 33 | **11%** | ⚠️ BMB output differs |
| sorting | 137 | 81 | 650 | **169%** | ✓ BMB is slower |
| json_parse | 5 | 49 | 36 | **10%** | ? INVESTIGATE |

**CRITICAL FINDING:** The `c_bench.exe` files were compiled without optimization (-O0).
When comparing against properly optimized C (-O3), BMB is **slower** on sorting (169%).

---

## Critical Issues Found

### Issue 1: C Baselines Compiled Without Optimization ⚠️⚠️⚠️

**Severity:** HIGH - Makes BMB look better than it actually is

**Problem:** The `c_bench.exe` files in the benchmark suite were compiled with `-O0` (no optimization).

**Evidence:**
```
sorting:    C -O0 = 650ms, C -O3 = 81ms (8x difference!)
brainfuck:  C -O0 = 33ms,  C -O3 = 47ms (anomalous)
json_parse: C -O0 = 36ms,  C -O3 = 49ms (anomalous)
```

**Impact:**
- Sorting: BMB appeared 5x faster, actually 1.7x slower
- Many benchmarks showing false positives

**Recommendation:**
1. Rebuild ALL C baselines with `gcc -O3` or `clang -O3`
2. Add build verification to CI
3. Document required compiler flags

---

### Issue 2: Fibonacci Benchmark - UNFAIR COMPARISON ⚠️

**Location:** `benches/compute/fibonacci/bmb/main.bmb`

**Problem:** The BMB version uses recursive Fibonacci:
```bmb
fn fibonacci(n: i64) -> i64 =
  if n <= 1 { n } else { fibonacci(n - 1) + fibonacci(n - 2) };
```

BMB's `LinearRecurrenceToLoop` optimization converts this O(2^n) exponential algorithm into an O(n) loop. The C version remains exponential.

**Result:** BMB appears **40x faster**, but this is algorithmic difference, not raw performance.

**Evidence:** The source file itself states:
> "NOTE: This is NOT a fair comparison! ... For fair comparison, use main_iterative.bmb/c"

**Recommendation:**
1. Rename current benchmark to `fibonacci_optimization_demo`
2. Use `main_iterative.bmb` for fair performance comparison
3. Create matching iterative C version

---

### Issue 3: Hash Table Benchmark - BUG ⚠️

**Location:** `benches/compute/hash_table/bmb/main.bmb`

**Problem:** The delete operation is not decrementing the count properly.

**Evidence:**
```
C output:   95259, 100000, 46445  (count decreased after delete)
BMB output: 95259, 100000, 95259  (count unchanged after delete)
```

**Impact:** Benchmark shows incorrect results, making performance comparison invalid.

**Root Cause:** Investigation needed in `hm_remove` function.

---

### Issue 4: fasta Benchmark - BUILD FAILURE ❌

**Problem:** Link failure due to missing runtime function:
```
undefined reference to `bmb_sb_with_capacity'
```

**Root Cause:** Runtime library (`libbmb_runtime.a`) doesn't export `bmb_sb_with_capacity` function that the fasta benchmark requires.

**Recommendation:**
1. Add `bmb_sb_with_capacity` to runtime library, OR
2. Rewrite fasta benchmark to not use StringBuilder capacity preallocation

---

### Issue 5: Suspiciously Good Results - INVESTIGATION NEEDED

Several benchmarks show BMB dramatically outperforming C (4-7x faster), which is unrealistic:

| Benchmark | Ratio | Suspicion Level |
|-----------|-------|-----------------|
| hash_table | 29% | High |
| brainfuck | 15% | High |
| sorting | 21% | High |
| json_parse | 14% | High |

**Possible Causes:**
1. Different algorithm implementations (like fibonacci)
2. Different workload sizes
3. Missing functionality in BMB version (early exit)
4. Different I/O handling overhead

**Action Required:** Audit each benchmark for algorithmic equivalence.

---

## Benchmark Fairness Audit

### Pass (Fair Comparisons) ✓

| Benchmark | Verification |
|-----------|--------------|
| spectral_norm | Same algorithm, same workload (N=500) |
| binary_trees | Same algorithm, same depth (21) |
| mandelbrot | Same algorithm, same resolution (2000x2000) |
| fannkuch | Same algorithm, same N (12) |
| n_body | Same algorithm, same iterations (50M) |

### Fail (Unfair or Broken) ✗

| Benchmark | Issue |
|-----------|-------|
| fibonacci | Algorithmic optimization difference |
| fasta | Build failure |
| hash_table | Needs audit |
| brainfuck | Needs audit |
| sorting | Needs audit |
| json_parse | Needs audit |

---

## Technical Findings

### v0.60.45 Optimization: scalarizer Pass

LLVM opt's auto-vectorization can hurt performance for simple arithmetic loops with early exits (mandelbrot case).

**Solution Applied:**
```rust
let passes_arg = match self.opt_level {
    OptLevel::Release => "default<O2>,scalarizer",
    // ...
};
```

**Impact:**
| Benchmark | opt only | opt+scalarizer | Improvement |
|-----------|----------|----------------|-------------|
| mandelbrot | 350ms | 145ms | 2.4x faster |

---

## Areas for Improvement

### 1. Missing C Baselines

The following benchmarks lack C baselines:
- `memory/pointer_chase`
- `memory/simd_vectorization`
- Several `contract_opt` benchmarks

### 2. Runtime Library Gaps

Missing runtime functions:
- `bmb_sb_with_capacity` (StringBuilder)
- Possibly other StringBuilder methods

### 3. Benchmark Documentation

Each benchmark should include:
- Algorithm complexity (Big-O)
- Workload parameters
- Expected output for verification
- Fair comparison checklist

### 4. Automated Fairness Checking

Implement automated checks:
- Output equivalence verification
- Algorithm complexity annotation
- Workload size validation

---

## Recommendations

### Immediate Actions

1. **Fix fibonacci benchmark** - Use iterative version for fair comparison
2. **Fix fasta build** - Add missing runtime function
3. **Audit suspicious results** - Verify hash_table, brainfuck, sorting, json_parse

### Medium-Term Actions

4. **Add fairness metadata** - Document algorithm/workload equivalence
5. **Complete C baselines** - Add missing C implementations
6. **Expand runtime** - Add StringBuilder capacity functions

### Long-Term Actions

7. **Automated benchmark CI** - Run benchmarks on every release
8. **Regression detection** - Alert on performance regressions > 5%
9. **Cross-platform testing** - Windows, Linux, macOS benchmarks

---

## Appendix: Benchmark Output Samples

### spectral_norm
```
BMB: 1.274219991
C:   1.274219991
```

### binary_trees
```
BMB: stretch tree of depth 22    check: 8388607
C:   stretch tree of depth 22    check: 8388607
```

### mandelbrot
```
BMB: 1518515 (pixels in set)
C:   1518515 (pixels in set)
```

---

## Corrected Performance Summary

After correcting for optimization levels and excluding unfair/broken benchmarks:

### Valid Benchmarks (Fair Comparison, C -O3)

| Benchmark | BMB (ms) | C (ms) | Ratio | Verdict |
|-----------|----------|--------|-------|---------|
| spectral_norm | 38 | 32 | 119% | Acceptable |
| binary_trees | 87 | 83 | 105% | Good |
| mandelbrot | 146 | 141 | 104% | Good |
| fannkuch | 73 | 68 | 107% | Acceptable |
| n_body | 78 | 68 | 115% | Acceptable |
| sorting | 137 | 81 | 169% | **Needs work** |

**Average Ratio:** ~120% (BMB is 20% slower than C -O3)

### Invalid Benchmarks (Excluded from Comparison)

| Benchmark | Issue |
|-----------|-------|
| fibonacci | Unfair: algorithmic optimization difference |
| hash_table | Bug: delete operation broken |
| fasta | Broken: missing runtime function |
| brainfuck | Different outputs between implementations |
| json_parse | Needs verification |

---

## Action Items (Priority Order)

1. **URGENT:** Rebuild all C baselines with `-O3`
2. **HIGH:** Fix hash_table delete bug
3. **HIGH:** Add `bmb_sb_with_capacity` to runtime
4. **MEDIUM:** Create iterative fibonacci benchmark
5. **MEDIUM:** Verify brainfuck and json_parse equivalence
6. **LOW:** Add benchmark build verification to CI

---

**Report Generated:** 2026-01-30
**Compiler Version:** v0.60.45
