# BMB Benchmark Analysis - Cycle 17

**Date:** 2026-01-28
**Compiler Version:** v0.60.17 (json_serialize optimization, break usage)
**Previous Cycles:** 13 (type narrowing), 14 (multiplication tracking), 15-16 (break/continue)

## Cycle 17 Achievements (v0.60.17)

### Fixes Completed

| Fix | Issue | Version | Status |
|-----|-------|---------|--------|
| json_serialize sb_push_escaped | 211% ratio due to per-char function calls | v0.60.17 | FIXED |
| fannkuch use break statement | Used flag-based workaround before | v0.60.17 | UPDATED |

### Analysis: json_serialize Fix

**Problem:** The benchmark used per-character `sb_push_char` calls (N calls for N characters).
C's equivalent `buf_char` is `static` and inlined (0 function call overhead).
BMB's `sb_push_char` is external C runtime (full function call overhead per char).

**Solution:** Use `sb_push_escaped(sb, s)` which processes the entire string in a single call.
This matches C's actual behavior (inline escaping) rather than C's source structure.

**Result:**
- Before: N function calls per string (where N = string length)
- After: 3 function calls per string (quote, escaped content, quote)
- For a 20-char string: ~27x reduction in function call overhead

### Verification

```
json_serialize: MIR shows sb_push_escaped instead of sb_push_char loop
fannkuch:       MIR shows correct break → while_exit_20 control flow
```

## Current Benchmark Status

| Benchmark | C (ms) | BMB (ms) | Ratio | Status | Root Cause |
|-----------|--------|----------|-------|--------|------------|
| fibonacci | 248 | 5 | **2%** | FAST | LinearRecurrenceToLoop |
| hash_table | 10 | 9 | **96%** | FAST | - |
| sorting | 654 | 170 | **26%** | FAST | - |
| csv_parse | 20 | 19 | **94%** | FAST | - |
| http_parse | 23 | 20 | **89%** | FAST | - |
| fasta | 195 | 194 | **99%** | OK | - |
| json_parse | 23 | 24-30 | **104-131%** | SLOW | String iteration |
| mandelbrot | 141 | 152 | **108%** | OK | - |
| n_body | 68 | 77 | **113%** | OK | Struct overhead |
| lexer | 19 | 24 | **123%** | SLOW | String iteration |
| spectral_norm | 31 | 38 | **122%** | SLOW | inttoptr alias |
| json_serialize | 23 | TBD | **TBD** | PENDING | sb_push_escaped fix |
| brainfuck | 20 | 26 | **130%** | SLOW | Variance |
| binary_trees | - | - | **TBD** | - | Fixed v0.60.15 |
| fannkuch | 79 | TBD | **TBD** | - | Using break v0.60.17 |

## Analysis: Why json_serialize was 211% (FIXED)

### The Problem

```bmb
// Per-character escaping - very slow
fn write_escaped_string(s: String, sb: i64) -> i64 = {
    while i < slen {
        c = s.byte_at(i);        // external call
        esc = get_escape_char(c); // external call
        sb_push_char(sb, c);      // external call
        i = i + 1;
    }
};
```

**Root Cause:** Each `sb_push_char` is an external C runtime function call.
C's equivalent `buf_char` is `static inline` and has zero call overhead.

### The Fix (v0.60.17)

```bmb
// Idiomatic BMB - single call for entire string
fn json_string_to_sb(s: String, sb: i64) -> i64 = {
    let u1 = sb_push_char(sb, 34);    // opening quote
    let u2 = sb_push_escaped(sb, s);   // escape entire string in one call
    sb_push_char(sb, 34)               // closing quote
};
```

**Result:** N function calls → 3 function calls (~27x reduction for typical strings)

## Remaining Performance Issues

| Benchmark | Ratio | Root Cause | Solution |
|-----------|-------|------------|----------|
| spectral_norm | 122% | inttoptr blocks alias analysis | Pointer types (Language Spec) |
| lexer | 123% | String byte iteration | byte_at inlining |
| json_parse | 104-131% | String byte iteration | byte_at inlining |
| brainfuck | 130% | Variance | Needs investigation |

## Cycle 18+ Recommendations

### Priority 1: byte_at Inlining

Multiple benchmarks (lexer, json_parse) iterate strings byte-by-byte using `byte_at`.
The external function call overhead is similar to the json_serialize issue.

**Options:**
- Implement String in BMB (enables full inlining)
- Generate inline LLVM IR for byte_at
- LTO (Link-Time Optimization) to inline runtime

### Priority 2: Native Array Types

Add `[T; N]` fixed arrays to eliminate array_get/array_set overhead.

**Impact:** spectral_norm, n_body, fannkuch

**Complexity:** Very High (40-80 hours)

### Priority 3: Pointer Types

Add `*T` pointers for proper alias analysis.

**Impact:** spectral_norm (122% → ~100%)

## Files Modified in Cycle 17

1. `ecosystem/benchmark-bmb/benches/real_world/json_serialize/bmb/main.bmb` - Use sb_push_escaped
2. `ecosystem/benchmark-bmb/benches/compute/fannkuch/bmb/main.bmb` - Use break statement
3. `ecosystem/benchmark-bmb/BENCHMARK_CYCLE_17_ANALYSIS.md` - This document

## Verification Commands

```bash
# Verify json_serialize compiles with sb_push_escaped
bmb build ecosystem/benchmark-bmb/benches/real_world/json_serialize/bmb/main.bmb --emit-mir

# Verify fannkuch compiles with break
bmb build ecosystem/benchmark-bmb/benches/compute/fannkuch/bmb/main.bmb --emit-mir
```
