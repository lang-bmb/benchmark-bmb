# BMB Benchmark Analysis Report - v0.60.36

## ⚠️ CRITICAL: Previous Benchmark Results Were INVALID

The pre-built C binaries were NOT compiled with `-O3` optimization, leading to
misleading results (e.g., sorting appeared to be 5x faster than C).

**All C benchmarks have been recompiled with `clang -O3`.**

## Corrected Summary

| Benchmark | C -O3 (s) | BMB (s) | Ratio | Status |
|-----------|-----------|---------|-------|--------|
| fibonacci | 0.448 | 0.000 | **0%** | ⚠️ DEMO - LinearRecurrenceToLoop |
| mandelbrot | 0.130 | 0.138 | 106% | ✅ ACCEPTABLE |
| spectral_norm | 0.030 | 0.030 | **100%** | ✅ EXCELLENT |
| fannkuch | 0.080 | 0.070 | **87%** | ✅ FASTER than C |
| binary_trees | 0.030 | 0.092 | **306%** | ❌ CRITICAL REGRESSION |
| fasta | 0.010 | 0.044 | **440%** | ❌ CRITICAL REGRESSION |
| n_body | 0.066 | 0.078 | 118% | ⚠️ NEEDS OPTIMIZATION |
| brainfuck | ~0 | 0.010 | - | ⚠️ TOO SHORT |
| json_serialize | ~0 | 0.014 | - | ⚠️ TOO SHORT |
| sorting | 0.114 | 0.124 | 108% | ✅ ACCEPTABLE |

---

## Critical Issues

### ❌ CRITICAL: binary_trees (306% ratio)

**Problem**: BMB is 3x slower than C.

**Root causes**:
1. GEP `nuw` keyword incompatibility with clang 18 prevents new build
2. Using older v0.60.35 binary with known issues
3. Tree allocation/traversal overhead

**Action required**:
- Fix LLVM IR compatibility issue
- Profile memory allocation patterns
- Optimize tree traversal

### ❌ CRITICAL: fasta (440% ratio)

**Problem**: BMB is 4.4x slower than C.

**Root causes**:
1. String building overhead (StringBuilder vs char array)
2. Manual memory layout (load_i64/store_i64) vs native struct
3. Random number generation overhead
4. Character output inefficiency

**Action required**:
- Optimize string concatenation
- Add native struct support to language
- Reduce function call overhead

### ⚠️ NEEDS OPTIMIZATION: n_body (118% ratio)

**Problem**: BMB is 18% slower than C.

**Potential causes**:
1. Floating-point operation overhead
2. Struct access via load_f64/store_f64
3. Missing SIMD vectorization

---

## Good Results

### ✅ EXCELLENT: spectral_norm (100%)

After recompiling C with -O3, BMB matches C exactly.
Stack-allocated arrays with native pointer syntax are efficient.

### ✅ FASTER: fannkuch (87%)

BMB is 13% faster than C. Likely due to:
- TailRecursiveToLoop optimization
- Better register allocation
- Effective narrowing optimization

### ✅ ACCEPTABLE: mandelbrot, sorting (~106-108%)

Within acceptable overhead range. Minor optimization opportunities.

---

## Benchmark Infrastructure Issues

### 1. Pre-built C Binaries Not Optimized

**Problem**: C binaries in `build_all/` were NOT compiled with `-O3`.
**Impact**: Made BMB appear faster than it actually is.
**Fix**: Recompile all C benchmarks with `clang -O3`.

### 2. LLVM IR Compatibility

**Problem**: GEP `nuw` keyword not recognized by clang 18.
**Impact**: Cannot rebuild some BMB benchmarks (binary_trees, fasta, n_body).
**Fix**: Ensure LLVM IR output is compatible with target clang version.

### 3. Benchmark Timing Too Short

**Problem**: brainfuck, json_serialize complete in <10ms.
**Impact**: Timing precision issues, unreliable ratios.
**Fix**: Increase workload size for all benchmarks to run >100ms.

---

## Recommendations

### Priority 1: Fix Critical Regressions

1. **fasta (440%)**: Profile and optimize string operations
2. **binary_trees (306%)**: Fix allocation overhead
3. **n_body (118%)**: Optimize struct/float operations

### Priority 2: Infrastructure

1. **Rebuild all C binaries** with `clang -O3`
2. **Fix LLVM IR** `nuw` compatibility
3. **Increase workload** for short benchmarks

### Priority 3: Documentation

1. **Label fibonacci** as "Optimization Demo"
2. **Document expected ratios** for each benchmark
3. **Add fairness assessment** to each benchmark

---

## Benchmark Categories

```
PASSING (≤110%):
  - spectral_norm (100%)
  - mandelbrot (106%)
  - fannkuch (87%)
  - sorting (108%)

NEEDS WORK (>110%):
  - n_body (118%)

CRITICAL (>200%):
  - binary_trees (306%)
  - fasta (440%)

SPECIAL:
  - fibonacci (0% - algorithmic optimization demo)
```

---

## Action Items

- [ ] Rebuild C binaries with -O3 and commit
- [ ] Fix LLVM IR nuw compatibility
- [ ] Profile fasta string operations
- [ ] Profile binary_trees allocation
- [ ] Increase brainfuck/json_serialize workload
- [ ] Create fibonacci_iterative for fair comparison
