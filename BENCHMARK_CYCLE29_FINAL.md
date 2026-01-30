# BMB Benchmark Report - Cycle 29 Final (v0.60.45)

## Summary

### Key Discovery: opt Auto-Vectorization Regression

LLVM opt's auto-vectorization can hurt performance for simple arithmetic loops with early exits.

**Solution:** Add `scalarizer` pass after main optimization to undo harmful vectorization.

---

## Performance Results

### v0.60.45 (opt + scalarizer)

| Benchmark | BMB | C | Ratio | Status |
|-----------|-----|---|-------|--------|
| spectral_norm | 40ms | 32ms | 125% | OK |
| binary_trees | 87ms | 82ms | 106% | OK |
| mandelbrot | 145ms | 138ms | **105%** | EXCELLENT |

### Comparison with Previous Versions

| Benchmark | llc only | opt only | opt+scalarizer | C |
|-----------|----------|----------|----------------|---|
| spectral_norm | 70ms | 37ms | 40ms | 32ms |
| binary_trees | 100ms | 84ms | 87ms | 82ms |
| mandelbrot | 205ms | **350ms** | **145ms** | 138ms |

---

## Technical Details

### The Problem

LLVM opt auto-vectorized mandelbrot's inner loop:

```llvm
; Original (scalar)
%call = call i64 @square_fp(i64 %zr_loop)
%call1 = call i64 @square_fp(i64 %zi_loop)
%add = add nsw i64 %call, %call1

; Vectorized (slower!)
%8 = phi <2 x i64> ...
%9 = mul nsw <2 x i64> %8, %8
%10 = udiv <2 x i64> %9, splat (i64 10000)
%11 = extractelement <2 x i64> %10, i64 0  ; overhead
%12 = extractelement <2 x i64> %10, i64 1  ; overhead
```

**Why vectorization hurts here:**
1. `insertelement`/`extractelement` overhead
2. Loop has early exit (`icmp ugt`) breaking vector benefits
3. 2-element vectors don't utilize full SIMD width

### The Solution

Add scalarizer pass to undo vectorization:

```rust
// bmb/src/codegen/llvm.rs
let passes_arg = match self.opt_level {
    OptLevel::Release => "default<O2>,scalarizer",
    OptLevel::Aggressive => "default<O3>,scalarizer",
    // ...
};
Command::new("opt")
    .args(["--passes", passes_arg, "-o"])
    // ...
```

---

## Code Changes

### `bmb/src/codegen/llvm.rs` (v0.60.45)

```rust
// v0.60.45: Two-pass optimization: main passes + scalarizer
// The scalarizer undoes harmful auto-vectorization for simple loops
// Use new pass manager syntax: -passes='default<O2>,scalarizer'
let passes_arg = match self.opt_level {
    OptLevel::Debug => "default<O0>,scalarizer",
    OptLevel::Release => "default<O2>,scalarizer",
    OptLevel::Size => "default<Os>,scalarizer",
    OptLevel::Aggressive => "default<O3>,scalarizer",
};
let opt_result = Command::new("opt")
    .args(["--passes", passes_arg, "-o"])
    .arg(&opt_bc)
    .arg(&temp_bc)
    .output();
```

### `CLAUDE.md`

Added Build Environment section documenting:
- Required tools (LLVM 21.1.8, GCC MinGW-w64, Rust)
- LLVM tools usage (opt, llc, clang)
- Environment variables (BMB_RUNTIME_PATH)
- Optimization strategy (opt + scalarizer fallback to llc)

---

## Trade-offs

| Benchmark Type | opt only | opt + scalarizer | Recommendation |
|----------------|----------|------------------|----------------|
| Complex loops with early exits | Poor | Good | scalarizer |
| SIMD-friendly parallel loops | Good | OK | opt only |
| Memory-heavy code | Good | Good | either |

**Current default:** scalarizer enabled (balanced performance)

---

## Future Improvements

1. **Selective scalarizer:** Only apply to functions with early-exit loops
2. **Profile-guided:** Collect runtime data to choose opt strategy
3. **BMB-specific vectorization:** Implement in MIR rather than relying on LLVM

---

**Version:** v0.60.45
**Date:** 2026-01-30
