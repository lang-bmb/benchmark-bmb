# benchmark-bmb

> Standard Benchmarking Suite for BMB Language

BMB 언어의 표준 벤치마크 스위트. C, Rust, BMB 간 성능 비교를 제공합니다.

## Goal

**BMB >= C -O3** (모든 케이스)
**BMB > C -O3** (계약 활용 케이스)

## Current Status: v0.3

### Latest Results (2026-01-10, Phase 35)

#### C vs Rust Baseline (native compilation)

| Benchmark | C (ms) | Rust (ms) | Ratio | Notes |
|-----------|--------|-----------|-------|-------|
| fibonacci(35) | 14.85 | 18.71 | 1.26x | C faster |
| mandelbrot | 3.54 | 4.38 | 1.24x | C faster |
| spectral_norm | 3.73 | 4.20 | 1.13x | C faster |
| binary_trees | 359.19 | 85.82 | 0.24x | Rust faster |
| fannkuch | 63.31 | 139.62 | 2.21x | C faster |
| n_body | 20.49 | 3.69 | 0.18x | Rust faster |
| sorting | 14.69 | 42.99 | 2.93x | C faster |

#### BMB Native Compilation

BMB native compilation requires LLVM/clang. When available:
- Compile: `bmb build -o output source.bmb`
- Performance target: **BMB >= C -O3**

**Benchmark Gate #1 PASSED**: Interpreter baseline established
**Benchmark Gate #2 PASSED**: Native compilation infrastructure ready

See `docs/BENCHMARK_ROADMAP.md` for detailed gate definitions.

### Implemented Benchmarks (12 total, 3 languages)

#### Compute-Intensive (Benchmarks Game Standard)

| Benchmark | C | Rust | BMB | Description |
|-----------|---|------|-----|-------------|
| fibonacci | ✅ | ✅ | ✅ | Recursive function calls, integer ops |
| n_body | ✅ | ✅ | ✅ | N-body simulation (fixed-point) |
| mandelbrot | ✅ | ✅ | ✅ | Fractal generation, fixed-point math |
| spectral_norm | ✅ | ✅ | ✅ | Matrix operations, linear algebra |
| binary_trees | ✅ | ✅ | ✅ | Memory allocation, recursion |
| fannkuch | ✅ | ✅ | ✅ | Permutation generation, array ops |

#### Contract-Optimized (BMB-Specific)

| Benchmark | C | Rust | BMB | Contract Benefit |
|-----------|---|------|-----|------------------|
| bounds_check | ✅ | ✅ | ✅ | pre로 경계검사 제거 (10-30% 향상) |
| null_check | ✅ | ✅ | ✅ | Option<T> + contracts로 null 검사 제거 |
| purity_opt | ✅ | ✅ | ✅ | 순수성 기반 CSE, 메모이제이션 |
| aliasing | ✅ | ✅ | ✅ | 소유권으로 aliasing 증명 → SIMD 활성화 |

#### Real-World Workloads

| Benchmark | C | Rust | BMB | Description |
|-----------|---|------|-----|-------------|
| json_parse | ✅ | ✅ | ✅ | JSON 파싱, 문자열 처리 |
| sorting | ✅ | ✅ | ✅ | 정렬 알고리즘 비교 |

## Benchmark Categories

### Compute-Intensive
Standard benchmarks from [The Computer Language Benchmarks Game](https://benchmarksgame-team.pages.debian.net/benchmarksgame/).

| Benchmark | Description | Measures |
|-----------|-------------|----------|
| `fibonacci` | Recursive Fibonacci(35) | Integer ops, function calls |
| `n_body` | N-body simulation | FP arithmetic (fixed-point) |
| `mandelbrot` | Mandelbrot set 50x50 | Iteration, fixed-point complex |
| `spectral_norm` | Eigenvalue approximation | Matrix-vector multiply |
| `binary_trees` | Binary tree allocate/deallocate | Memory patterns, recursion |
| `fannkuch` | Pancake flipping | Permutation, array reversal |

### Contract-Optimized
BMB-specific benchmarks demonstrating contract-based optimizations.

| Benchmark | Description | Expected BMB Advantage |
|-----------|-------------|------------------------|
| `bounds_check` | Array access with pre conditions | 10-30% (bounds check elimination) |
| `null_check` | Option<T> handling with contracts | 15-25% (null check elimination) |
| `purity_opt` | Pure function redundancy | 20-50% (CSE, hoisting) |
| `aliasing` | Non-aliasing array operations | 30-50% (SIMD vectorization) |

### Real-World
Practical workloads representative of actual applications.

| Benchmark | Description | Measures |
|-----------|-------------|----------|
| `json_parse` | JSON validation and counting | String processing, parsing |
| `sorting` | Multiple sorting algorithms | Comparisons, data movement |

## Directory Structure

```
benchmark-bmb/
├── README.md
├── benches/
│   ├── compute/
│   │   ├── fibonacci/{c,bmb}/main.{c,bmb}
│   │   ├── n_body/{c,bmb}/main.{c,bmb}
│   │   ├── mandelbrot/{c,bmb}/main.{c,bmb}
│   │   ├── spectral_norm/{c,bmb}/main.{c,bmb}
│   │   ├── binary_trees/{c,bmb}/main.{c,bmb}
│   │   └── fannkuch/{c,bmb}/main.{c,bmb}
│   ├── contract/
│   │   ├── bounds_check/{c,bmb}/main.{c,bmb}
│   │   ├── null_check/{c,bmb}/main.{c,bmb}
│   │   ├── purity_opt/{c,bmb}/main.{c,bmb}
│   │   └── aliasing/{c,bmb}/main.{c,bmb}
│   └── real_world/
│       ├── json_parse/{c,bmb}/main.{c,bmb}
│       └── sorting/{c,bmb}/main.{c,bmb}
├── runner/
│   ├── Cargo.toml
│   └── src/main.rs
└── results/
```

## Running Benchmarks

```bash
# Build runner
cd runner
cargo build --release

# Run all benchmarks
./target/release/benchmark-bmb run

# Run specific category
./target/release/benchmark-bmb run --category compute
./target/release/benchmark-bmb run --category contract
./target/release/benchmark-bmb run --category realworld

# Run single benchmark
./target/release/benchmark-bmb run fibonacci

# Verify benchmark gates
./target/release/benchmark-bmb gate 3.1      # Gate #3.1 verification
./target/release/benchmark-bmb gate 3.2 -v   # Gate #3.2 with verbose output

# Compare languages
./target/release/benchmark-bmb compare mandelbrot
```

### Requirements

- **C benchmarks**: GCC with `-O3` optimization
- **Rust benchmarks**: rustc with `--release` (LTO enabled)
- **BMB benchmarks**:
  - Native: LLVM/clang for linking
  - Interpreter: `bmb` in PATH (slower, for validation)

## Output Format

```
=== BMB Benchmark Suite v0.2 ===

Category: compute
─────────────────────────────────────────────────────────────
Benchmark         C (ms)    BMB (ms)    Ratio    Status
─────────────────────────────────────────────────────────────
fibonacci         850.23     855.67     1.01x      ✓
mandelbrot        123.45     120.12     0.97x      ✓★
binary_trees      456.78     450.23     0.99x      ✓
─────────────────────────────────────────────────────────────

Category: contract
─────────────────────────────────────────────────────────────
Benchmark         C (ms)    BMB (ms)    Ratio    Status
─────────────────────────────────────────────────────────────
bounds_check      100.00      75.00     0.75x      ✓★
null_check        200.00     160.00     0.80x      ✓★
purity_opt        300.00     180.00     0.60x      ✓★
aliasing          400.00     240.00     0.60x      ✓★
─────────────────────────────────────────────────────────────

Legend:
  ✓  = BMB within 5% of C
  ✓★ = BMB faster than C
  ✗  = BMB more than 5% slower
```

## Benchmark Requirements

### Implementation Guidelines

1. **Identical Algorithm**: Same algorithm across all languages
2. **No External Libraries**: Standard library only
3. **Fair Optimization**: Language-appropriate optimizations allowed
4. **Contracts in BMB**: Use pre/post where applicable

### Measurement

- **Warm-up**: 2 iterations before measurement
- **Iterations**: 5 measurements, median reported
- **Environment**: Single-threaded, isolated CPU cores
- **Compiler flags**: C with `-O3`, BMB with `--release`

## Methodology

Following [Benchmarks Game methodology](https://benchmarksgame-team.pages.debian.net/benchmarksgame/):

1. Same algorithm, different implementations
2. Wall-clock time measurement
3. Median of multiple runs
4. Validation of output correctness

## Benchmark Gates

Performance requirements at each major BMB release phase.

| Gate | Phase | Criteria | Status |
|------|-------|----------|--------|
| **Gate #1** | v0.31 | Interpreter >= Rust interpreter | ✅ Passed |
| **Gate #2** | v0.34 | Native == C -O3 (fibonacci) | ✅ Passed |
| **Gate #3.1** | v0.35 | Compute within 10% of C | 📋 In Progress |
| **Gate #3.2** | v0.36 | All Benchmarks Game within 5% of C | 📋 Planned |
| **Gate #3.3** | v0.37 | 3+ benchmarks faster than C | 📋 Planned |
| **Gate #4** | v1.0 | All gates + CI enforcement | 📋 Planned |

See [BENCHMARK_ROADMAP.md](../../docs/BENCHMARK_ROADMAP.md) for detailed roadmap.

## Roadmap

| Version | Features | Status |
|---------|----------|--------|
| v0.1 | Basic runner, 3 benchmarks | ✅ |
| v0.2 | 12 benchmarks, 3 categories | ✅ |
| v0.3 | Gate integration, Rust comparison | 🔄 In Progress |
| v0.4 | Full Benchmarks Game suite (11 benchmarks) | 📋 Planned |
| v0.5 | CI regression detection, 2% threshold | 📋 Planned |
| v0.6 | Web dashboard (bench.bmb.dev) | 📋 Planned |

## Contributing

1. Fork the repository
2. Add benchmark implementation in both C and BMB
3. Validate correctness (same output)
4. Submit PR with benchmark results

## License

MIT License
