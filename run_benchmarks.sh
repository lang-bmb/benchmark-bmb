#!/bin/bash
# BMB Benchmark Suite v0.100
# Compares BMB native compilation (via LLVM) against C (-O3)

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
BMB="$PROJECT_ROOT/target/release/bmb"
RUNTIME="$PROJECT_ROOT/bmb/runtime/libbmb_runtime.a"

# Output directories
RESULTS_DIR="$SCRIPT_DIR/results"
BUILD_DIR="$SCRIPT_DIR/build"
mkdir -p "$RESULTS_DIR" "$BUILD_DIR"

# Benchmark categories
COMPUTE_BENCHMARKS=(
    "fibonacci"
    "mandelbrot"
    "spectral_norm"
    "n_body"
)

# Check prerequisites
check_prereqs() {
    if [[ ! -f "$BMB" ]]; then
        echo "Error: BMB compiler not found at $BMB"
        echo "Build with: cargo build --release --features llvm"
        exit 1
    fi

    if [[ ! -f "$RUNTIME" ]]; then
        echo "Error: BMB runtime not found at $RUNTIME"
        echo "Build with: cd bmb/runtime && clang -c bmb_runtime.c -o bmb_runtime.o && ar rcs libbmb_runtime.a bmb_runtime.o"
        exit 1
    fi

    if ! command -v clang &> /dev/null; then
        echo "Error: clang not found"
        exit 1
    fi
}

# Run a single benchmark and measure time
run_benchmark() {
    local name="$1"
    local exe="$2"
    local iterations="${3:-3}"

    local total_time=0
    for ((i=1; i<=iterations; i++)); do
        local start=$(date +%s.%N)
        "$exe" > /dev/null 2>&1 || true
        local end=$(date +%s.%N)
        local elapsed=$(echo "$end - $start" | bc)
        total_time=$(echo "$total_time + $elapsed" | bc)
    done

    # Average time
    echo "scale=3; $total_time / $iterations" | bc
}

# Compile and benchmark a single test
benchmark_one() {
    local category="$1"
    local name="$2"
    local bench_dir="$SCRIPT_DIR/benches/$category/$name"

    if [[ ! -d "$bench_dir" ]]; then
        echo "SKIP: $name (not found)"
        return
    fi

    local bmb_src="$bench_dir/bmb/main.bmb"
    local c_src="$bench_dir/c/main.c"

    if [[ ! -f "$bmb_src" ]] || [[ ! -f "$c_src" ]]; then
        echo "SKIP: $name (missing source)"
        return
    fi

    echo "Benchmarking: $name"

    # Compile C version
    local c_exe="$BUILD_DIR/${name}_c"
    clang -O3 "$c_src" -o "$c_exe" -lm 2>/dev/null || {
        echo "  C compile failed"
        return
    }

    # Compile BMB version (emit IR + clang -O3 for best performance)
    local bmb_ir="$BUILD_DIR/${name}_bmb.ll"
    local bmb_exe="$BUILD_DIR/${name}_bmb"

    export BMB_RUNTIME_PATH="$RUNTIME"
    "$BMB" build "$bmb_src" --emit-ir -o "$bmb_ir" 2>/dev/null || {
        echo "  BMB compile failed"
        return
    }
    clang -O3 "$bmb_ir" "$RUNTIME" -o "$bmb_exe" -lm -no-pie 2>/dev/null || {
        echo "  BMB link failed"
        return
    }

    # Run benchmarks
    local c_time=$(run_benchmark "$name" "$c_exe" 3)
    local bmb_time=$(run_benchmark "$name" "$bmb_exe" 3)

    # Calculate ratio
    local ratio=$(echo "scale=2; $bmb_time / $c_time * 100" | bc)

    echo "  C (-O3):   ${c_time}s"
    echo "  BMB:       ${bmb_time}s (${ratio}% of C)"

    # Save to results
    echo "$name,$c_time,$bmb_time,$ratio" >> "$RESULTS_DIR/benchmark_results.csv"
}

# Main benchmark run
main() {
    check_prereqs

    echo "============================================"
    echo "BMB Benchmark Suite v0.100"
    echo "============================================"
    echo ""
    echo "BMB Compiler: $BMB"
    echo "Runtime:      $RUNTIME"
    echo "Output:       $RESULTS_DIR"
    echo ""

    # Initialize results file
    echo "benchmark,c_time_s,bmb_time_s,ratio_percent" > "$RESULTS_DIR/benchmark_results.csv"

    echo "Running compute benchmarks..."
    echo "--------------------------------------------"
    for bench in "${COMPUTE_BENCHMARKS[@]}"; do
        benchmark_one "compute" "$bench"
    done

    echo ""
    echo "============================================"
    echo "Results saved to: $RESULTS_DIR/benchmark_results.csv"
    echo "============================================"
}

main "$@"
