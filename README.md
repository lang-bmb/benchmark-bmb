# benchmark-bmb

> Standard Benchmarking Suite for BMB Language

BMB 언어의 표준 벤치마크 스위트. C, BMB 간 성능 비교를 제공합니다.

## Performance Summary

**Total Benchmarks**: 30 (24 compute + 6 real-world)
**Build Success**: 30/30 (100%)
**BMB Faster than C**: 18/30 (60%)
**Near Parity (±15%)**: 9/30 (30%)

### BMB Faster than C -O3

| Benchmark | BMB | C -O3 | Speedup | Category |
|-----------|-----|-------|---------|----------|
| ackermann | 0.043s | 10.95s | **255x** | TCO |
| nqueen | 0.99s | 6.78s | **6.9x** | TCO |
| sorting | 0.17s | 0.68s | **3.9x** | TCO |
| tak | 0.08s | 0.09s | **1.1x** | TCO |
| n_body | 0.11s | 0.13s | **1.2x** | Compute |
| perfect_numbers | 0.59s | 0.96s | **1.6x** | Compute |
| brainfuck | 0.06s | 0.09s | **1.5x** | Real-World |
| primes_count | 0.03s | 0.04s | **1.3x** | Compute |
| http_parse | 0.06s | 0.11s | **1.8x** | Real-World |
| json_parse | 0.07s | 0.11s | **1.6x** | Real-World |
| json_serialize | 0.08s | 0.11s | **1.4x** | Real-World |

### Near Parity (±15%)

| Benchmark | BMB | C -O3 | Ratio |
|-----------|-----|-------|-------|
| mandelbrot | 0.22s | 0.22s | 1.00x |
| sieve | 0.10s | 0.10s | 1.02x |
| binary_trees | 0.09s | 0.09s | 1.00x |
| fannkuch | 0.08s | 0.08s | 1.05x |
| collatz | 0.02s | 0.02s | 1.04x |
| digital_root | 0.02s | 0.02s | 1.05x |
| sum_of_squares | 0.02s | 0.02s | 1.06x |
| hash_table | 0.02s | 0.02s | 0.95x |
| fasta | 0.05s | 0.04s | 1.12x |

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
| ackermann | Ackermann function | ✓ (255x faster) |
| nqueen | N-Queens problem | ✓ (6.9x faster) |
| sorting | Quicksort/Mergesort | ✓ (3.9x faster) |
| tak | Tak function | ✓ (1.1x faster) |
| fibonacci | Fibonacci sequence | - |
| gcd | Greatest common divisor | - |
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

### Real-World (6 benchmarks)

| Benchmark | Description | BMB vs C |
|-----------|-------------|----------|
| brainfuck | BF interpreter | 1.5x faster |
| http_parse | HTTP parsing | 1.8x faster |
| json_parse | JSON parsing | 1.6x faster |
| json_serialize | JSON serialization | 1.4x faster |
| csv_parse | CSV parsing | 1.5x slower |
| lexer | Lexer benchmark | 1.1x slower |

## Directory Structure

```
benchmark-bmb/
├── README.md
├── benches/
│   ├── compute/
│   │   ├── ackermann/{c,bmb}/main.{c,bmb}
│   │   ├── binary_trees/{c,bmb}/main.{c,bmb}
│   │   ├── collatz/{c,bmb}/main.{c,bmb}
│   │   ├── digital_root/{c,bmb}/main.{c,bmb}
│   │   ├── fannkuch/{c,bmb}/main.{c,bmb}
│   │   ├── fasta/{c,bmb}/main.{c,bmb}
│   │   ├── fibonacci/{c,bmb}/main.{c,bmb}
│   │   ├── gcd/{c,bmb}/main.{c,bmb}
│   │   ├── hash_table/{c,bmb}/main.{c,bmb}
│   │   ├── k-nucleotide/{c,bmb}/main.{c,bmb}
│   │   ├── mandelbrot/{c,bmb}/main.{c,bmb}
│   │   ├── matrix_multiply/{c,bmb}/main.{c,bmb}
│   │   ├── n_body/{c,bmb}/main.{c,bmb}
│   │   ├── nqueen/{c,bmb}/main.{c,bmb}
│   │   ├── perfect_numbers/{c,bmb}/main.{c,bmb}
│   │   ├── pidigits/{c,bmb}/main.{c,bmb}
│   │   ├── primes_count/{c,bmb}/main.{c,bmb}
│   │   ├── regex_redux/{c,bmb}/main.{c,bmb}
│   │   ├── reverse-complement/{c,bmb}/main.{c,bmb}
│   │   ├── sieve/{c,bmb}/main.{c,bmb}
│   │   ├── spectral_norm/{c,bmb}/main.{c,bmb}
│   │   ├── sum_of_squares/{c,bmb}/main.{c,bmb}
│   │   ├── sorting/{c,bmb}/main.{c,bmb}
│   │   └── tak/{c,bmb}/main.{c,bmb}
│   └── real_world/
│       ├── brainfuck/{c,bmb}/main.{c,bmb}
│       ├── csv_parse/{c,bmb}/main.{c,bmb}
│       ├── http_parse/{c,bmb}/main.{c,bmb}
│       ├── json_parse/{c,bmb}/main.{c,bmb}
│       ├── json_serialize/{c,bmb}/main.{c,bmb}
│       └── lexer/{c,bmb}/main.{c,bmb}
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
2. **Fair optimization**: C uses `-O3 -march=native`, BMB uses LLVM `-O2`
3. **Median timing**: 3 runs, median reported
4. **Output validation**: Verify identical output

## Key Features

### Tail Call Optimization (TCO)

BMB automatically optimizes tail-recursive functions into loops, providing significant speedups:

- **ackermann**: 255x faster (deep recursion → loop)
- **nqueen**: 6.9x faster (backtracking → TCO)
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
