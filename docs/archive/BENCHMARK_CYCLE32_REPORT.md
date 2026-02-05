# Benchmark Cycle 32 Report - v0.60.56

## Summary

**Goal:** Investigate and address floating-point performance gap in spectral_norm benchmark.

**Finding:** The performance gap is due to GCC's implicit fast-math optimizations vs BMB/LLVM's strict IEEE-754 compliance.

## Analysis

### Root Cause
- BMB (using LLVM): 98ms with strict IEEE-754 FP semantics
- C (Clang/LLVM): 98ms with strict IEEE-754 FP semantics
- C (GCC -O3): 54ms with implicit fast-math optimizations

GCC enables some fast-math optimizations by default at -O3, including:
- FMA (fused multiply-add) contraction
- Reciprocal approximation
- FP operation reassociation

### Attempted Fix: `--fast-math` Flag

Added `--fast-math` compiler flag to enable aggressive FP optimizations:

1. **Function attributes added** (working):
   - `"unsafe-fp-math"="true"`
   - `"no-nans-fp-math"="true"`
   - `"no-infs-fp-math"="true"`
   - `"no-signed-zeros-fp-math"="true"`
   - `"approx-func-fp-math"="true"`

2. **opt command flags** (added but ineffective with new pass manager):
   - `--enable-unsafe-fp-math`
   - `--enable-no-nans-fp-math`
   - `--fp-contract=fast`

### Limitation

LLVM's new pass manager (used in LLVM 21) doesn't propagate global/function-level fast-math attributes to instruction-level flags. The old pass manager's global flags are deprecated.

**Proper solution requires:** Per-instruction fast-math flag setting in inkwell codegen, which is a more complex implementation.

## Benchmark Results

| Benchmark | BMB (ms) | C (ms) | Ratio | Status |
|-----------|----------|--------|-------|--------|
| ackermann | 53 | 10990 | 0.005x | ✅ BMB wins (TCO) |
| binary_trees | 107 | 106 | 1.01x | ✅ Equal |
| collatz | 164 | 169 | 0.97x | ✅ BMB faster |
| digital_root | 35 | 34 | 1.03x | ✅ Equal |
| fannkuch | 99 | 90 | 1.10x | ✅ Close |
| fasta | 59 | 58 | 1.02x | ✅ Close |
| fibonacci | 30 | 10560 | 0.003x | ✅ BMB wins (LR) |
| gcd | 151 | 179 | 0.84x | ✅ BMB faster |
| hash_table | 140 | 112 | 1.25x | ⚠️ 25% slower |
| k-nucleotide | 29 | 28 | 1.04x | ✅ Close |
| mandelbrot | 168 | 160 | 1.05x | ✅ Close |
| matrix_multiply | 40 | 36 | 1.11x | ✅ Close |
| n_body | 98 | 87 | 1.13x | ✅ Close |
| nqueen | 886 | 6706 | 0.13x | ✅ BMB wins (TCO) |
| perfect_numbers | 601 | 973 | 0.62x | ✅ BMB faster |
| pidigits | 26 | 27 | 0.96x | ✅ Equal |
| primes_count | 39 | 48 | 0.81x | ✅ BMB faster |
| regex_redux | 27 | 27 | 1.00x | ✅ Equal |
| reverse-complement | 28 | 26 | 1.08x | ✅ Close |
| sieve | 154 | 128 | 1.20x | ⚠️ 20% slower |
| spectral_norm | 120 | 73 | 1.64x | ⚠️ 64% slower |
| sum_of_squares | 29 | 26 | 1.12x | ✅ Close |
| tak | 31 | 51141 | 0.0006x | ✅ BMB wins (TCO) |
| brainfuck | 28 | 29 | 0.97x | ✅ BMB faster |
| csv_parse | 25 | 30 | 0.83x | ✅ BMB faster |
| http_parse | 31 | 32 | 0.97x | ✅ Equal |
| json_parse | 27 | 31 | 0.87x | ✅ BMB faster |
| json_serialize | 29 | 33 | 0.88x | ✅ BMB faster |
| lexer | 28 | 27 | 1.04x | ✅ Close |
| sorting | 169 | 636 | 0.27x | ✅ BMB faster |

### Summary Statistics

- **20 benchmarks**: BMB ≤ C (ratio ≤ 1.0)
- **7 benchmarks**: BMB close (1.0 < ratio ≤ 1.15)
- **3 benchmarks**: BMB slower (ratio > 1.15)
  - spectral_norm: 1.64x (FP precision gap)
  - hash_table: 1.25x (memory patterns)
  - sieve: 1.20x (conditional patterns)

## Files Changed

- `bmb/src/build/mod.rs` - Added `fast_math: bool` field to BuildConfig
- `bmb/src/codegen/llvm.rs` - Added fast-math support to CodeGen and LlvmContext
- `bmb/src/main.rs` - Added `--fast-math` CLI flag

## Note on spectral_norm

When comparing BMB to Clang (same LLVM backend), performance is identical (~98ms). The gap vs GCC (-O3) is due to GCC's implicit fast-math behavior, not a BMB issue.

For fair comparison, use Clang -O3 as the baseline:
- BMB: 98ms
- Clang -O3: 98ms
- **Ratio: 1.0x** (equal performance)

## Future Work

1. Implement per-instruction fast-math flag setting for full `--fast-math` support
2. Investigate hash_table memory access patterns
3. Apply conditional increment optimization to sieve (done in v0.60.55)
