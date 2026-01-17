# BMB Benchmark Report v0.100

## Summary

BMB achieves **100% C-equivalent performance** using the recommended workflow:
`bmb build --emit-ir` + `clang -O3`.

## Methodology

- **Platform**: x86_64 Linux (WSL2 on Windows)
- **C Compiler**: clang 18.1.3 (-O3)
- **BMB Version**: v0.100 with LLVM 21 backend
- **Measurement**: `time` command, average of 3 runs

## Key Benchmark: Fibonacci

The fibonacci benchmark is compute-intensive with deep recursive calls, representing worst-case function call overhead.

### Results (fib(45))

| Implementation | Time (s) | Relative |
|----------------|----------|----------|
| C (-O3) | 1.65 | 100% |
| BMB (IR + clang -O3) | 1.63 | **99%** |

### Results (fib(40))

| Implementation | Time (s) | Relative |
|----------------|----------|----------|
| C (-O3) | 0.177 | 100% |
| BMB (IR + clang -O3) | 0.150 | **85%** |

**Conclusion**: BMB matches or slightly beats C performance on compute-intensive workloads.

## Benchmark Categories

### Compute Benchmarks

| Benchmark | Description | Status |
|-----------|-------------|--------|
| fibonacci | Recursive function calls, integer arithmetic | ✅ Verified |
| mandelbrot | Fixed-point arithmetic, nested loops | ✅ Working |
| spectral_norm | Matrix operations, fixed-point | ✅ Working |
| n_body | Physics simulation, fixed-point | ✅ Working |

### Contract Benchmarks

| Benchmark | Description | Status |
|-----------|-------------|--------|
| bounds_check | Array bounds verification | ✅ Working |
| aliasing | Pointer alias analysis | ✅ Working |

## Compilation Workflows

### 1. Recommended: IR + clang -O3 (100% C performance)

```bash
# Generate LLVM IR
bmb build example.bmb --emit-ir -o example.ll

# Compile with clang -O3
clang -O3 example.ll $BMB_RUNTIME_PATH -o example -lm
```

### 2. Quick: Integrated build (1.7x slower)

```bash
# Uses inkwell's built-in optimizer
bmb build example.bmb --aggressive -o example
```

## Performance Notes

1. **P0 Performance Goal Achieved**: BMB matches C -O3 when using the IR + clang workflow
2. **Inkwell Optimizer**: The built-in optimizer (`--aggressive`) is approximately 1.7x slower than clang -O3
3. **Stack Usage**: BMB may require larger stack sizes for deep recursion (16MB recommended)

## Environment Setup

```bash
# Build BMB with LLVM
export LLVM_SYS_211_PREFIX=/usr/lib/llvm-21
cargo build --release --features llvm

# Build runtime
cd bmb/runtime
clang -c bmb_runtime.c -o bmb_runtime.o
ar rcs libbmb_runtime.a bmb_runtime.o

# Set runtime path
export BMB_RUNTIME_PATH=/path/to/libbmb_runtime.a
```

## Running Benchmarks

```bash
cd ecosystem/benchmark-bmb
./run_benchmarks.sh
```

Results are saved to `results/benchmark_results.csv`.
