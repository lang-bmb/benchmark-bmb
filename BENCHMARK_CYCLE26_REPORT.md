# BMB Benchmark Report - Cycle 26 (v0.60.40)

## Summary

### Key Improvement: `null_ptr()` Constant Folding

The `0 as *T` pattern (commonly used in `null_ptr()` functions) is now constant-folded at compile time, eliminating function call overhead.

### Before (Cycle 24)
```llvm
%call = call ptr @null_ptr()              ; function call overhead
%lhs_ptr = ptrtoint ptr %field_val to i64
%rhs_ptr = ptrtoint ptr %call to i64      ; extra ptrtoint
%ptr_eq = icmp eq i64 %lhs_ptr, %rhs_ptr
```

### After (Cycle 26)
```llvm
%lhs_ptr = ptrtoint ptr %field_val to i64
%ptr_null_eq = icmp eq i64 %lhs_ptr, 0    ; direct comparison with constant 0
```

### Improvements
- **Eliminated**: `call ptr @null_ptr()` function call
- **Eliminated**: Extra `ptrtoint` instruction for call result
- **Result**: 3 instructions → 2 instructions per null check

---

## Code Changes

### `bmb/src/mir/optimize.rs` - Extended `extract_constant_return`

```rust
// v0.60.40: Handle `0 as *T` pattern (null pointer)
// This recognizes functions like `fn null_ptr() -> *T = 0 as *T`
if let MirInst::Cast { dest, src, to_ty, .. } = inst
    && dest.name == place.name
    && matches!(to_ty, MirType::Ptr(_) | MirType::StructPtr(_))
    && matches!(src, Operand::Constant(Constant::Int(0)))
{
    // Null pointer is just constant 0
    return Some(Constant::Int(0));
}
```

This extends `ConstFunctionEval` to recognize that:
- `fn null_ptr() -> *T = 0 as *T` returns constant 0
- All calls to `null_ptr()` can be replaced with constant 0
- This works automatically for any 0-arg function returning a cast of 0 to pointer

---

## Benchmark Status

**Note:** LLVM `opt` tool is blocked by Application Control policy on this machine.
Full benchmarks cannot be run with proper optimizations.

### IR-Level Verification

| Pattern | Cycle 24 | Cycle 26 | Status |
|---------|----------|----------|--------|
| `null_ptr()` calls | 2 per file | 0 per file | ELIMINATED |
| Instructions per null check | 4 | 2 | 50% reduction |

### Reference Results (Cycle 24 with full optimization)

| Benchmark | Ratio | Status |
|-----------|-------|--------|
| binary_trees | 101% | OK |
| mandelbrot | 108% | OK |
| spectral_norm | 114% | OK |
| fannkuch | 103% | OK |
| fasta | 114% | Slow |
| n_body | 100% | OK |
| fibonacci | 7% | Demo (LinearRecurrenceToLoop) |
| sorting | 23% | Demo (TailRecursiveToLoop) |

---

## Combined Improvements (Cycle 25 + 26)

| Feature | Cycle 25 | Cycle 26 |
|---------|----------|----------|
| `null` keyword comparison | Added codegen support | - |
| `null_ptr()` constant folding | - | Added to ConstFunctionEval |
| Mixed ptr/int comparison | Added in codegen | - |

**Result:** Both `null` keyword and `null_ptr()` pattern now generate identical, optimal code.

---

## Backward Compatibility

Existing code using `null_ptr()` pattern:
```bmb
fn null_ptr() -> *Node = 0 as *Node;

fn check(ptr: *Node) -> i64 = {
    let nil = null_ptr();
    if ptr == nil { 1 } else { 0 }
};
```

Is now **automatically optimized** to be as efficient as using `null` keyword:
```bmb
fn check(ptr: *Node) -> i64 = {
    if ptr == null { 1 } else { 0 }
};
```

No code changes required for existing codebases.

---

## Recommendations for Cycle 27

### Priority 1: Resolve Infrastructure
- Fix LLVM `opt` access (Application Control policy)
- Run full benchmark suite with proper optimizations

### Priority 2: Language Features
1. **Struct array syntax** - Fix fasta benchmark fairness
2. **Static array allocation** - Fix n_body benchmark fairness

### Priority 3: Optimization
1. **Branch elimination** - Fold `br i1 true` to unconditional branch
2. **Dead function elimination** - Remove unused `null_ptr()` after constant folding

---

## Files Modified

- `bmb/src/mir/optimize.rs` (lines 1491-1500): Extended `extract_constant_return`

---

## Verification

Test file `test_null_ptr_fold.bmb`:
```bmb
fn null_ptr() -> *Node = 0 as *Node;
fn check_tree(node: *Node) -> i64 = {
    let left = node.left;
    let nil = null_ptr();
    if left == nil { 1 }
    else { 1 + check_tree(node.left) + check_tree(node.right) }
};
```

**Cycle 24**: `call ptr @null_ptr()` present in IR
**Cycle 26**: No `null_ptr()` calls - constant folded to 0

**Version:** v0.60.40
