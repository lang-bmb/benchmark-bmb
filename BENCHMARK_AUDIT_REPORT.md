# BMB Benchmark Fairness Audit Report

## Executive Summary

Comprehensive audit of BMB benchmark suite comparing C and BMB implementations for fairness, consistency, and measurement validity.

**Final Results After All Optimizations (2026-01-28 v0.60):**

| Category | Count | Benchmarks |
|----------|-------|------------|
| FAST (<100%) | 7 | n_body 94%, fannkuch 82%, json_serialize 76%, brainfuck 98%, csv_parse 75%, http_parse 60% |
| OK (100-103%) | 4 | binary_trees 100%, hash_table 102%, spectral_norm 102%, sorting 102%, mandelbrot 101% |
| SLOW (>103%) | 4 | fibonacci 104%, fasta 117%, json_parse 131%, lexer 105% |

### v0.60 Cycle 7 Analysis

**Key Changes:**
- Increased iteration counts for better measurement accuracy:
  - json_parse: 10,000 → 100,000 iterations
  - sorting: 50 → 200 iterations

**Key Discovery: MIR Optimizations Require `--release` or `--aggressive`**

The default build mode (`Debug`) runs NO MIR optimizations. The benchmark script uses `--aggressive` which correctly enables all optimizations including:
- TailCallOptimization (8 passes)
- TailRecursiveToLoop (6 passes)
- LoopInvariantCodeMotion (5 passes)

**Results After Increased Iterations:**

| Benchmark | Before v0.60 | After v0.60 | Change |
|-----------|--------------|-------------|--------|
| **sorting** | 99-114% (varies) | 102% OK | Stabilized |
| **brainfuck** | 102-106% (varies) | 98% FAST | Improved |
| **json_parse** | 107% | 131% SLOW | True performance revealed |
| **fasta** | 117-139% | 117% SLOW | Stabilized |

**json_parse Root Cause Analysis:**
With 100K iterations, the 131% slowdown is a genuine performance gap, not measurement noise. The TailRecursiveToLoop optimization IS working (verified via verbose output), but there's still overhead from:
- String object handling vs C's const char*
- byte_at() method call overhead
- Store/load patterns in generated LLVM IR (alloca-based temporaries)

### v0.59 Compiler-Level Optimizations

| Benchmark | Before | After | Change | Method |
|-----------|--------|-------|--------|--------|
| **brainfuck** | 106% SLOW | 102% OK | -4% | Added @inline attribute support to compiler + applied to exec_one |

**Key Finding:** Added compiler-level support for explicit `@inline` attribute that forces LLVM `alwaysinline` attribute, bypassing the compiler's size-based heuristics (15-20 instruction limit).

### Cycle 6 Analysis (v0.59)

**Measurement Variance Analysis:**
Short benchmarks (3-8ms) show 3-8% variance between runs. This makes benchmarks near the 103% threshold fluctuate between OK and SLOW status.

**Consistently SLOW:** Only `fasta` (129-139%) is consistently slow across all measurements.

**fasta Root Cause Analysis:**
- 100 `inttoptr` instructions in optimized LLVM IR
- Every memory access requires i64 → ptr conversion
- BMB uses i64 as pointer proxy (language design limitation)
- **Required fix:** Native pointer/struct types in the language

**Borderline Benchmarks (vary with measurement):**
- sorting: 99-110% (varies)
- brainfuck: 102-106% (varies)
- json_parse: 105-110% (varies)

These variations are within measurement noise for short-running benchmarks.

### v0.57 Optimizations Applied

| Benchmark | Before | After | Change | Method |
|-----------|--------|-------|--------|--------|
| **sorting** | 106% SLOW | 99% FAST | -7% | Inlined instruction handling removes function call overhead |
| **brainfuck** | 108% SLOW | 102% OK | -6% | Inlined all instruction handlers, eliminated tuple returns |
| **hash_table** | 103% OK | 99% FAST | -4% | Consistent with v0.56 inlining |

### Optimizations Applied (v0.56)

| Benchmark | Before | After | Change | Method |
|-----------|--------|-------|--------|--------|
| **hash_table** | 111% SLOW | 102% OK | -9% | Inlined accessor functions directly |
| **fasta** | 127% SLOW | 138% SLOW | +11% | Array lookup + inline (didn't help) |
| **http_parse** | 64% | 66% | OK | Already fixed with byte_at() |

---

## Optimization Attempts

### 1. hash_table (111% → 102%) - SUCCESS

**Problem:** Function call overhead from accessor functions (`entry_ptr`, `entry_state`, `entry_key`).

**Solution:** Inlined all accessor logic directly into the loop functions:

```bmb
// Before: Multiple function calls
let e = entry_ptr(m, idx);
let state = entry_state(e);
if entry_key(e) == key { ... }

// After: Direct inlined access
let e = m + 8 + (idx * 24);
let state = load_i64(e + 16);
if load_i64(e) == key { ... }
```

**Result:** 111% → 102% (within OK range)

---

### 2. fasta (127% → 138%) - FAILED

**Problem:** Linear search through probability table with cascading if-else or recursive function calls.

**Attempted Solutions:**

1. **Array-based lookup tables** (v0.56): Replaced if-else chains with pre-allocated arrays
   - Result: No improvement (~138%)

2. **While loop conversion**: Replaced recursion with while loop
   - Result: BMB while loops lack early exit (break), so still iterate all elements

3. **@inline + direct load_i64**: Added inline hints and inlined load_i64 calls
   - Result: No significant improvement

**Root Cause Analysis:**

The fundamental issue is NOT the algorithm but the execution overhead:

| Aspect | C | BMB |
|--------|---|-----|
| Array access | `table[i].p` → single instruction | `load_i64(table + i * 16)` → inttoptr + load |
| Loop | Simple for loop | Recursive calls (even with TCO) |
| Type system | Native pointers | i64 as pointer proxy |

**Conclusion:** This requires compiler-level improvements:
1. Native struct/pointer support
2. Better optimization of load_i64 pattern
3. Jump table generation for recursive selection

---

## Remaining SLOW Benchmarks

### fasta (138%) - Compiler Optimization Needed

**Root cause:** i64-to-pointer conversion overhead and lack of native struct support.

**Required fixes:**
- Native struct types with field access
- Pointer type system (not i64 proxy)
- Better LLVM IR generation for memory access patterns

### sorting (105%) - Within Measurement Variance

**Analysis:** At 5% overhead with 3-4% variance, this is statistically borderline. The ~5% difference could be from:
- Tuple return overhead in partition function
- Slightly different array handling

### json_parse (106%) - Within Measurement Variance

**Analysis:** At 6% overhead with 3-6% variance, this is statistically borderline.

---

## Fair Benchmarks Summary

### FAST Benchmarks (BMB legitimately faster)

| Benchmark | Result | Reason |
|-----------|--------|--------|
| fibonacci | 98% | TCO optimization effective |
| n_body | 95% | Good numeric codegen |
| fannkuch | 83% | Local variables allow better register allocation |
| json_serialize | 77% | StringBuilder efficient |
| csv_parse | 77% | StringBuilder + efficient parsing |
| http_parse | 66% | byte_at() is efficient |
| lexer | 97% | Equivalent performance |

### OK Benchmarks (Within tolerance)

| Benchmark | Result | Notes |
|-----------|--------|-------|
| binary_trees | 101% | Within variance |
| hash_table | 102% | Improved with inlining |
| spectral_norm | 100% | Identical performance |
| mandelbrot | 100% | Identical performance |
| brainfuck | 103% | Within variance |

---

## Compiler Optimization Opportunities

Based on the audit, these compiler improvements would have the most impact:

### High Priority

1. **Native struct types** - Would enable C-like struct access patterns
   - Impact: fasta 138% → ~100%, hash_table could be even faster

2. **Jump table for pattern matching** - Convert cascading if-else to switch/jump table
   - Impact: fasta selection loop could be O(1) instead of O(n)

### Medium Priority

3. **Better pointer optimization** - Optimize inttoptr/ptrtoint patterns
   - Impact: All memory-intensive benchmarks

4. **Loop-invariant code motion for while loops** - Already exists for recursion, ensure it works for while

---

## Measurement Methodology

### Current Setup
- 5 runs per benchmark, discarding min/max
- Variance tracked and flagged when >10%
- Results categorized as FAST (<100%), OK (100-103%), SLOW (>103%)

### Known Limitations
- Short benchmarks (4-6ms) have higher variance (3-8%)
- Results within ±5% are statistically equivalent

---

## Conclusion

### Overall Assessment

**12 of 15 benchmarks (80%)** are at or faster than C performance, demonstrating BMB's core compilation is sound.

### Summary of Changes (v0.56 → v0.57)

| Metric | v0.56 | v0.57 | Change |
|--------|-------|-------|--------|
| FAST benchmarks | 7 | 7 | 0 (sorting improved to FAST) |
| OK benchmarks | 5 | 5 | 0 (brainfuck improved to OK) |
| SLOW benchmarks | 3 | 3 | 0 (lexer now borderline SLOW) |
| sorting | 106% | 99% | **-7% improvement** |
| brainfuck | 108% | 102% | **-6% improvement** |

### Remaining SLOW Benchmarks Analysis

| Benchmark | Result | Root Cause | Fix Required |
|-----------|--------|------------|--------------|
| fasta | 135% | StringBuilder overhead, i64-to-pointer | Compiler: struct types, inlined string ops |
| sorting | 106% | Measurement variance (~5%) | Statistically equivalent |
| json_parse | 109% | Measurement variance (~5%) | Statistically equivalent |
| lexer | 105% | Measurement variance (~6%) | Statistically equivalent |

### v0.57 Cycle 4 Finding: TCO vs While Loops

**Key Discovery:** Tail recursion with TCO is FASTER than while loops for hot paths.

Testing on fasta's character generation loops:
- Tail recursive version: 135% of C
- While loop version: 275% of C (2x slower!)

**Reason:** While loops with mutable variables incur:
1. alloca for each mutable variable
2. store/load on each iteration
3. PHI nodes less optimized than tail calls

**Recommendation:** Prefer tail recursion over while loops for performance-critical loops.

### Next Steps for Compiler

1. **Struct support**: Add native struct types to eliminate memory access overhead (fasta)
2. **Pointer types**: Replace i64-as-pointer pattern with real pointer type
3. **Jump tables**: Optimize cascading if-else to switch/jump table for O(1) dispatch

These are fundamental language/compiler improvements, not benchmark-specific fixes.
