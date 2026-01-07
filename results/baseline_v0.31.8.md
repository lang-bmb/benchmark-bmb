# Benchmark Baseline v0.31.8

> **Date**: 2026-01-07
> **Platform**: Windows, AMD Ryzen (native CPU)
> **Compiler**: rustc with `-C opt-level=3 -C lto=fat -C target-cpu=native`
> **Purpose**: Benchmark Gate #1 baseline for BMB compiler performance targets

## Executive Summary

**13 benchmarks** established across 3 categories:
- **Compute**: 6 benchmarks (CPU-intensive algorithms)
- **Contract**: 4 benchmarks (BMB-specific optimizations)
- **Real World**: 2 benchmarks (practical workloads)

**Note**: C benchmarks not run (GCC not available). Rust used as baseline which should be comparable to C -O3.

## Compute Benchmarks (Benchmarks Game Standard)

| Benchmark | Description | Median (ms) | Min (ms) | Max (ms) |
|-----------|-------------|-------------|----------|----------|
| binary_trees | Memory allocation, recursion | 147.18 | 146.29 | 151.36 |
| fannkuch | Permutation generation, array ops | 315.38 | 291.04 | 333.29 |
| fibonacci | Recursive function calls, integer ops | 34.52 | 34.46 | 36.74 |
| mandelbrot | Fractal generation, fixed-point math | 11.60 | 9.36 | 16.32 |
| n_body | N-body simulation | 10.18 | 9.78 | 10.76 |
| spectral_norm | Matrix operations, linear algebra | 8.86 | 7.83 | 9.19 |

**Target for BMB**: >= Rust baseline (within 5%)

## Contract Benchmarks (BMB-Specific)

| Benchmark | Description | Expected BMB Advantage | Median (ms) | Min (ms) | Max (ms) |
|-----------|-------------|------------------------|-------------|----------|----------|
| bounds_check | Array access with pre conditions | 10-30% (bounds check elimination) | 7.04 | 6.88 | 8.42 |
| null_check | Option<T> handling with contracts | 15-25% (null check elimination) | 8.62 | 8.32 | 8.63 |
| purity_opt | Pure function redundancy | 20-50% (CSE, hoisting) | 6.46 | 5.80 | 6.97 |
| aliasing | Non-aliasing array operations | 30-50% (SIMD vectorization) | 7.42 | 7.11 | 8.10 |

**Target for BMB**: > Rust baseline by 10%+ (contract optimization advantage)

## Real World Benchmarks

| Benchmark | Description | Median (ms) | Min (ms) | Max (ms) |
|-----------|-------------|-------------|----------|----------|
| json_parse | JSON validation and counting | 8.42 | 8.22 | 9.53 |
| sorting | Multiple sorting algorithms | 73.01 | 69.20 | 74.59 |

**Target for BMB**: >= Rust baseline (within 5%)

## Benchmark Gate Criteria

### Gate #1 (v0.31) - Baseline Establishment
- [x] Define benchmark suite: 13 benchmarks across 3 categories
- [x] Run baseline measurements: Rust compiler metrics recorded
- [x] Document baseline: This file

### Gate #2 (v0.32) - Performance Target
- [ ] BMB compute benchmarks >= Rust baseline
- [ ] BMB contract benchmarks > Rust baseline by 10%+
- [ ] Self-compile time baseline established

### Gate #3 (v1.0) - Final Verification
- [ ] All compute benchmarks >= C -O3
- [ ] Contract benchmarks show clear optimization advantage
- [ ] No performance regressions from v0.32

## Methodology

- **Warm-up**: 1 iteration before measurement
- **Iterations**: 3 measurements, median reported
- **Environment**: Single-threaded, native CPU
- **Compiler flags**: Rust with `-C opt-level=3 -C lto=fat -C target-cpu=native`

## Notes

1. **C benchmarks**: Not run due to GCC unavailability. Rust baseline is expected to be comparable.
2. **BMB benchmarks**: Not runnable yet - requires LLVM codegen completion for native compilation.
3. **pidigits**: Skipped (Rust implementation not found)

## Next Steps

1. Install GCC and run C benchmarks for direct comparison
2. Complete BMB native compilation (LLVM codegen)
3. Run BMB benchmarks and compare against baseline
4. Establish CI for benchmark regression detection
