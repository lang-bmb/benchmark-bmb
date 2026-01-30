# benchmark-bmb

> Standard Benchmarking Suite for BMB Language

BMB 언어의 표준 벤치마크 스위트. C, BMB 간 성능 비교를 제공합니다.

## Performance Summary (v0.60.47)

**Total Benchmarks**: 30 (24 compute + 6 real-world)
**Build Success**: 30/30 (100%)
**BMB Faster than C -O3**: 8/14 key benchmarks (57%)
**Near Parity (±20%)**: 4/14 (29%)

### BMB Faster than C -O3

| Benchmark | BMB | C -O3 | Speedup | Category |
|-----------|-----|-------|---------|----------|
| ackermann | 0.04s | 11.12s | **271x** | TCO |
| nqueen | 0.88s | 6.74s | **7.7x** | TCO |
| sorting | 0.16s | 0.62s | **3.9x** | TCO |
| tak | 0.02s | 0.03s | **1.5x** | TCO |
| fibonacci | 0.02s | 0.02s | **1.2x** | Compute |
| gcd | 0.03s | 0.03s | **1.1x** | Compute |
| hash_table | 0.02s | 0.02s | **1.1x** | Compute |
| fannkuch | 0.08s | 0.08s | **1.0x** | Compute |

### Near Parity (±20%)

| Benchmark | BMB | C -O3 | Ratio |
|-----------|-----|-------|-------|
| mandelbrot | 0.16s | 0.15s | 0.95x |
| binary_trees | 0.10s | 0.09s | 0.93x |
| n_body | 0.08s | 0.07s | 0.89x |
| matrix_multiply | 0.03s | 0.02s | 0.82x |

### C -O3 Faster

| Benchmark | BMB | C -O3 | Ratio |
|-----------|-----|-------|-------|
| sieve | 0.03s | 0.02s | 0.74x |
| spectral_norm | 0.05s | 0.03s | 0.67x |

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
| ackermann | Ackermann function | ✓ (271x faster) |
| nqueen | N-Queens problem | ✓ (7.7x faster) |
| sorting | Quicksort/Mergesort | ✓ (3.9x faster) |
| tak | Tak function | ✓ (1.5x faster) |
| fibonacci | Fibonacci sequence | ✓ (1.2x faster) |
| gcd | Greatest common divisor | ✓ (1.1x faster) |
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
| hash_table | Hash table operations | ✓ (1.1x faster) |
| fasta | FASTA file generation | - |
| pidigits | Pi digit calculation | - |
| regex_redux | Pattern matching | - |
| k-nucleotide | Nucleotide counting | - |
| reverse-complement | DNA complement | - |

### Real-World (6 benchmarks)

| Benchmark | Description | BMB vs C |
|-----------|-------------|----------|
| sorting | Quicksort benchmark | 3.9x faster |
| json_serialize | JSON serialization | ~1.0x (parity) |
| csv_parse | CSV parsing | ~1.0x (parity) |
| json_parse | JSON parsing | ~1.0x (parity) |
| http_parse | HTTP parsing | ~1.0x (parity) |
| lexer | Lexer benchmark | ~1.0x (parity) |

## Directory Structure

```
benchmark-bmb/
├── README.md
├── benches/
│   ├── compute/
│   │   ├── ackermann/{c,bmb}/main.{c,bmb}
│   │   ├── binary_trees/{c,bmb}/main.{c,bmb}
│   │   └── ... (24 benchmarks)
│   └── real_world/
│       ├── brainfuck/{c,bmb}/main.{c,bmb}
│       └── ... (6 benchmarks)
└── results/
```

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

### Requirements

- **C benchmarks**: GCC with `-O3 -march=native`
- **BMB benchmarks**: BMB compiler with LLVM backend
- **Runtime**: `libbmb_runtime.a` in BMB_RUNTIME_PATH

## Methodology

1. **Same algorithm**: Identical algorithm across C and BMB
2. **Fair optimization**: C uses `-O3 -march=native`, BMB uses LLVM `-O3` with scalarizer
3. **Median timing**: 3 runs, median reported (first run excluded for cold start)
4. **Output validation**: Verify identical output

## Key Features

### Tail Call Optimization (TCO)

BMB automatically optimizes tail-recursive functions into loops:

- **ackermann**: 271x faster (deep recursion → loop)
- **nqueen**: 7.7x faster (backtracking → TCO)
- **sorting**: 3.9x faster (recursive sort → loop)

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
