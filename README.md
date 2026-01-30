# benchmark-bmb

> Standard Benchmarking Suite for BMB Language

BMB 언어의 표준 벤치마크 스위트. C, BMB 간 성능 비교를 제공합니다.

## Performance Summary (v0.60.48)

**Total Benchmarks**: 30 (24 compute + 6 real-world)
**Build Success**: 30/30 (100%)
**BMB Faster than C -O3**: 6/11 key benchmarks (55%)
**Near Parity (±20%)**: 3/11 (27%)

### BMB Faster than C -O3

| Benchmark | BMB | C -O3 | Speedup | Category |
|-----------|-----|-------|---------|----------|
| ackermann | 0.04s | 11.6s | **322x** | TCO |
| nqueen | 0.90s | 6.99s | **7.8x** | TCO |
| sorting | 0.15s | 0.63s | **4.1x** | TCO |
| fibonacci | 0.008s | 0.01s | **1.3x** | Compute |
| gcd | 0.025s | 0.026s | **1.04x** | Compute |

### Near Parity (±20%)

| Benchmark | BMB | C -O3 | Ratio |
|-----------|-----|-------|-------|
| mandelbrot | 0.15s | 0.15s | 1.05x |
| hash_table | 0.015s | 0.012s | 1.18x |

### C -O3 Faster

| Benchmark | BMB | C -O3 | Ratio |
|-----------|-----|-------|-------|
| spectral_norm | 0.08s | 0.06s | 1.26x |
| sieve | 0.025s | 0.02s | 1.23x |

### Output Correctness

| Benchmark | Status | Notes |
|-----------|--------|-------|
| spectral_norm | ✓ | Float output: 1.274224148 |
| n_body | ✓ | Float output: -0.169075164 |
| hash_table | ✓ | Count: 95259, 100000, 46445 |
| All others | ✓ | Integer output matches C |

## Benchmark Categories

### Compute-Intensive (24 benchmarks)

Standard benchmarks from [The Computer Language Benchmarks Game](https://benchmarksgame-team.pages.debian.net/benchmarksgame/).

| Benchmark | Description | TCO Benefit |
|-----------|-------------|-------------|
| ackermann | Ackermann function | ✓ (322x faster) |
| nqueen | N-Queens problem | ✓ (7.8x faster) |
| sorting | Quicksort/Mergesort | ✓ (4.1x faster) |
| fibonacci | Fibonacci sequence | ✓ (1.3x faster) |
| gcd | Greatest common divisor | ✓ (1.04x faster) |
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
| sorting | Quicksort benchmark | 4.1x faster |
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

- **ackermann**: 322x faster (deep recursion → loop)
- **nqueen**: 7.8x faster (backtracking → TCO)
- **sorting**: 4.1x faster (recursive sort → loop)

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
