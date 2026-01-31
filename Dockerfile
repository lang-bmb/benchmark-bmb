# BMB Benchmark Suite - Reproducible Environment
# Usage:
#   docker build -t bmb-benchmark .
#   docker run --rm -v $(pwd)/results:/benchmark/results bmb-benchmark

FROM ubuntu:22.04

LABEL maintainer="BMB Team"
LABEL description="Reproducible environment for BMB benchmark suite"

# Avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc-12 \
    g++-12 \
    clang-15 \
    curl \
    git \
    wget \
    pkg-config \
    libssl-dev \
    cmake \
    time \
    && rm -rf /var/lib/apt/lists/*

# Set default compilers
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-12 100 \
    && update-alternatives --install /usr/bin/clang clang /usr/bin/clang-15 100

# Install Rust
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

# Install hyperfine for benchmarking
RUN cargo install hyperfine

# Create benchmark directory
WORKDIR /benchmark

# Copy benchmark suite
COPY . /benchmark/

# Build the benchmark runner
RUN cd runner && cargo build --release

# Compile C benchmarks with GCC
RUN for dir in benches/*/*/c; do \
        if [ -f "$dir/main.c" ]; then \
            gcc -O3 -march=native -o "$dir/main_gcc" "$dir/main.c" -lm 2>/dev/null || true; \
        fi; \
    done

# Compile C benchmarks with Clang
RUN for dir in benches/*/*/c; do \
        if [ -f "$dir/main.c" ]; then \
            clang -O3 -o "$dir/main_clang" "$dir/main.c" -lm 2>/dev/null || true; \
        fi; \
    done

# Compile Rust benchmarks
RUN for dir in benches/*/*/rust; do \
        if [ -f "$dir/main.rs" ]; then \
            rustc -C opt-level=3 -C lto=fat -o "$dir/main_rust" "$dir/main.rs" 2>/dev/null || true; \
        fi; \
    done

# Create results directory
RUN mkdir -p /benchmark/results

# Default command: run all benchmarks
ENTRYPOINT ["/benchmark/scripts/docker_run.sh"]
CMD ["--all"]
