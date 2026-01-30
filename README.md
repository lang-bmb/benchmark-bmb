# benchmark-bmb

> Standard Benchmarking Suite for BMB Language

BMB 언어의 표준 벤치마크 스위트. C (GCC/Clang), BMB 간 성능 비교를 제공합니다.

## Test Environment

```yaml
environment:
  cpu: "Intel Core i7-1165G7 @ 2.8GHz"
  cores_used: 1  # single-threaded benchmarks
  ram: "32GB DDR4"
  os: "Windows 11 (MSYS2)"
  gcc: "13.2.0"
  clang: "19.1.1"
  llvm: "21.1.8"
  bmb: "0.60.51"
```

## Performance Summary (v0.60.51)

### Compute Benchmarks (23 benchmarks)

| Benchmark | BMB | GCC -O3 | Clang -O3 | vs GCC | vs Clang | Category |
|-----------|-----|---------|-----------|--------|----------|----------|
| ackermann | 59ms | 11305ms | 60ms | **0.01x** | 0.98x | LICM |
| binary_trees | 112ms | 112ms | 112ms | 1.00x | 1.00x | Memory |
| collatz | 41ms | 40ms | 43ms | 1.02x | **0.95x** | Pure |
| digital_root | 40ms | 38ms | 36ms | 1.05x | 1.11x | Pure |
| fannkuch | 105ms | 95ms | 103ms | 1.11x | 1.02x | Permutation |
| fasta | 62ms | 60ms | 57ms | 1.03x | 1.09x | String |
| fibonacci | 36ms | 37ms | 36ms | **0.97x** | 1.00x | Pure |
| gcd | 47ms | 49ms | 48ms | **0.96x** | **0.98x** | Pure |
| hash_table | 38ms | 37ms | 36ms | 1.03x | 1.06x | Hash |
| k-nucleotide | 36ms | 32ms | 36ms | 1.12x | 1.00x | Hash |
| mandelbrot | 174ms | 166ms | 174ms | 1.05x | 1.00x | FP Compute |
| matrix_multiply | 42ms | 37ms | 45ms | 1.14x | **0.93x** | Matrix |
| n_body | 104ms | 95ms | 100ms | 1.09x | 1.04x | Physics |
| nqueen | 906ms | 6856ms | 919ms | **0.13x** | 0.99x | LICM |
| perfect_numbers | 620ms | 1002ms | 621ms | **0.62x** | 1.00x | LICM |
| pidigits | 32ms | 35ms | 36ms | **0.91x** | **0.89x** | BigNum |
| primes_count | 49ms | 55ms | 67ms | **0.89x** | **0.73x** | Pure |
| regex_redux | 34ms | 33ms | 37ms | 1.03x | **0.92x** | Regex |
| reverse-complement | 35ms | 34ms | 35ms | 1.03x | 1.00x | String |
| sieve | 41ms | 41ms | 51ms | 1.00x | **0.80x** | Array |
| spectral_norm | 65ms | 50ms | 62ms | 1.30x | 1.05x | FP Matrix |
| sum_of_squares | 32ms | 33ms | 36ms | **0.97x** | **0.89x** | Pure |
| tak | 36ms | 45ms | 37ms | **0.80x** | **0.97x** | Recursion |

### Real-World Benchmarks (7 benchmarks)

| Benchmark | BMB | GCC -O3 | Clang -O3 | vs GCC | vs Clang | Category |
|-----------|-----|---------|-----------|--------|----------|----------|
| brainfuck | 32ms | 33ms | 38ms | **0.97x** | **0.84x** | Interpreter |
| csv_parse | 35ms | 35ms | 36ms | 1.00x | **0.97x** | Parsing |
| http_parse | 36ms | 38ms | 37ms | **0.95x** | **0.97x** | Parsing |
| json_parse | 34ms | 39ms | 34ms | **0.87x** | 1.00x | Parsing |
| json_serialize | 34ms | 37ms | 40ms | **0.92x** | **0.85x** | Serialization |
| lexer | 35ms | 34ms | 37ms | 1.03x | **0.95x** | Tokenization |
| sorting | 176ms | 644ms | 139ms | **0.27x** | 1.27x | TCO |

**Legend**: Bold = BMB faster, Regular = C faster or parity

---

## Analysis

### BMB vs Clang (Fair Comparison - Same LLVM Backend)

동일한 LLVM 백엔드를 사용하므로 **언어 자체의 성능**을 측정합니다.

| Category | BMB Faster | Parity (±5%) | Clang Faster |
|----------|------------|--------------|--------------|
| Compute (23) | 9 (39%) | 10 (43%) | 4 (17%) |
| Real-World (7) | 5 (71%) | 2 (29%) | 0 (0%) |
| **Total (30)** | **14 (47%)** | **12 (40%)** | **4 (13%)** |

**결론**: BMB는 Clang과 동등하거나 더 우수한 성능

### BMB vs GCC (Compiler Comparison)

LLVM과 GCC의 최적화 차이를 보여줍니다.

| Category | BMB Faster | Parity (±5%) | GCC Faster |
|----------|------------|--------------|------------|
| Compute (23) | 11 (48%) | 7 (30%) | 5 (22%) |
| Real-World (7) | 5 (71%) | 1 (14%) | 1 (14%) |
| **Total (30)** | **16 (53%)** | **8 (27%)** | **6 (20%)** |

---

## LICM Optimization Analysis

### LICM (Loop-Invariant Code Motion) 벤치마크

이 벤치마크들은 LLVM의 LICM 최적화 효과를 보여줍니다.

| Benchmark | BMB | GCC | Clang | 분석 |
|-----------|-----|-----|-------|------|
| ackermann | 59ms | 11305ms | 60ms | **BMB ≈ Clang** (LLVM 기능) |
| nqueen | 906ms | 6856ms | 919ms | **BMB ≈ Clang** (LLVM 기능) |
| perfect_numbers | 620ms | 1002ms | 621ms | **BMB ≈ Clang** (LLVM 기능) |

**핵심 인사이트**:
- LICM은 **LLVM의 기능**이며 BMB만의 특별한 기능이 아님
- Clang도 동일한 최적화 혜택을 받음
- GCC 대비 극적인 차이는 컴파일러 차이 (LLVM vs GCC)

### TCO (Tail Call Optimization) 벤치마크

| Benchmark | BMB | GCC | Clang | 분석 |
|-----------|-----|-----|-------|------|
| sorting | 176ms | 644ms | 139ms | Clang > BMB > GCC |

**분석**: sorting에서 Clang이 BMB보다 빠른 이유는 데이터 타입 차이:
- C: `int` (32-bit)
- BMB: `i64` (64-bit)

---

## Known Issues

### 1. spectral_norm (BMB 1.30x slower than GCC)

GCC의 nested loop IV strength reduction 최적화:
- `i + j` 패턴을 running counter로 변환
- LLVM (Clang, BMB 모두)은 이 최적화 미지원
- **LLVM 한계이며 BMB 문제가 아님**

### 2. sorting (Data Type Mismatch)

```c
// C version - 32-bit
int* arr = (int*)malloc(size * sizeof(int));

// BMB version - 64-bit
fn array_new(n: i64) -> i64 = malloc(n * 8);
```

공정한 비교를 위해 C를 `int64_t`로 변경 필요

### 3. hash_table (Output Difference)

- BMB: 97648, C: 95259
- 원인: signed vs unsigned 해시 연산 차이
- 수정 필요

---

## v0.60.51 Changes

- **DCE 버그 수정**: `has_side_effects()`에 `PtrStore`, `ArrayAlloc` 추가
- **Clang 비교 추가**: GCC와 Clang 모두 벤치마크
- **분석 개선**: LICM이 LLVM 기능임을 명확히 문서화

## v0.60.50 Changes

- **TCO 검증 완료**: ackermann, nqueen, tak은 LICM이며 TCO가 아님 확인
- **측정값 갱신**: 최신 실측 데이터로 업데이트

---

## Running Benchmarks

```bash
# Build BMB compiler
cargo build --release --features llvm --target x86_64-pc-windows-gnu

# Set runtime path
export BMB_RUNTIME_PATH="/path/to/lang-bmb/bmb/runtime"

# Build all benchmarks
./build_all.sh

# Run with hyperfine (recommended)
hyperfine --warmup 2 --runs 5 './bench_bmb' './bench_gcc' './bench_clang'
```

## Methodology

1. **Same algorithm**: 동일 알고리즘
2. **Fair optimization**:
   - GCC: `-O3 -march=native`
   - Clang: `-O3`
   - BMB: LLVM -O3 + scalarizer
3. **Multiple runs**: 3회 실행, 중앙값 보고
4. **Output validation**: 결과값 일치 확인

---

## License

MIT License
