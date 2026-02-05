# Fannkuch IR Analysis

**Date**: 2026-02-05
**BMB Version**: v0.69.0
**Performance Gap**: 2.12x slower than C

## Summary

The 2.12x performance gap in fannkuch is caused by:
1. **Heap allocation** vs static arrays (major)
2. **No SIMD vectorization** in BMB (major)
3. **Function call overhead** for array operations (minor - inlined)
4. **Missing memcpy optimization** (moderate)

---

## IR Comparison

### C Version (Optimized)

```llvm
; Vectorized initialization (8 elements per iteration)
%11 = phi <4 x i32> [ <i32 0, i32 1, i32 2, i32 3>, %6 ], [ %23, %8 ]
%12 = add <4 x i32> %11, splat (i32 4)
store <4 x i32> %11, ptr %13, align 16

; Uses memcpy for array copy
tail call void @llvm.memcpy.p0.p0.i64(ptr @perm, ptr @perm1, i64 %32, i1 false)

; Static global arrays
@perm = dso_local global [12 x i32] zeroinitializer
@perm1 = dso_local global [12 x i32] zeroinitializer
```

**Key optimizations applied by LLVM:**
- SIMD vectorization (4 elements per cycle)
- Static array allocation
- memcpy intrinsic for bulk copy
- Loop unrolling

### BMB Version

```llvm
; Scalar initialization (1 element per iteration)
%call6 = call i64 @array_set(ptr %call1, i32 %i4, i64 %arg_sext)

; Uses heap allocation
%call = call ptr @array_new(i32 %0)  ; malloc

; Loop-based array copy
%call17 = call i64 @array_get(ptr %call1, i32 %i16)
%call19 = call i64 @array_set(ptr %call, i32 %i18, i64 %call17)
```

**Optimization blockers:**
- Dynamic allocation prevents LLVM from knowing array size
- Function calls (even with alwaysinline) add overhead
- No vectorization possible without static sizes

---

## Root Cause Analysis

### 1. Heap Allocation (Major Impact: ~50%)

| Aspect | C | BMB |
|--------|---|-----|
| Allocation | Static global `int arr[12]` | `malloc(n * 8)` |
| Size known | Yes (compile time) | No (runtime) |
| SIMD possible | Yes | No |

**Why BMB uses heap:**
- BMB lacks fixed-size array syntax (`int arr[12]`)
- Current array handling requires malloc for element assignment

### 2. SIMD Vectorization (Major Impact: ~40%)

C initialization loop is vectorized:
```llvm
store <4 x i32> %11, ptr %13, align 16  ; 4 elements at once
```

BMB initialization is scalar:
```llvm
call i64 @array_set(ptr %call1, i32 %i4, i64 %val)  ; 1 element at a time
```

**Why BMB can't vectorize:**
- Dynamic allocation prevents size-based vectorization
- Pointer aliasing unknown

### 3. Array Copy (Moderate Impact: ~10%)

C uses intrinsic:
```llvm
@llvm.memcpy.p0.p0.i64(ptr @perm, ptr @perm1, i64 40, i1 false)
```

BMB uses loop:
```llvm
while i < n { array_set(perm, i, array_get(perm1, i)); i = i + 1 }
```

---

## Improvement Strategies

### Strategy A: Add Fixed-Size Arrays (Recommended)

**Language change required:**

```bmb
// New syntax for fixed-size arrays
fn fannkuch(n: i64) -> i64 = {
    let perm: [i64; 12] = [0; 12];    // Stack-allocated
    let perm1: [i64; 12] = [0; 12];
    ...
}
```

**Benefits:**
- Enables SIMD vectorization
- Stack allocation (faster)
- Compile-time size known

**Effort:** High (parser, AST, type system, codegen changes)

### Strategy B: Recognize memcpy Pattern (Quick Win)

**MIR optimization:**
Detect pattern:
```
i = 0
while i < n { dst[i] = src[i]; i += 1 }
```
Lower to:
```llvm
@llvm.memcpy(dst, src, n * 8)
```

**Benefits:**
- Moderate speedup for array copy
- No language change needed

**Effort:** Medium (MIR pass)

### Strategy C: Static Allocation Hint

**Annotation approach:**
```bmb
@static(12)
fn array_new(n: i64) -> *i64 = ...;
```

**Benefits:**
- Enables some optimizations
- Minimal language change

**Effort:** Medium

---

## Projected Impact

| Strategy | Impact | Effort | Recommended |
|----------|--------|--------|-------------|
| A: Fixed arrays | ~50% faster | High | ✅ Long-term |
| B: memcpy pattern | ~10% faster | Medium | ✅ Quick win |
| C: Static hints | ~20% faster | Medium | Maybe |

**Combined projection:**
- Current: 2.12x slower
- After Strategy B: ~1.9x slower
- After Strategy A: ~1.1x slower (Gate #3.1 target)

---

## Conclusion

To achieve Gate #3.1 (≤1.10x C) for fannkuch:

1. **Short-term**: Implement memcpy pattern detection in MIR
2. **Long-term**: Add fixed-size array support to BMB language

The fundamental issue is that BMB lacks a way to express fixed-size, stack-allocated arrays that LLVM can optimize with SIMD.
