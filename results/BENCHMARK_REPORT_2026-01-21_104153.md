# BMB Benchmark Full Report

**Generated:** 2026-01-21_104153
**Iterations:** 3 (Warmup: 1)

## Summary

| Metric | Count |
|--------|-------|
| Total Benchmarks | 48 |
| FAST (BMB < C) | 24 |
| OK (within 10%) | 7 |
| SLOW (>10% slower) | 14 |
| FAILED | 3 |

## Results by Category

### COMPUTE

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| binary_trees | 189 | 189 | 181 | 1 | ✓ OK |
| fannkuch | 107 | 208 | 282 | 1.944 | ⚠️ SLOW |
| fasta | 16 | 8 | 10 | 0.5 | ✅ FAST |
| fibonacci | 32 | 41 | 46 | 1.281 | ⚠️ SLOW |
| hash_table | 15 | N/A | 18 | N/A | ❌ BMB_FAIL |
| k-nucleotide | 11 | N/A | 8 | N/A | ❌ BMB_FAIL |
| mandelbrot | 8 | 7 | 15 | 0.875 | ✅ FAST |
| n_body | 48 | 9 | 9 | 0.188 | ✅ FAST |
| reverse-complement | 8 | 7 | 9 | 0.875 | ✅ FAST |
| spectral_norm | 9 | 12 | 11 | 1.333 | ⚠️ SLOW |

### CONTRACT

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| aliasing | 8 | 11 | 15 | 1.375 | ⚠️ SLOW |
| bounds_check | 10 | 9 | 10 | 0.9 | ✅ FAST |
| branch_elim | 9 | 8 | 9 | 0.889 | ✅ FAST |
| invariant_hoist | 10 | 8 | 9 | 0.8 | ✅ FAST |
| null_check | 9 | 8 | 15 | 0.889 | ✅ FAST |
| purity_opt | 12 | 9 | 14 | 0.75 | ✅ FAST |

### CONTRACT_OPT

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| bounds_elim | 9 | 10 | N/A | 1.111 | ⚠️ SLOW |
| branch_elim | 13 | 7 | N/A | 0.538 | ✅ FAST |
| loop_invariant | 11 | 8 | N/A | 0.727 | ✅ FAST |
| null_elim | 10 | 9 | N/A | 0.9 | ✅ FAST |

### MEMORY

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| cache_stride | 8 | 10 | N/A | 1.25 | ⚠️ SLOW |
| memory_copy | 7 | 11 | N/A | 1.571 | ⚠️ SLOW |
| pointer_chase | 12 | 9 | N/A | 0.75 | ✅ FAST |
| simd_sum | 8 | 8 | N/A | 1 | ✓ OK |
| stack_allocation | 8 | 8 | N/A | 1 | ✓ OK |

### REAL_WORLD

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| brainfuck | 11 | N/A | 16 | N/A | ❌ BMB_FAIL |
| csv_parse | 14 | 9 | 15 | 0.643 | ✅ FAST |
| http_parse | 15 | 28 | 15 | 1.867 | ⚠️ SLOW |
| json_parse | 10 | 9 | 15 | 0.9 | ✅ FAST |
| json_serialize | 30 | 30 | 24 | 1 | ✓ OK |
| lexer | 9 | 9 | 11 | 1 | ✓ OK |
| sorting | 27 | 10 | 116 | 0.37 | ✅ FAST |

### SURPASS

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| graph_traversal | 14 | 12 | N/A | 0.857 | ✅ FAST |
| matrix_multiply | 8 | 11 | N/A | 1.375 | ⚠️ SLOW |
| sort_presorted | 8 | 8 | N/A | 1 | ✓ OK |
| string_search | 14 | 16 | N/A | 1.143 | ⚠️ SLOW |
| tree_balance | 11 | 9 | N/A | 0.818 | ✅ FAST |

### SYSCALL

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| file_io_seq | 1913 | 1748 | N/A | 0.914 | ✅ FAST |
| process_spawn | 1424 | 1320 | N/A | 0.927 | ✅ FAST |
| syscall_overhead | 85 | 237 | N/A | 2.788 | ⚠️ SLOW |

### ZERO_OVERHEAD

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| aliasing_proof | 12 | 18 | N/A | 1.5 | ⚠️ SLOW |
| bounds_check_proof | 15 | 13 | N/A | 0.867 | ✅ FAST |
| null_check_proof | 8 | 10 | N/A | 1.25 | ⚠️ SLOW |
| overflow_proof | 10 | 8 | N/A | 0.8 | ✅ FAST |
| purity_proof | 9 | 10 | N/A | 1.111 | ⚠️ SLOW |

### BOOTSTRAP

| Benchmark | C (ms) | BMB (ms) | Rust (ms) | BMB/C | Status |
|-----------|--------|----------|-----------|-------|--------|| lex_bootstrap | 16 | 10 | 18 | 0.625 | ✅ FAST |
| parse_bootstrap | 9 | 9 | 9 | 1 | ✓ OK |
| typecheck_bootstrap | 36 | 8 | 163 | 0.222 | ✅ FAST |

## Gate Verification

### Gate #3.1: Compute ≤ 1.10x C
- **Result:** 5 / 8 passed
- **Status:** ❌ FAILED

### Gate #3.2: Bounds check 0% overhead
- **Average BMB/C ratio:** 0.959
- **Status:** ✅ PASSED

### Gate #3.4: 3+ benchmarks faster than C
- **Faster count:** 24
- **Status:** ✅ PASSED
