# benchmark-bmb

> Standard Benchmarking Suite for BMB Language

BMB 언어의 표준 벤치마크 스위트. C, BMB 간 성능 비교를 제공합니다.

## Performance Summary (v0.60.49)

**Total Benchmarks**: 30 (24 compute + 6 real-world)
**Build Success**: 30/30 (100%)
**BMB Faster than C -O3**: 6/11 key benchmarks (55%)
**Near Parity (±20%)**: 4/11 (36%)

### BMB Faster than C -O3

| Benchmark | BMB | C -O3 | Speedup | Category |
|-----------|-----|-------|---------|----------|
| ackermann | 0.04s | 11.6s | **261x** | TCO |
| nqueen | 0.98s | 6.87s | **7x** | TCO |
| sorting | 0.25s | 0.68s | **2.7x** | TCO |
| fibonacci | 0.078s | 0.092s | **1.18x** | Compute |
| gcd | 0.087s | 0.092s | **1.06x** | Compute |

### Near Parity (±20%)

| Benchmark | BMB | C -O3 | Ratio |
|-----------|-----|-------|-------|
| mandelbrot | 0.16s | 0.16s | 1.04x |
| sieve | 0.026s | 0.024s | 1.08x |
| hash_table | 0.015s | 0.012s | 1.18x |

### C -O3 Faster (LLVM Limitation)

| Benchmark | BMB | C -O3 | C (Clang) | Ratio | Notes |
|-----------|-----|-------|-----------|-------|-------|
| spectral_norm | 0.05s | 0.035s | 0.05s | 1.43x | See below |

**Note**: spectral_norm shows identical performance between BMB and Clang (both LLVM-based).
The 43% gap vs GCC is due to GCC's superior loop strength reduction for `i + j` patterns
in nested loops. This is an LLVM limitation, not BMB-specific.

### Output Correctness

| Benchmark | Status | Notes |
|-----------|--------|-------|
| spectral_norm | ✓ | Float output: 1.274224148 |
| n_body | ✓ | Float output: -0.169075164 |
| hash_table | ✓ | Hash operations verified |
| All others | ✓ | Integer output matches C |

## v0.60.49 Changes

- **sieve**: Fixed to use byte arrays (`store_u8`/`load_u8`) instead of 64-bit arrays
  - Memory usage: 8x reduction (800KB → 100KB)
  - Performance: 1.23x → 1.08x (near parity)

- **spectral_norm**: Documented as LLVM vs GCC difference
  - BMB matches Clang performance exactly
  - GCC applies strength reduction that LLVM doesn't

## Benchmark Categories

### Compute-Intensive (24 benchmarks)

Standard benchmarks from [The Computer Language Benchmarks Game](https://benchmarksgame-team.pages.debian.net/benchmarksgame/).

| Benchmark | Description | TCO Benefit |
|-----------|-------------|-------------|
| ackermann | Ackermann function | ✓ (261x faster) |
| nqueen | N-Queens problem | ✓ (7x faster) |
| sorting | Quicksort/Mergesort | ✓ (2.7x faster) |
| fibonacci | Fibonacci sequence | ✓ (1.18x faster) |
| gcd | Greatest common divisor | ✓ (1.06x faster) |
| mandelbrot | Fractal generation | - |
| spectral_norm | Eigenvalue approximation | - |
| binary_trees | Tree allocation | - |
| fannkuch | Permutation flipping | - |
| n_body | N-body simulation | - |
| sieve | Sieve of Eratosthenes | - |
| matrix_multiply | Matrix multiplication | - |
| primes_count | Prime counting | - |
| perfect_numbers | Perfect number search | - |
| collatz | Collatz conjecture | - |
| digital_root | Digital root calculation | - |
| sum_of_squares | Sum of squares | - |
| hash_table | Hash table operations | - |
| fasta | FASTA file generation | - |
| pidigits | Pi digit calculation | - |
| regex_redux | Pattern matching | - |
| k-nucleotide | Nucleotide counting | - |
| reverse-complement | DNA complement | - |
| tak | Tak function | - |

### Real-World (6 benchmarks)

| Benchmark | Description | BMB vs C |
|-----------|-------------|----------|
| sorting | Quicksort benchmark | 2.7x faster |
| json_serialize | JSON serialization | ~1.0x (parity) |
| csv_parse | CSV parsing | ~1.0x (parity) |
| json_parse | JSON parsing | ~1.0x (parity) |
| http_parse | HTTP parsing | ~1.0x (parity) |
| lexer | Lexer benchmark | ~1.0x (parity) |

## Running Benchmarks

```bash
# Build BMB compiler
cd /path/to/lang-bmb
cargo build --release --features llvm --target x86_64-pc-windows-gnu

# Set runtime path
export BMB_RUNTIME_PATH="/path/to/lang-bmb/bmb/runtime"

# Build and run a benchmark
./target/x86_64-pc-windows-gnu/release/bmb build benches/compute/fibonacci/bmb/main.bmb -o fib.exe
./fib.exe

# Build C version for comparison
gcc -O3 -march=native -o fib_c.exe benches/compute/fibonacci/c/main.c -lm
./fib_c.exe
```

## Methodology

1. **Same algorithm**: Identical algorithm across C and BMB
2. **Fair optimization**: C uses `-O3 -march=native`, BMB uses LLVM `-O3` with scalarizer
3. **Median timing**: 3-5 runs, median reported (first run excluded for cold start)
4. **Output validation**: Verify identical output

## Key Features

### Tail Call Optimization (TCO)

BMB automatically optimizes tail-recursive functions into loops:

- **ackermann**: 261x faster (deep recursion → loop)
- **nqueen**: 7x faster (backtracking → TCO)
- **sorting**: 2.7x faster (recursive sort → loop)

### Float Output

BMB supports proper floating-point output with `println_f64()`:

```bmb
fn main() -> i64 = {
    let result = 1.274224148;
    let _p = println_f64(result);  // Prints: 1.274224148
    0
};
```

## License

MIT License
