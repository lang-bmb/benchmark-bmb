# Benchmark Cycle 31 Report - v0.60.55

## Summary

**Optimization:** Conditional Increment to Branchless Add

**Impact:** Eliminates branches in conditional increment patterns, enabling better pipelining and potential vectorization.

## New Optimization: ConditionalIncrementToSelect (v0.60.55)

### Pattern Detected
```
cond_block:
  %cond = icmp eq %byte_i64, 1
  br i1 %cond, then_block, else_block

then_block:
  %new_val = add %val, 1
  br merge_block

else_block:
  br merge_block

merge_block:
  %result = phi [%new_val, then_block], [%val, else_block]
```

### Transformed To
```
cond_block:
  %cond = icmp eq %byte_i64, 1
  %cond_i64 = zext i1 %cond to i64
  %result = add %val, %cond_i64
  br merge_block
```

### Benefits
1. **Branch elimination** - No branch misprediction penalty
2. **Better pipelining** - Straight-line code for CPU
3. **Vectorization potential** - LLVM can better vectorize branchless loops

## Benchmark Results

| Benchmark | BMB (ms) | C (ms) | Ratio | Status |
|-----------|----------|--------|-------|--------|
| ackermann | 55 | 10979 | 0.005x | ✅ BMB wins (TCO) |
| binary_trees | 104 | 104 | 1.00x | ✅ Equal |
| collatz | 159 | 172 | 0.92x | ✅ BMB faster |
| digital_root | 33 | 33 | 1.00x | ✅ Equal |
| fannkuch | 96 | 88 | 1.09x | ✅ Close |
| fasta | 59 | 53 | 1.11x | ✅ Close |
| fibonacci | 24 | 10509 | 0.002x | ✅ BMB wins (LR) |
| gcd | 151 | 178 | 0.85x | ✅ BMB faster |
| hash_table | 134 | 104 | 1.29x | ⚠️ 29% slower |
| k-nucleotide | 26 | 27 | 0.96x | ✅ BMB faster |
| mandelbrot | 169 | 156 | 1.08x | ✅ Close |
| matrix_multiply | 37 | 31 | 1.19x | ⚠️ 19% slower |
| n_body | 94 | 85 | 1.11x | ✅ Close |
| nqueen | 882 | 6808 | 0.13x | ✅ BMB wins (TCO) |
| perfect_numbers | 615 | 997 | 0.62x | ✅ BMB faster |
| pidigits | 30 | 31 | 0.97x | ✅ Equal |
| primes_count | 45 | 53 | 0.85x | ✅ BMB faster |
| regex_redux | 30 | 32 | 0.94x | ✅ BMB faster |
| reverse-complement | 30 | 31 | 0.97x | ✅ Equal |
| sieve | 157 | 136 | 1.15x | ⚠️ 15% slower |
| spectral_norm | 125 | 77 | 1.62x | ⚠️ 62% slower |
| sum_of_squares | 31 | 29 | 1.07x | ✅ Close |
| tak | 34 | 51275 | 0.0007x | ✅ BMB wins (TCO) |
| brainfuck | 26 | 28 | 0.93x | ✅ BMB faster |
| csv_parse | 29 | 34 | 0.85x | ✅ BMB faster |
| http_parse | 30 | 34 | 0.88x | ✅ BMB faster |
| json_parse | 29 | 32 | 0.91x | ✅ BMB faster |
| json_serialize | 30 | 33 | 0.91x | ✅ BMB faster |
| lexer | 28 | 29 | 0.97x | ✅ Equal |
| sorting | 168 | 639 | 0.26x | ✅ BMB faster |

### Summary Statistics

- **19 benchmarks**: BMB ≤ C (ratio ≤ 1.0)
- **6 benchmarks**: BMB close (1.0 < ratio ≤ 1.15)
- **4 benchmarks**: BMB slower (ratio > 1.15)
  - spectral_norm: 1.62x (main issue - floating point)
  - hash_table: 1.29x (memory access patterns)
  - matrix_multiply: 1.19x (needs SIMD)
  - sieve: 1.15x (improved from ~1.21x)

## Files Changed

- `bmb/src/mir/optimize.rs` - Added `ConditionalIncrementToSelect` pass

## Next Steps

1. **spectral_norm** - Investigate floating-point performance gap
2. **hash_table** - Analyze memory access patterns
3. **matrix_multiply** - Consider SIMD intrinsics

## Verification

- All tests pass: `cargo test --release`
- Sieve output matches C: 14388000
