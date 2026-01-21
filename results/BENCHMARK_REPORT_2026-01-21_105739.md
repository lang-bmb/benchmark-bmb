# BMB Benchmark Full Report

**Generated:** 2026-01-21_105739
**Iterations:** 3 (Warmup: 1)

## Summary

| Metric | Count |
|--------|-------|
| Total Benchmarks | 48 |
| FAST (BMB < C) | 17 |
| OK (within 10%) | 16 |
| SLOW (>10% slower) | 14 |
| FAILED | 1 |

## Results by Category

### COMPUTE

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| binary_trees | 81 | 88 | 91 | 1.086 | ✓ OK |
| fannkuch | 66 | 140 | 144 | 2.121 | ⚠️ SLOW |
| fasta | 5 | 6 | 5 | 1.2 | ⚠️ SLOW |
| fibonacci | 16 | 23 | 22 | 1.438 | ⚠️ SLOW |
| hash_table | 8 | 4 | 9 | 0.5 | ✅ FAST |
| k-nucleotide | 5 | 5 | 5 | 1 | ✓ OK |
| mandelbrot | 5 | 6 | 6 | 1.2 | ⚠️ SLOW |
| n_body | 22 | 5 | 5 | 0.227 | ✅ FAST |
| reverse-complement | 5 | 5 | 6 | 1 | ✓ OK |
| spectral_norm | 5 | 4 | 5 | 0.8 | ✅ FAST |

### CONTRACT

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| aliasing | 5 | 5 | 5 | 1 | ✓ OK |
| bounds_check | 7 | 4 | 5 | 0.571 | ✅ FAST |
| branch_elim | 5 | 4 | 5 | 0.8 | ✅ FAST |
| invariant_hoist | 4 | 4 | 5 | 1 | ✓ OK |
| null_check | 4 | 4 | 5 | 1 | ✓ OK |
| purity_opt | 4 | 5 | 5 | 1.25 | ⚠️ SLOW |

### CONTRACT_OPT

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| bounds_elim | 5 | 4 | N/A | 0.8 | ✅ FAST |
| branch_elim | 5 | 5 | N/A | 1 | ✓ OK |
| loop_invariant | 5 | 4 | N/A | 0.8 | ✅ FAST |
| null_elim | 4 | 4 | N/A | 1 | ✓ OK |

### MEMORY

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| cache_stride | 6 | 5 | N/A | 0.833 | ✅ FAST |
| memory_copy | 4 | 5 | N/A | 1.25 | ⚠️ SLOW |
| pointer_chase | 5 | 6 | N/A | 1.2 | ⚠️ SLOW |
| simd_sum | 4 | 6 | N/A | 1.5 | ⚠️ SLOW |
| stack_allocation | 4 | 4 | N/A | 1 | ✓ OK |

### REAL_WORLD

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| brainfuck | 5 | N/A | 4 | N/A | ❌ BMB_FAIL |
| csv_parse | 6 | 4 | 5 | 0.667 | ✅ FAST |
| http_parse | 7 | 16 | 8 | 2.286 | ⚠️ SLOW |
| json_parse | 14 | 11 | 4 | 0.786 | ✅ FAST |
| json_serialize | 11 | 16 | 8 | 1.455 | ⚠️ SLOW |
| lexer | 5 | 4 | 5 | 0.8 | ✅ FAST |
| sorting | 16 | 4 | 45 | 0.25 | ✅ FAST |

### SURPASS

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| graph_traversal | 6 | 4 | N/A | 0.667 | ✅ FAST |
| matrix_multiply | 4 | 4 | N/A | 1 | ✓ OK |
| sort_presorted | 5 | 5 | N/A | 1 | ✓ OK |
| string_search | 5 | 5 | N/A | 1 | ✓ OK |
| tree_balance | 6 | 5 | N/A | 0.833 | ✅ FAST |

### SYSCALL

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| file_io_seq | 642 | 676 | N/A | 1.053 | ✓ OK |
| process_spawn | 545 | 546 | N/A | 1.002 | ✓ OK |
| syscall_overhead | 32 | 87 | N/A | 2.719 | ⚠️ SLOW |

### ZERO_OVERHEAD

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| aliasing_proof | 4 | 5 | N/A | 1.25 | ⚠️ SLOW |
| bounds_check_proof | 6 | 4 | N/A | 0.667 | ✅ FAST |
| null_check_proof | 5 | 6 | N/A | 1.2 | ⚠️ SLOW |
| overflow_proof | 4 | 4 | N/A | 1 | ✓ OK |
| purity_proof | 5 | 5 | N/A | 1 | ✓ OK |

### BOOTSTRAP

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| lex_bootstrap | 8 | 4 | 7 | 0.5 | ✅ FAST |
| parse_bootstrap | 4 | 5 | 4 | 1.25 | ⚠️ SLOW |
| typecheck_bootstrap | 17 | 4 | 69 | 0.235 | ✅ FAST |

## Gate Verification

### Gate #3.1: Compute ≤ 1.10x C
- **Result:** 6 / 10 passed
- **Status:** ❌ FAILED

### Gate #3.2: Bounds check 0% overhead
- **Average BMB/C ratio:** 0.679
- **Status:** ✅ PASSED

### Gate #3.4: 3+ benchmarks faster than C
- **Faster count:** 17
- **Status:** ✅ PASSED
