# BMB Performance Gap Analysis

**Version**: v0.68.0
**Date**: 2026-02-05
**Baseline**: v0.60.251 benchmark results

## Executive Summary

Out of 48 benchmarks, 14 are **SLOW** (>10% slower than C). This document analyzes root causes and improvement strategies.

| Category | SLOW Count | Critical Gaps |
|----------|------------|---------------|
| Compute | 4 | fannkuch (2.12x), fibonacci (1.44x) |
| Memory | 3 | simd_sum (1.5x) |
| Real World | 2 | http_parse (2.29x), json_serialize (1.46x) |
| System | 1 | syscall_overhead (2.72x) |
| Zero Overhead | 2 | aliasing_proof (1.25x) |
| Contract | 1 | purity_opt (1.25x) |
| Bootstrap | 1 | parse_bootstrap (1.25x) |

---

## Critical Gaps (>1.5x slower)

### 1. syscall_overhead (2.72x)

**Benchmark**: Measures FFI/syscall overhead
**BMB**: 87ms | **C**: 32ms

**Root Cause**:
- BMB runtime initialization overhead
- Extra wrapper layers for FFI calls
- String allocation for syscall arguments

**Improvement Strategy**:
- [ ] Optimize runtime startup
- [ ] Direct FFI without wrapper allocation
- [ ] Lazy initialization of runtime structures

### 2. http_parse (2.29x)

**Benchmark**: HTTP header parsing
**BMB**: 16ms | **C**: 7ms

**Root Cause**:
- String operations in BMB are not as optimized as C
- Pattern matching overhead
- Allocation patterns differ

**Improvement Strategy**:
- [ ] Use byte-level parsing (avoid String allocations)
- [ ] Implement specialized string matching intrinsics
- [ ] Profile and optimize hot paths

### 3. fannkuch (2.12x)

**Benchmark**: Fannkuch-redux (permutation generation)
**BMB**: 140ms | **C**: 66ms

**Root Cause**:
- Array swap/reverse operations not optimized
- Loop structure differs from C
- LLVM fails to vectorize BMB version

**Improvement Strategy**:
- [ ] Review generated IR vs C IR
- [ ] Add vectorization hints
- [ ] Consider specialized array intrinsics

---

## Moderate Gaps (1.2x - 1.5x slower)

### 4. simd_sum (1.5x)

**Benchmark**: SIMD vector summation
**BMB**: 6ms | **C**: 4ms

**Root Cause**:
- BMB lacks SIMD intrinsics
- LLVM auto-vectorization less effective

**Improvement Strategy**:
- [ ] Add SIMD intrinsics to BMB
- [ ] Use contract-guided vectorization hints
- [ ] Align memory for vector operations

### 5. json_serialize (1.46x)

**Benchmark**: JSON serialization
**BMB**: 16ms | **C**: 11ms

**Root Cause**:
- String builder allocation patterns
- Integer-to-string conversion overhead

**Improvement Strategy**:
- [ ] Optimize StringBuilder implementation
- [ ] Use pre-allocated buffers
- [ ] Inline integer formatting

### 6. fibonacci (1.44x)

**Benchmark**: Recursive fibonacci
**BMB**: 23ms | **C**: 16ms

**Root Cause**:
- Tail-call optimization differences
- Function call overhead

**Improvement Strategy**:
- [ ] Verify TCO is applied correctly
- [ ] Check for register spilling differences

### 7. memory_copy (1.25x)

**Benchmark**: Memory copy operations
**BMB**: 5ms | **C**: 4ms

**Root Cause**:
- BMB uses loop, C uses memcpy
- LLVM doesn't recognize copy pattern

**Improvement Strategy**:
- [ ] Detect copy patterns in MIR
- [ ] Lower to memcpy/memmove intrinsics

### 8. aliasing_proof (1.25x)

**Benchmark**: Aliasing optimization test
**BMB**: 5ms | **C**: 4ms

**Root Cause**:
- noalias annotations not fully propagated
- LLVM alias analysis limitations

**Improvement Strategy**:
- [ ] Ensure noalias is on all parameters
- [ ] Add restrict-like semantics

### 9. Other 1.2x-1.25x Gaps

| Benchmark | Ratio | Category |
|-----------|-------|----------|
| fasta | 1.2x | Compute |
| mandelbrot | 1.2x | Compute |
| pointer_chase | 1.2x | Memory |
| null_check_proof | 1.2x | Zero Overhead |
| purity_opt | 1.25x | Contract |
| parse_bootstrap | 1.25x | Bootstrap |

These minor gaps are within acceptable variance and may be due to:
- Measurement noise
- Slight IR generation differences
- Runtime initialization costs amortized differently

---

## Gate #3.1 Analysis

**Requirement**: Compute benchmarks ≤ 1.10x C
**Status**: 6/10 passed ❌

| Benchmark | Ratio | Status |
|-----------|-------|--------|
| ackermann | 1.00x | ✅ PASS |
| binary_trees | 1.09x | ✅ PASS |
| gcd | 0.95x | ✅ PASS |
| hash_table | 0.50x | ✅ PASS |
| n_body | 0.23x | ✅ PASS |
| spectral_norm | 0.80x | ✅ PASS |
| fannkuch | 2.12x | ❌ FAIL |
| fasta | 1.20x | ❌ FAIL |
| fibonacci | 1.44x | ❌ FAIL |
| mandelbrot | 1.20x | ❌ FAIL |

**Action Required**:
1. **fannkuch**: Critical - needs IR-level optimization
2. **fibonacci**: Medium - verify TCO
3. **fasta/mandelbrot**: Low - small gaps, may improve with general optimizations

---

## Improvement Priorities

### P0: Critical (>1.5x gap)
1. syscall_overhead - Runtime optimization
2. http_parse - String parsing optimization
3. fannkuch - Array operation optimization

### P1: Important (1.2x-1.5x gap, affects Gate #3.1)
4. fibonacci - TCO verification
5. fasta - Profile and optimize
6. mandelbrot - Float operation check

### P2: Nice-to-have (<1.25x gap)
7. Memory copy pattern detection
8. SIMD intrinsics
9. Better alias propagation

---

## Comparison with C

### Why BMB ≈ C (in most cases)

Both use LLVM backend with same optimization level:
- Same instruction selection
- Same register allocation
- Same loop optimizations

### Why BMB < C (in some cases)

1. **Runtime overhead**: BMB has minimal runtime for string management
2. **ABI differences**: BMB calling convention may differ
3. **IR generation**: BMB may generate less optimal IR patterns
4. **Intrinsics**: C stdlib has highly optimized implementations

### Why BMB > C (in some cases)

1. **Contract-guided optimization**: Bounds checks eliminated at compile time
2. **Type-aware optimization**: Richer type information for MIR passes
3. **Proof-guided DCE**: Dead code elimination based on contracts

---

## Next Steps

1. **Profile critical benchmarks** with perf/vtune
2. **Compare IR output** for fannkuch, fibonacci
3. **Implement runtime optimizations** for syscall overhead
4. **Add SIMD intrinsics** for simd_sum and vectorizable loops

---

## Appendix: Full Results

See `results/BENCHMARK_REPORT_2026-01-21_105739.md` for complete results.
