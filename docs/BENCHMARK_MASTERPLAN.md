# BMB Benchmark Masterplan

> 전략적 벤치마크 계획: BMB 목표 달성 검증, 결함 발굴, 공신력 확보

## 목적

### 1. 자체 검증 (Self-Validation)
BMB의 핵심 목표인 **"C와 동등하거나 더 빠른 성능"**을 다양한 시나리오에서 증명합니다.

```
목표: BMB >= C -O3 (모든 케이스)
목표: BMB > C -O3 (계약 활용 케이스)
```

### 2. 결함 발굴 (Defect Discovery)
벤치마크 실패 케이스에서 언어/컴파일러의 최적화 누락 또는 버그를 발견합니다.

- 예상보다 느린 케이스 → 코드젠 최적화 기회
- LLVM IR 패턴 분석 → 누락된 최적화 패스 발견
- 메모리 사용량 이상 → 할당 전략 개선 기회

### 3. 공신력 확보 (Credibility)
업계 표준 벤치마크를 채택하여 객관적 비교를 가능하게 합니다.

**참조 벤치마크 스위트:**
- [The Computer Language Benchmarks Game](https://benchmarksgame-team.pages.debian.net/benchmarksgame/) - 언어 간 비교 표준
- [PolyBench](https://github.com/cavazos-lab/PolyBench-ACC) - 루프 최적화 평가
- [CoreMark](https://github.com/eembc/coremark) - 임베디드 시스템 표준
- [Embench](https://github.com/embench/embench-iot) - IoT 워크로드

## 벤치마크 아키텍처

```
benchmark-bmb/
├── benches/
│   ├── compute/          # Benchmarks Game 표준 (10개)
│   │   ├── fibonacci/
│   │   ├── n_body/
│   │   ├── mandelbrot/
│   │   ├── spectral_norm/
│   │   ├── binary_trees/
│   │   ├── fannkuch/
│   │   ├── fasta/
│   │   ├── k-nucleotide/
│   │   ├── reverse-complement/
│   │   └── hash_table/
│   │
│   ├── zero_overhead/    # Zero-Cost Safety 증명 (5개)
│   │   ├── bounds_check_proof/   # Gate #3.2
│   │   ├── overflow_proof/       # Gate #3.3
│   │   ├── null_check_proof/
│   │   ├── aliasing_proof/
│   │   └── purity_proof/
│   │
│   ├── contract_opt/     # 계약 기반 최적화 (4개)
│   │   ├── bounds_elim/
│   │   ├── null_elim/
│   │   ├── branch_elim/
│   │   └── loop_invariant/
│   │
│   ├── surpass/          # C보다 빠른 케이스 (5개)
│   │   ├── matrix_multiply/
│   │   ├── sort_presorted/
│   │   ├── string_search/
│   │   ├── graph_traversal/
│   │   └── tree_balance/
│   │
│   ├── memory/           # 메모리 패턴 (5개)
│   │   ├── cache_stride/
│   │   ├── memory_copy/
│   │   ├── stack_allocation/
│   │   ├── pointer_chase/
│   │   └── simd_sum/
│   │
│   ├── syscall/          # 시스템 호출 (3개)
│   │   ├── syscall_overhead/
│   │   ├── file_io_seq/
│   │   └── process_spawn/
│   │
│   ├── real_world/       # 실제 워크로드 (6개)
│   │   ├── json_parse/
│   │   ├── json_serialize/
│   │   ├── csv_parse/
│   │   ├── http_parse/
│   │   ├── lexer/
│   │   └── brainfuck/
│   │
│   └── bootstrap/        # 컴파일러 자체 (3개)
│       ├── lex_bootstrap/
│       ├── parse_bootstrap/
│       └── typecheck_bootstrap/
│
├── docs/
│   ├── BENCHMARK_MASTERPLAN.md   # 이 문서
│   ├── BENCHMARK_COMPARISON.md   # 상세 비교 결과
│   └── BENCHMARK_ROADMAP.md      # 벤치마크 로드맵
│
├── results/              # 측정 결과 보관
└── runner/               # Rust 기반 벤치마크 러너
```

## 성능 목표 (Performance Gates)

| Gate | Phase | 기준 | 목표 | 상태 |
|------|-------|------|------|------|
| **#1** | v0.31 | Interpreter 기준선 | Rust interpreter 동등 | ✅ 통과 |
| **#2** | v0.34 | Native 컴파일 | C -O3와 fibonacci 동등 | ✅ 통과 |
| **#3.1** | v0.54 | Compute 벤치마크 | Clang 대비 ≤1.10x | ✅ 1.00-1.08x |
| **#3.2** | v0.54 | Bounds check | 0% (컴파일 타임 제거) | ✅ 완료 |
| **#3.3** | v0.54 | Overflow check | 0% (컴파일 타임 제거) | ✅ 완료 |
| **#3.4** | v0.54.5 | C 대비 전체 | ≤1.05x (모든 compute) | 📋 검증 필요 |
| **#3.5** | v0.54.5 | Rust 대비 | ≤1.00x | 📋 검증 필요 |
| **#4** | v0.54.5 | Surpass 케이스 | 3+ 벤치마크 C보다 빠름 | 📋 검증 필요 |
| **#5** | v1.0 | CI 자동화 | 회귀 방지 (2% 임계값) | 📋 계획 |

## 측정 방법론

### 재현성 요구사항

[How2Bench](https://arxiv.org/html/2501.10711v1) 기준 준수:

| 요구사항 | 상태 | 구현 |
|----------|------|------|
| 소스 공개 | ✅ | MIT 라이선스, GitHub 공개 |
| 환경 명시 | ✅ | OS, CPU, 컴파일러 버전 기록 |
| CI 일관성 | ✅ | GitHub Actions 동일 환경 |
| 통계적 측정 | ✅ | 중앙값, 5회 반복, warm-up 2회 |
| 재현 가능 | ✅ | 단일 스크립트 실행 |

### 측정 환경

```yaml
# 표준 측정 환경
platform: x86_64-linux (GitHub Actions ubuntu-latest)
c_compiler: clang 18.x (-O3 -march=native)
rust_compiler: rustc stable (--release, LTO)
bmb_compiler: bmb v0.54+ (--emit-ir + clang -O3)

# 측정 파라미터
warmup_iterations: 2
measurement_iterations: 5
metric: median_time_ms
timeout: 300s
```

### 유효성 검증

각 벤치마크는 출력 검증을 포함:

```bash
# C와 BMB 출력이 동일해야 함
diff <(./c_benchmark) <(./bmb_benchmark)
```

## Zero-Cost Safety 검증

### LLVM IR 패턴 분석

| 최적화 | 확인 패턴 | 기대 IR | 실패 IR |
|--------|----------|---------|---------|
| Bounds check 제거 | `getelementptr` + `load` | 직접 GEP | `call @bmb_array_bounds_check` |
| Overflow check 제거 | `add nsw` / `mul nsw` | nsw 플래그 | `call @llvm.sadd.with.overflow` |
| Null check 제거 | 직접 역참조 | `load ptr` | `icmp eq ptr, null` |
| Aliasing 증명 | `noalias` 속성 | `noalias ptr` | 속성 없음 |
| Purity CSE | 중복 호출 제거 | 단일 호출 | 다중 호출 |

### 검증 스크립트

```bash
# Zero-Cost Safety 자동 검증
./target/release/benchmark-bmb verify-ir bounds_check_proof
# 출력: ✅ No bounds check in LLVM IR

./target/release/benchmark-bmb verify-ir overflow_proof
# 출력: ✅ Using 'add nsw', no overflow check
```

## Surpass 케이스: C보다 빠른 이유

BMB의 계약 시스템이 C에서 불가능한 최적화를 가능하게 합니다.

### matrix_multiply

```bmb
fn matrix_multiply(a: [[i64; N]; M], b: [[i64; P]; N], c: &mut [[i64; P]; M])
  pre N > 0 and M > 0 and P > 0
  pre N <= 64 and M <= 64 and P <= 64  // 컴파일 타임 상수
{
  // N, M, P가 정적으로 확정되어 루프 언롤링 가능
}
```

**C 대비 이점**: C에서는 런타임 크기 체크 필요, BMB에서는 pre-condition으로 컴파일 타임 확정

### sort_presorted

```bmb
fn optimized_sort(arr: &mut [i64])
  pre is_nearly_sorted(arr, 0.9)  // 90% 이상 정렬됨
{
  // 컴파일러가 insertion sort 선택 가능
}
```

**C 대비 이점**: C에서는 항상 worst-case 가정, BMB에서는 힌트로 최적화

## CI 통합

### 회귀 방지

```yaml
# .github/workflows/benchmark.yml
name: Benchmark Gate
on: [push, pull_request]
jobs:
  benchmark:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Run benchmarks
        run: |
          cd ecosystem/benchmark-bmb
          ./target/release/benchmark-bmb ci --threshold 2%
      - name: Upload results
        uses: actions/upload-artifact@v4
        with:
          name: benchmark-results
          path: results/
```

### 알림 설정

- **2% 초과 성능 저하**: PR 차단, 이슈 자동 생성
- **5% 이상 개선**: 릴리스 노트에 포함
- **Gate 실패**: 머지 차단

## 결함 발굴 프로세스

### 1. 벤치마크 실패 분석

```bash
# 예상보다 느린 케이스 식별
./target/release/benchmark-bmb run --category compute --verbose
# 출력: mandelbrot: 1.15x vs C (목표: ≤1.05x) ❌
```

### 2. LLVM IR 분석

```bash
# IR 비교
bmb build mandelbrot.bmb --emit-ir -o mandelbrot.ll
# 최적화 누락 패턴 검색
grep -E "call @bmb_|icmp.*null" mandelbrot.ll
```

### 3. GitHub 이슈 생성

```markdown
## Performance: mandelbrot 1.15x vs C

### 증상
mandelbrot 벤치마크가 C 대비 15% 느림 (목표: 5% 이내)

### LLVM IR 분석
- 불필요한 bounds check 발견 (line 42)
- 루프 언롤링 미적용 (line 56-78)

### 재현
```bash
cd ecosystem/benchmark-bmb
./run_benchmarks.sh mandelbrot
```

### 제안
- [ ] bounds check 제거 조건 개선
- [ ] 루프 최적화 힌트 추가
```

## 문서 및 산출물

| 문서 | 목적 | 업데이트 주기 |
|------|------|--------------|
| BENCHMARK_REPORT.md | 최신 결과 요약 | 매 릴리스 |
| BENCHMARK_COMPARISON.md | 상세 언어별 비교 | 분기별 |
| BENCHMARK_ROADMAP.md | 벤치마크 개발 계획 | 필요시 |
| results/*.md | 개별 측정 결과 | 매 CI 실행 |

## 참고 자료

### 벤치마크 표준
- [Benchmarks Game Methodology](https://benchmarksgame-team.pages.debian.net/benchmarksgame/sometimes-people-just-make-up-stuff.html)
- [How2Bench: Benchmark Quality Guidelines](https://arxiv.org/html/2501.10711v1)
- [Programming Language Benchmarks](https://programming-language-benchmarks.vercel.app/)

### Zero-Cost Abstraction
- [Rust Zero-Cost Abstractions](https://doc.rust-lang.org/beta/embedded-book/static-guarantees/zero-cost-abstractions.html)
- [Benchmarking Zero-Cost Abstraction in Rust](https://rustsnippet.substack.com/p/benchmarking-zero-cost-abstraction)

### 컴파일러 최적화
- [LLVM Polly Loop Optimization](https://arxiv.org/abs/2010.08040)
- [CoreMark Compiler Optimization](https://codasip.com/papers/better-benchmarks-through-compiler-optimizations-codasip-jump-threading/)
