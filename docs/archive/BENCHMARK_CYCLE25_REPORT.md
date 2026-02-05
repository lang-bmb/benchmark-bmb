# BMB Benchmark Report - Cycle 25 (v0.60.39)

## Summary

### Key Changes
1. **`null` keyword now fully supported for pointer comparisons**
   - Eliminated `null_ptr()` function call overhead in benchmarks
   - Added mixed pointer/int comparison codegen for `ptr == null` and `ptr != null`

2. **Codegen improvements**
   - `Expr::Null` now generates direct `icmp eq i64 %ptr, 0` (no function call)
   - Handles both `lhs.is_pointer_value() && rhs.is_int_value()` and vice versa

### IR Quality Improvement

**Before (Cycle 24 - using `null_ptr()`):**
```llvm
%call = call ptr @null_ptr()              ; function call overhead
%lhs_ptr = ptrtoint ptr %field_val to i64
%rhs_ptr = ptrtoint ptr %call to i64      ; extra ptrtoint
%ptr_eq = icmp eq i64 %lhs_ptr, %rhs_ptr
```

**After (Cycle 25 - using `null` keyword):**
```llvm
%lhs_ptr = ptrtoint ptr %field_val to i64
%ptr_null_eq = icmp eq i64 %lhs_ptr, 0    ; direct comparison with 0
```

**Improvement:**
- Eliminates function call overhead
- Eliminates extra `ptrtoint` instruction
- Cleaner, more efficient IR

---

## Benchmark Results

**Note:** LLVM `opt` tool is blocked by Application Control policy on this machine.
Cycle 25 binaries were built with `llc -O3` only (no IR-level optimizations).
Results below reflect this limitation.

| Benchmark | C -O3 (s) | BMB (s) | Ratio | Status |
|-----------|-----------|---------|-------|--------|
| binary_trees | 0.085 | 0.090 | 106% | OK (limited by opt) |
| fibonacci | - | - | - | Not tested (opt blocked) |
| mandelbrot | - | - | - | Not tested (opt blocked) |
| spectral_norm | - | - | - | Not tested (opt blocked) |
| fannkuch | - | - | - | Not tested (opt blocked) |
| fasta | - | - | - | Not tested (opt blocked) |
| n_body | - | - | - | Not tested (opt blocked) |
| sorting | - | - | - | Not tested (opt blocked) |

**Reference (Cycle 24 with full optimizations):**
| Benchmark | Ratio | Status |
|-----------|-------|--------|
| binary_trees | 101% | OK |
| mandelbrot | 108% | OK |
| spectral_norm | 114% | OK |
| fannkuch | 103% | OK |
| fasta | 114% | Slow |
| n_body | 100% | OK |

---

## Code Changes

### 1. Added null keyword support in codegen (`bmb/src/codegen/llvm.rs`)

```rust
// v0.60.39: Pointer-to-int comparison (e.g., ptr == null where null is 0)
} else if lhs.is_pointer_value() && rhs.is_int_value() {
    let result = self.builder
        .build_int_compare(IntPredicate::EQ,
            self.builder.build_ptr_to_int(lhs.into_pointer_value(),
                self.context.i64_type(), "lhs_ptr")?,
            rhs.into_int_value(),
            "ptr_null_eq")?;
    Ok(result.into())
} else if lhs.is_int_value() && rhs.is_pointer_value() {
    // v0.60.39: Int-to-pointer comparison (e.g., null == ptr)
    // ... similar handling
}
```

### 2. Updated binary_trees benchmark

Replaced `null_ptr()` function calls with `null` keyword:

```bmb
// Before:
let nil = null_ptr();
if left == nil { 1 }

// After:
if left == null { 1 }
```

---

## Recommendations for Cycle 26

### Priority 1: Infrastructure
1. **Fix LLVM tools access** - `opt` is blocked by Application Control
2. **Alternative optimization approach** - Consider embedding opt in BMB or using different toolchain

### Priority 2: Language Features
1. **struct array syntax** - Fix fasta benchmark fairness
2. **static array allocation** - Fix n_body benchmark fairness

### Priority 3: Further null optimizations
1. **Constant fold null comparisons** - When comparing with known null, eliminate branch
2. **Add null propagation analysis** - Track nullability through data flow

---

## Infrastructure Issues

### Application Control Policy
- `opt.exe` blocked: "An Application Control policy has blocked this file"
- Impacts LLVM IR optimizations
- Workaround: Use `llc -O3` directly (limited optimization)

### Linker Issues
- `collect2.exe: error: ld returned 1 exit status` on some configurations
- Fixed by using manual `llc` → `gcc` pipeline

---

## Conclusion

Cycle 25 successfully added:
1. Full `null` keyword support for pointer comparisons
2. Cleaner IR generation (eliminated function call overhead)

The improvement is visible in the IR but not measurable in benchmarks due to LLVM toolchain limitations on this machine. With full `opt` access, the improvement should be ~1-2% for pointer-heavy code.

**Version:** v0.60.39
