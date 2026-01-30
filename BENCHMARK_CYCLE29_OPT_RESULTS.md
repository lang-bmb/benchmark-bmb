# BMB Benchmark Results - opt Restored (v0.60.44)

## Summary

Application Control exception granted for `opt.exe`. Full LLVM optimization now available.

## Key Finding: opt vs llc Trade-offs

| Benchmark | llc -O3 only | opt -O2 | C | Best Method |
|-----------|--------------|---------|---|-------------|
| spectral_norm | 70ms (218%) | **37ms (115%)** | 32ms | opt |
| binary_trees | 100ms (122%) | **84ms (102%)** | 82ms | opt |
| mandelbrot | **205ms (151%)** | 357ms (259%) | 138ms | llc |

### Analysis

- **opt excels at:** Loop-heavy compute (spectral_norm), memory allocation (binary_trees)
- **llc excels at:** Simple arithmetic loops (mandelbrot)
- **Cause:** opt transformations can sometimes prevent llc from generating optimal code

---

## Benchmark Details

### spectral_norm (5500 iterations)
```
llc -O3 only:  70ms  (218% of C)
opt -O2:       37ms  (115% of C)  ← BEST
C baseline:    32ms  (100%)
```

### binary_trees (depth 21)
```
llc -O3 only:  100ms (122% of C)
opt -O2:       84ms  (102% of C)  ← BEST
C baseline:    82ms  (100%)
```

### mandelbrot (16000x16000)
```
llc -O3 only:  205ms (151% of C)  ← BEST
opt -O2:       357ms (259% of C)
opt -O3:       350ms (254% of C)
C baseline:    138ms (100%)
```

---

## Recommendations

### Option 1: Selective Optimization
Choose opt or llc based on code characteristics:
- Use `opt` for: complex control flow, memory-intensive code
- Use `llc` for: simple tight loops, floating-point heavy code

### Option 2: Profile-Guided Selection
Run both and keep the faster result (for benchmarks/critical code).

### Option 3: Investigate mandelbrot Regression
Analyze why opt hurts mandelbrot:
```bash
# Compare assembly output
opt -O3 -S mandelbrot.ll -o mandelbrot_opt.ll
diff mandelbrot.ll mandelbrot_opt.ll
```

---

## Current Compiler Behavior

The compiler tries opt first, falls back to llc if opt fails:

```rust
// Try opt
let opt_result = Command::new("opt")
    .args([opt_level_str, "-o", &opt_bc, &temp_bc])
    .output();

// If opt fails, try llc
if !opt_success {
    let llc_result = Command::new("llc")
        .args(["-O3", "-filetype=obj", "-o", &obj, &temp_bc])
        .output();
}
```

---

## Next Steps

1. Investigate mandelbrot opt regression
2. Consider per-benchmark optimization strategy
3. Profile spectral_norm to understand remaining 15% gap

---

**Version:** v0.60.44
**Date:** 2026-01-30
