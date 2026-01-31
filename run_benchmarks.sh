#!/bin/bash
# BMB Benchmark Runner
# Builds and runs all benchmarks, collecting timing data

BMB="D:/data/lang-bmb/target/x86_64-pc-windows-gnu/release/bmb.exe"
RESULTS_DIR="benchmark_results"
mkdir -p "$RESULTS_DIR"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "=============================================="
echo "BMB Benchmark Suite v0.60.58"
echo "=============================================="
echo ""

# Function to time a command (returns milliseconds)
time_cmd() {
    local start=$(date +%s%N)
    "$@" > /dev/null 2>&1
    local end=$(date +%s%N)
    echo $(( (end - start) / 1000000 ))
}

# Function to run benchmark multiple times and get median
run_benchmark() {
    local exe=$1
    local runs=5
    local times=()

    for ((i=1; i<=runs; i++)); do
        local t=$(time_cmd "$exe")
        times+=($t)
    done

    # Sort and get median
    IFS=$'\n' sorted=($(sort -n <<<"${times[*]}")); unset IFS
    local median=${sorted[$((runs/2))]}
    echo $median
}

# Build and benchmark function
benchmark() {
    local name=$1
    local category=$2
    local bmb_src="benches/$category/$name/bmb/main.bmb"
    local c_src="benches/$category/$name/c/main.c"
    local bmb_exe="$RESULTS_DIR/${name}_bmb.exe"
    local c_exe="$RESULTS_DIR/${name}_c.exe"

    printf "%-20s " "$name"

    # Build BMB
    if [ -f "$bmb_src" ]; then
        if $BMB build "$bmb_src" -o "$bmb_exe" > /dev/null 2>&1; then
            bmb_time=$(run_benchmark "$bmb_exe")
            printf "BMB: %6dms  " "$bmb_time"
        else
            printf "BMB: ${RED}BUILD FAIL${NC}  "
            bmb_time="FAIL"
        fi
    else
        printf "BMB: ${YELLOW}NO SRC${NC}     "
        bmb_time="N/A"
    fi

    # Build C
    if [ -f "$c_src" ]; then
        if gcc -O3 -march=native -o "$c_exe" "$c_src" -lm 2>/dev/null; then
            c_time=$(run_benchmark "$c_exe")
            printf "C: %6dms  " "$c_time"
        else
            printf "C: ${RED}BUILD FAIL${NC}  "
            c_time="FAIL"
        fi
    else
        printf "C: ${YELLOW}NO SRC${NC}     "
        c_time="N/A"
    fi

    # Calculate ratio
    if [[ "$bmb_time" =~ ^[0-9]+$ ]] && [[ "$c_time" =~ ^[0-9]+$ ]] && [ "$c_time" -gt 0 ]; then
        ratio=$(echo "scale=2; $bmb_time / $c_time" | bc)
        if (( $(echo "$ratio <= 1.1" | bc -l) )); then
            printf "${GREEN}Ratio: ${ratio}x${NC}"
        elif (( $(echo "$ratio <= 1.5" | bc -l) )); then
            printf "${YELLOW}Ratio: ${ratio}x${NC}"
        else
            printf "${RED}Ratio: ${ratio}x${NC}"
        fi
    fi

    echo ""
}

echo "=== COMPUTE BENCHMARKS ==="
echo ""

for dir in benches/compute/*/; do
    name=$(basename "$dir")
    benchmark "$name" "compute"
done

echo ""
echo "=== REAL-WORLD BENCHMARKS ==="
echo ""

for dir in benches/real_world/*/; do
    name=$(basename "$dir")
    benchmark "$name" "real_world"
done

echo ""
echo "Done! Results in $RESULTS_DIR/"
