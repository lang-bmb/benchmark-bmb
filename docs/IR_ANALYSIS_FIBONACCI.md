# Fibonacci IR Analysis

**Date**: 2026-02-05
**BMB Version**: v0.69.0
**Performance Gap**: 1.44x slower than C

## Summary

The 1.44x performance gap is caused by LLVM optimizing C's version completely at compile time, while BMB's version runs at runtime.

**C (after -O3)**: Entire computation constant-folded
**BMB**: Loop runs 1 billion times at runtime

---

## IR Comparison

### C Version (after opt -O3)

```llvm
define dso_local noundef i32 @main() local_unnamed_addr #1 {
  ; ENTIRE computation reduced to a constant!
  %1 = tail call i32 @printf(ptr @.str, i64 noundef -5860475048709551616)
  ret i32 0
}
```

LLVM computed `fibonacci(50) * 1000000000` at compile time and printed the constant.

### BMB Version

```llvm
define i64 @bmb_user_main() #6 {
entry:
  ...
  br label %while_cond_0

while_cond_0:                                     ; preds = %while_body_1, %entry
  %lt = icmp slt i64 %i1, 1000000000
  br i1 %lt, label %while_body_1, label %while_exit_2

while_body_1:                                     ; preds = %while_cond_0
  %call = call i64 @fibonacci_iter(i32 50)  ; Called 1 billion times!
  ...
  br label %while_cond_0
```

The loop still exists and runs 1 billion times.

---

## Root Cause: Missing Function Attributes

### C fibonacci_iter attributes:
```llvm
attributes #0 = {
  nofree norecurse nosync nounwind
  memory(none)  ; <-- KEY: No memory access
  ...
}
```

### BMB fibonacci_iter attributes:
```llvm
attributes #6 = {
  mustprogress nounwind willreturn
  ; MISSING: memory(none)
}
```

The missing `memory(none)` attribute prevents LLVM from:
1. Recognizing the function is pure (no side effects)
2. Hoisting the call out of the loop (LICM)
3. Constant-folding the result

---

## Why BMB Lacks memory(none)

BMB's fibonacci_iter uses `alloca` for local variables:

```llvm
define i64 @fibonacci_iter(i32 %0) #6 {
entry:
  %b = alloca i64, align 8
  %i = alloca i32, align 4
  %a = alloca i64, align 8
  store i64 0, ptr %a, align 4
  ...
}
```

Even though these allocas don't escape, BMB doesn't add `memory(none)` because:
1. The function technically writes to memory (stack allocas)
2. BMB's attribute inference is conservative

---

## Solution: Pure Function Annotation

### Strategy A: Automatic Pure Detection (Recommended)

During MIR/codegen, detect functions that:
1. Only access local allocas
2. Don't call impure functions
3. Don't access global state

Add `memory(none)` attribute automatically.

### Strategy B: Explicit @pure Annotation

Allow users to mark pure functions:
```bmb
@pure
fn fibonacci_iter(n: i64) -> i64 = { ... }
```

Generate `memory(none)` for marked functions.

### Strategy C: Promote Allocas Early

Run mem2reg before emitting IR to eliminate allocas:
```llvm
; Before: uses allocas
%a = alloca i64
store i64 0, ptr %a

; After mem2reg: uses SSA values
%a.0 = i64 0
```

This may allow LLVM to infer `memory(none)`.

---

## Impact Analysis

| Optimization | C | BMB |
|--------------|---|-----|
| mem2reg | ✅ Applied | ✅ Applied (but late) |
| Function attribute inference | ✅ `memory(none)` | ❌ Missing |
| LICM (loop hoisting) | ✅ Hoisted | ❌ Not hoisted |
| Constant folding | ✅ Full | ❌ Partial |
| Final result | Constant | Runtime loop |

---

## Projected Impact

| Strategy | Impact | Effort |
|----------|--------|--------|
| A: Auto pure detection | ~100% fix (matches C) | Medium |
| B: @pure annotation | ~100% fix (user effort) | Low |
| C: Early mem2reg | ~50% improvement | Low |

**Current**: 1.44x slower
**After fix**: ≈1.0x (same as C)

---

## Conclusion

The fibonacci gap is entirely due to missing function attributes. BMB should:

1. **Short-term**: Add `@pure` annotation support
2. **Medium-term**: Implement automatic pure function detection
3. **Verify**: After fix, LLVM should constant-fold like C

This is not an algorithmic issue - both use identical O(n) algorithms. It's a metadata/attribute issue that prevents LLVM optimization.
