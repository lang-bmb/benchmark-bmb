# Benchmark Results: Rust vs BMB

**Date**: 2026-01-08
**Version**: BMB v0.31.16 (Benchmark Gate #1 Interim)
**Platform**: Windows 11 (x86_64-pc-windows-msvc)
**Rust**: 1.84.0
**BMB**: LLVM 18.x backend

## Summary

| Language | fibonacci(35) | Relative |
|----------|---------------|----------|
| Rust     | ~69ms         | 1.00x    |
| BMB      | ~92ms         | 1.33x    |

**BMB is approximately 33% slower than Rust** for this compute-intensive benchmark.

## Detailed Results

### Rust (Release Build)

```
Build: cargo build --release
Binary: target/release/fibonacci.exe

Run 1: 66 ms
Run 2: 70 ms
Run 3: 71 ms
Run 4: 71 ms
Run 5: 67 ms

Average: 69.0 ms
Median:  70 ms
```

### BMB (Native Build)

```
Build: bmb build benches/compute/fibonacci/bmb/main.bmb
Binary: main.exe (LLVM-compiled)

Run 1: 88 ms
Run 2: 95 ms
Run 3: 93 ms
Run 4: 97 ms
Run 5: 89 ms

Average: 92.4 ms
Median:  93 ms
```

## Analysis

### Performance Gap Factors

1. **Optimization Level**: BMB uses basic LLVM optimizations; Rust uses highly tuned LLVM passes
2. **Function Call Overhead**: BMB may have higher call overhead in recursive functions
3. **Integer Representation**: Both use i64, but Rust's codegen is more mature
4. **LLVM Pass Pipeline**: Rust has years of LLVM optimization tuning

### Expected Improvements

- **Contract-based optimizations**: Not applicable to fibonacci (no contracts)
- **Tail-call optimization**: Future BMB feature could eliminate recursion overhead
- **LLVM pass tuning**: Adjusting optimization passes for BMB's IR patterns

## Notes

- C benchmarks could not run (GCC not installed on test system)
- Exit codes truncated to 8 bits: fibonacci(35) = 9227465 → 201 (mod 256)
- Both compilers used default release optimizations
- Warm-up runs were executed before measurement (2 iterations each)

## Conclusion

BMB achieves ~75% of Rust's performance on compute-intensive workloads. This is acceptable for an early-stage compiler. Contract-based optimizations (bounds check elimination, null check elimination) are expected to provide BMB advantages in appropriate workloads.

**Gate Status**: ⚠️ BMB 33% slower than Rust baseline
**Next Gate**: Benchmark Gate #2 (after Bootstrap completion)
