# BMB Benchmark Report - Cycle 29 (v0.60.44)

## Summary

### MIR Optimization Improvements

Added two new MIR optimization passes to reduce CFG complexity and enable further optimizations.

### New Passes

#### 1. PhiSimplification

Replaces PHI nodes with simpler instructions when possible:
- Single-value phi → Copy or Const instruction
- All-same-value phi → Copy or Const instruction

```
Before:                          After:
%x = phi [1, then_0]      →     %x = const 1
```

#### 2. BlockMerging

Merges blocks connected by unconditional jumps when the target has only one predecessor:

```
Before:                          After:
entry:                           entry:
  goto then_0                      %x = const 1
then_0:                            ret %x
  %x = const 1
  ret %x
```

---

## Code Changes

### `bmb/src/mir/optimize.rs`

#### PhiSimplification pass (lines 1056-1131)
```rust
pub struct PhiSimplification;

impl OptimizationPass for PhiSimplification {
    fn name(&self) -> &'static str { "phi_simplification" }

    fn run_on_function(&self, func: &mut MirFunction) -> bool {
        // For each phi with single value or all-same values:
        // - Place operand → MirInst::Copy
        // - Constant operand → MirInst::Const
    }
}
```

#### BlockMerging pass (lines 1133-1255)
```rust
pub struct BlockMerging;

impl OptimizationPass for BlockMerging {
    fn name(&self) -> &'static str { "block_merging" }

    fn run_on_function(&self, func: &mut MirFunction) -> bool {
        // Find blocks ending in Goto where target has single predecessor
        // Merge target's instructions into source block
        // Update all references
    }
}
```

#### Pipeline Integration
Added to both Release and Aggressive pipelines after UnreachableBlockElimination:
```rust
pipeline.add_pass(Box::new(UnreachableBlockElimination));
pipeline.add_pass(Box::new(PhiSimplification));  // v0.60.44
pipeline.add_pass(Box::new(BlockMerging));       // v0.60.44
pipeline.add_pass(Box::new(IfElseToSwitch));
```

---

## Verification

### Test: Constant condition phi elimination

```bmb
fn test_phi() -> i64 = {
    let x = if true { 1 } else { 0 };
    x
};
```

**Generated LLVM IR:**
```llvm
define i64 @test_phi() {
entry:
  ret i64 1
}
```

The entire function is reduced to a single return instruction through:
1. SimplifyBranches: `br i1 true` → `goto then_0`
2. UnreachableBlockElimination: Remove `else_1` block
3. PhiSimplification: `phi [1, then_0]` → `const 1`
4. BlockMerging: Merge `then_0` into `entry`
5. DeadCodeElimination: Remove unused instructions

---

## Benchmark Results

### Performance Comparison (llc -O3)

| Benchmark | BMB (Cycle 29) | C (gcc -O2) | Ratio |
|-----------|----------------|-------------|-------|
| spectral_norm | ~70ms | ~32ms | 218% |
| binary_trees | ~100ms | ~82ms | 122% |
| mandelbrot | ~205ms | ~136ms | 151% |

### Comparison with Previous Cycle

| Benchmark | Cycle 28 | Cycle 29 | Change |
|-----------|----------|----------|--------|
| spectral_norm | ~73ms | ~70ms | -4% |
| binary_trees | ~100ms | ~100ms | 0% |
| mandelbrot | ~205ms | ~205ms | 0% |

**Note:** The new passes provide marginal improvement because:
1. These benchmarks have few single-value phi nodes
2. Most blocks already have multiple predecessors
3. The primary benefit is CFG simplification for downstream passes

---

## Optimization Pipeline Order

```
1. AlgebraicSimplification
2. ConstantFolding
3. DeadCodeElimination
4. SimplifyBranches         ← Constant conditions to gotos
5. UnreachableBlockElimination ← Remove dead blocks
6. PhiSimplification        ← NEW: Simplify single-value phis
7. BlockMerging             ← NEW: Merge linear blocks
8. IfElseToSwitch
9. CopyPropagation
10. MemoryLoadCSE
11. GlobalFieldAccessCSE
12. ContractBasedOptimization
13. ContractUnreachableElimination
14. TailCallOptimization
15. TailRecursiveToLoop
16. LinearRecurrenceToLoop
17. LoopInvariantCodeMotion
18. StringConcatOptimization
```

---

## Recommendations for Cycle 30

### Priority 1: Infrastructure
- Continue requesting IT exception for `opt.exe`
- Consider installing LLVM 21 in WSL for optimization

### Priority 2: Language Features
- Struct array syntax (fasta benchmark fairness)
- Static array allocation (n_body benchmark fairness)

### Priority 3: Optimization
- **GVN (Global Value Numbering)** - Eliminate redundant computations
- **Strength Reduction** - Replace expensive operations with cheaper ones
- **Dead Store Elimination** - Remove stores that are never read

---

**Version:** v0.60.44
