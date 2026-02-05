# Benchmark Cycle 33 Report - v0.60.57

## Summary

**Goal:** Investigate remaining performance gaps (hash_table, matrix_multiply, sieve).

**Finding:** Performance gaps are due to low-level codegen differences, not MIR optimization issues.

## Current Benchmark Results

| Benchmark | BMB (ms) | C (ms) | Ratio | Status |
|-----------|----------|--------|-------|--------|
| ackermann | 57 | 11106 | 0.005x | BMB wins (TCO) |
| binary_trees | 111 | 104 | 1.07x | Close |
| collatz | 160 | 171 | 0.94x | BMB faster |
| digital_root | 35 | 32 | 1.09x | Close |
| fannkuch | 95 | 90 | 1.06x | Close |
| fasta | 60 | 57 | 1.05x | Close |
| fibonacci | 28 | 10617 | 0.003x | BMB wins (LR) |
| gcd | 154 | 179 | 0.86x | BMB faster |
| hash_table | 139 | 106 | **1.31x** | 31% slower |
| k-nucleotide | 26 | 26 | 1.00x | Equal |
| mandelbrot | 170 | 159 | 1.07x | Close |
| matrix_multiply | 38 | 32 | **1.19x** | 19% slower |
| n_body | 97 | 85 | 1.14x | Close |
| nqueen | 885 | 6754 | 0.13x | BMB wins (TCO) |
| perfect_numbers | 607 | 984 | 0.62x | BMB faster |
| pidigits | 27 | 29 | 0.93x | BMB faster |
| primes_count | 42 | 49 | 0.86x | BMB faster |
| regex_redux | 26 | 26 | 1.00x | Equal |
| reverse-complement | 26 | 26 | 1.00x | Equal |
| sieve | 156 | 133 | **1.17x** | 17% slower |
| spectral_norm | 121 | 75 | **1.61x** | 61% slower (FP) |
| sum_of_squares | 27 | 26 | 1.04x | Close |
| tak | 30 | 51421 | 0.0006x | BMB wins (TCO) |
| brainfuck | 26 | 27 | 0.96x | BMB faster |
| csv_parse | 29 | 29 | 1.00x | Equal |
| http_parse | 28 | 31 | 0.90x | BMB faster |
| json_parse | 26 | 33 | 0.79x | BMB faster |
| json_serialize | 28 | 34 | 0.82x | BMB faster |
| lexer | 26 | 25 | 1.04x | Close |
| sorting | 170 | 647 | 0.26x | BMB wins |

## Analysis by Benchmark

### 1. hash_table (1.31x)

**Root Cause: LLVM Codegen + Data Type Size**

BMB inner loop (hm_get_loop):
```asm
leaq  (,%r8,8), %r10        # r10 = idx * 8
leaq  (%r10,%r10,2), %r10   # r10 = idx * 24 (2 instructions)
movq  24(%rcx,%r10), %r11   # load 64-bit state
```

C inner loop:
```asm
leaq  (%rax,%rax,2), %rcx   # rcx = idx * 3
leaq  (%rdx,%rcx,8), %r9    # r9 = base + idx * 24 (combined!)
movl  16(%r9), %ecx         # load 32-bit state
```

**Issues:**
1. BMB uses 2 LEA instructions for `idx * 24`, C combines it with base address in 1
2. BMB state field is 64-bit, C uses 32-bit int (better cache efficiency)
3. BMB's `idx > mask` termination check is dead code (idx is always `band mask`)

**Potential Fixes:**
- Add 32-bit integer type (`i32`) for struct fields
- Implement proper loop termination with iteration counter
- This is an LLVM backend codegen issue, not MIR

### 2. matrix_multiply (1.19x)

**Root Cause: Loop Counter vs Pointer Comparison**

BMB inner loop (8 instructions):
```asm
movq   (%rdx), %r9       # load a[i][k]
incq   %r10              # k++  (extra instruction!)
imulq  (%rcx), %r9       # multiply by b[k][j]
addq   %r9, %rax         # sum += product
addq   %r11, %rdx        # a_ptr += stride
addq   $8, %rcx          # b_ptr += 8
cmpq   %r8, %r10         # k < n?
jl     loop
```

C inner loop (7 instructions):
```asm
movq   (%rax), %rdx      # load a[i][k]
imulq  (%rcx), %rdx      # multiply by b[k][j]
addq   $8, %rax          # a_ptr += 8
addq   %r9, %rcx         # b_ptr += stride
addq   %rdx, %r8         # sum += product
cmpq   %rax, %r10        # a_ptr < a_end?
jne    loop
```

**Issue:** BMB maintains a separate loop counter that C eliminates through pointer comparison.

**Potential Fix:** Loop counter to pointer transformation pass in MIR. Complex optimization.

### 3. sieve (1.17x)

**Root Cause: Vectorization/Unrolling Differences**

Both BMB and C use SIMD vectorization (verified via assembly), but GCC applies more aggressive loop unrolling to the counting loop.

GCC unrolled scalar tail:
```asm
cmpb   $1, (%rcx,%rax)    # check arr[i]
sbbq   $-1, %rsi          # count += (arr[i] == 1)
cmpb   $1, 1(%rcx,%rax)   # check arr[i+1] (unrolled!)
sbbq   $-1, %rsi
cmpb   $1, 2(%rcx,%rax)   # check arr[i+2] (unrolled!)
...
```

**Issue:** GCC's loop unrolling is more aggressive than LLVM's for this pattern.

**Potential Fix:** Investigate LLVM unrolling heuristics, or manually unroll in source.

### 4. spectral_norm (1.61x)

**Root Cause:** FP precision requirements (documented in Cycle 32)
- BMB/LLVM: Strict IEEE-754 compliance
- GCC: Implicit fast-math at -O3

**Status:** Requires per-instruction fast-math flags in inkwell codegen.

## Summary Statistics

- **21 benchmarks**: BMB ≤ C (ratio ≤ 1.0)
- **6 benchmarks**: BMB close (1.0 < ratio ≤ 1.15)
- **4 benchmarks**: BMB slower (ratio > 1.15)

## Optimization Priority Matrix

| Issue | Benchmarks Affected | Complexity | Estimated Impact |
|-------|---------------------|------------|------------------|
| Per-instruction fast-math | spectral_norm | High | -40% for FP code |
| Loop counter elimination | matrix_multiply | High | -10% for matrix ops |
| 32-bit integer types | hash_table | Medium | -15% for struct-heavy |
| Address calc optimization | hash_table | Low (LLVM issue) | -5% |
| Loop unrolling hints | sieve | Medium | -10% |

## Conclusions

The remaining performance gaps are not due to missing MIR optimizations but rather:

1. **LLVM Backend Codegen**: Address calculation patterns not optimal
2. **Data Type Limitations**: No 32-bit integers for efficient struct layouts
3. **Loop Structure**: Counter-based loops vs pointer-based iteration
4. **FP Semantics**: Strict IEEE-754 vs fast-math defaults

These require deeper language/compiler changes:
- Adding `i32` type (language spec change)
- Per-instruction fast-math flags (inkwell codegen change)
- Loop counter to pointer transformation (advanced MIR optimization)

## No Code Changes This Cycle

This cycle was analytical - no compiler changes were made. The findings inform future development priorities.
