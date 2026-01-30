# BMB Benchmark Report - Cycle 27 (v0.60.41)

## Summary

### Key Improvement: Unreachable Block Elimination

Added `UnreachableBlockElimination` pass that removes basic blocks that cannot be reached from the entry block. This cleans up dead code left after `SimplifyBranches` converts constant-condition branches to unconditional gotos.

### Before
```llvm
define i64 @test() {
entry:
  br i1 true, label %then_0, label %else_1  ; always takes then_0

then_0:
  br label %merge_2

else_1:                            ; <-- UNREACHABLE
  br label %merge_2

merge_2:
  %_t2 = phi i64 [ 1, %then_0 ], [ 0, %else_1 ]
  ret i64 %_t2
}
```

### After
```llvm
define i64 @test() {
entry:
  br label %then_0                 ; unconditional

then_0:
  br label %merge_2

merge_2:                           ; else_1 REMOVED
  %_t2 = phi i64 [ 1, %then_0 ]    ; only one predecessor now
  ret i64 %_t2
}
```

### Improvements
- **Eliminated**: Unreachable blocks after branch simplification
- **Simplified**: PHI nodes with references to removed blocks
- **Smaller**: Generated IR code size reduced

---

## Code Changes

### `bmb/src/mir/optimize.rs`

#### 1. Added `UnreachableBlockElimination` pass

```rust
pub struct UnreachableBlockElimination;

impl OptimizationPass for UnreachableBlockElimination {
    fn name(&self) -> &'static str {
        "unreachable_block_elimination"
    }

    fn run_on_function(&self, func: &mut MirFunction) -> bool {
        // Find all reachable blocks starting from entry
        let mut reachable: HashSet<String> = HashSet::new();
        let mut worklist: Vec<String> = vec!["entry".to_string()];

        while let Some(label) = worklist.pop() {
            if reachable.contains(&label) { continue; }
            reachable.insert(label.clone());
            // Add successors based on terminator
            // ...
        }

        // Remove unreachable blocks
        func.blocks.retain(|b| reachable.contains(&b.label));

        // Update PHI nodes to remove references to removed blocks
        // ...
    }
}
```

#### 2. Added to optimization pipeline

```rust
// In OptLevel::Release and OptLevel::Aggressive:
pipeline.add_pass(Box::new(SimplifyBranches));
// v0.60.41: Remove unreachable blocks after branch simplification
pipeline.add_pass(Box::new(UnreachableBlockElimination));
pipeline.add_pass(Box::new(IfElseToSwitch));
```

---

## Verification

Block count comparison for test function:

| Mode | Blocks | Status |
|------|--------|--------|
| Debug (no opt) | 6 | else_1 exists |
| Release (opt) | 5 | else_1 removed |

The `else_1` block is correctly eliminated when optimization is enabled.

---

## Benchmark Status

**Note:** LLVM `opt` tool remains blocked by Application Control policy.
Full benchmark comparison is not possible with current infrastructure.

### Reference Results (Cycle 24 with full optimization)

| Benchmark | Ratio | Status |
|-----------|-------|--------|
| binary_trees | ~100% | OK |
| mandelbrot | ~108% | OK |
| spectral_norm | ~114% | OK |
| fannkuch | ~103% | OK |
| fasta | ~114% | Slow |
| n_body | ~100% | OK |
| fibonacci | ~7% | Demo |
| sorting | ~23% | Demo |

---

## Combined Improvements (Cycles 25-27)

| Cycle | Feature | Impact |
|-------|---------|--------|
| 25 | `null` keyword comparison | Eliminates null_ptr() for new code |
| 26 | `null_ptr()` constant folding | Eliminates null_ptr() for existing code |
| 27 | Unreachable block elimination | Cleaner IR after branch simplification |

---

## Recommendations for Cycle 28

### Priority 1: Infrastructure
- **Resolve LLVM `opt` access** - Critical for benchmark validation
- Consider embedding LLVM passes in BMB compiler

### Priority 2: Language Features
1. **Struct array syntax** - Fix fasta benchmark fairness
2. **Static array allocation** - Fix n_body benchmark fairness

### Priority 3: Optimization
1. **Phi simplification** - When phi has one value, replace with copy
2. **Block merging** - Merge blocks connected by unconditional jumps

---

## Files Modified

- `bmb/src/mir/optimize.rs`:
  - Added `UnreachableBlockElimination` struct and implementation
  - Added to Release and Aggressive optimization pipelines

---

**Version:** v0.60.41
