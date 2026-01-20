# BMB Benchmark Roadmap

> 벤치마크 스위트 개발 및 검증 로드맵

## 버전 히스토리

| 버전 | 날짜 | 주요 변경 |
|------|------|----------|
| v0.1 | 2026-01-08 | 기본 러너, 3개 벤치마크 |
| v0.2 | 2026-01-10 | 12개 벤치마크, 3개 카테고리 |
| v0.3 | 2026-01-17 | Gate 통합, Rust 비교, 50+ 벤치마크 |
| **v0.4** | 2026-01-20 | **Zero-Cost 검증, 문서화** |

## 현재 상태 (v0.4)

### Gate 체크리스트

| Gate | 설명 | 목표 | 상태 |
|------|------|------|------|
| **#1** | Interpreter 기준선 | Rust interpreter 동등 | ✅ v0.31 통과 |
| **#2** | Native 컴파일 | C -O3와 fibonacci 동등 | ✅ v0.34 통과 |
| **#3.1** | Compute 벤치마크 | Clang 대비 ≤1.10x | ✅ v0.54 (1.00-1.08x) |
| **#3.2** | Bounds check | 0% 오버헤드 | ✅ v0.54 검증됨 |
| **#3.3** | Overflow check | 0% 오버헤드 | ✅ v0.54 검증됨 |
| **#3.4** | C 대비 전체 | ≤1.05x (모든 compute) | 📋 v0.54.5 예정 |
| **#3.5** | Rust 대비 | ≤1.00x | 📋 v0.54.5 예정 |
| **#4** | Surpass 케이스 | 3+ C보다 빠름 | 📋 v0.54.5 예정 |
| **#5** | CI 자동화 | 회귀 방지 2% | 📋 v0.5 예정 |

### 벤치마크 현황 (50+)

| 카테고리 | 구현 | 검증 | 상태 |
|----------|------|------|------|
| compute | 10/10 | 6/10 | 🔄 진행 중 |
| zero_overhead | 5/5 | 2/5 | 🔄 진행 중 |
| contract_opt | 4/4 | 0/4 | 📋 대기 |
| surpass | 5/5 | 0/5 | 📋 대기 |
| memory | 5/5 | 0/5 | 📋 대기 |
| syscall | 3/3 | 0/3 | 📋 대기 |
| real_world | 6/6 | 0/6 | 📋 대기 |
| bootstrap | 3/3 | 0/3 | 📋 대기 |

---

## Phase 1: 기초 (v0.1-v0.2) ✅ 완료

### v0.1 - 기본 인프라
- [x] 벤치마크 러너 구현 (Rust)
- [x] fibonacci, mandelbrot, spectral_norm 구현
- [x] C/BMB 비교 기능
- [x] 결과 출력 포맷

### v0.2 - 확장
- [x] 12개 벤치마크로 확장
- [x] 3개 카테고리 (compute, contract, real_world)
- [x] Rust 비교 추가
- [x] 결과 저장 기능

---

## Phase 2: Gate 통합 (v0.3) ✅ 완료

### 구현 완료
- [x] Gate 검증 명령어 (`benchmark-bmb gate 3.2`)
- [x] 50+ 벤치마크 구현
- [x] 카테고리 확장 (8개)
- [x] 상세 결과 리포트

### 검증 완료
- [x] Gate #3.1: Clang 대비 1.00-1.08x
- [x] Gate #3.2: Bounds check 0% (LLVM IR 검증)
- [x] Gate #3.3: Overflow check 0% (LLVM IR 검증)

---

## Phase 3: 종합 검증 (v0.4) 🔄 현재

### 목표
BMB의 목표 달성 자체 검증, 결함/개선 기회 발굴, 공신력 확보

### 태스크

| ID | 태스크 | 우선순위 | 상태 |
|----|--------|----------|------|
| 4.1 | Benchmarks Game 전체 실행 (10개) | P0 | 📋 계획 |
| 4.2 | Zero-Cost 나머지 3개 검증 (null/aliasing/purity) | P0 | 📋 계획 |
| 4.3 | Surpass 케이스 검증 (5개) | P0 | 📋 계획 |
| 4.4 | 문서 작성 (MASTERPLAN, COMPARISON, ROADMAP) | P1 | ✅ 완료 |
| 4.5 | README.md 업데이트 | P1 | 📋 계획 |

### 검증 명령어

```bash
# Benchmarks Game 전체
./target/release/benchmark-bmb run --category compute --all

# Zero-Cost IR 검증
./target/release/benchmark-bmb verify-ir null_check_proof
./target/release/benchmark-bmb verify-ir aliasing_proof
./target/release/benchmark-bmb verify-ir purity_proof

# Surpass 케이스
./target/release/benchmark-bmb run --category surpass --verbose
```

---

## Phase 4: CI 자동화 (v0.5) 📋 계획

### 목표
성능 회귀 자동 감지 및 차단

### 태스크

| ID | 태스크 | 우선순위 | 상태 |
|----|--------|----------|------|
| 5.1 | GitHub Actions 워크플로우 | P0 | 📋 계획 |
| 5.2 | 2% 임계값 자동 검사 | P0 | 📋 계획 |
| 5.3 | PR 차단 규칙 | P0 | 📋 계획 |
| 5.4 | 결과 아티팩트 저장 | P1 | 📋 계획 |
| 5.5 | Slack/Discord 알림 | P2 | 📋 계획 |

### 구현 계획

```yaml
# .github/workflows/benchmark.yml
name: Benchmark Gate
on:
  push:
    branches: [main]
  pull_request:
    branches: [main]

jobs:
  benchmark:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4

      - name: Setup
        run: |
          # Install clang, rustc, bmb

      - name: Run benchmarks
        run: |
          cd ecosystem/benchmark-bmb
          cargo build --release
          ./target/release/benchmark-bmb ci --threshold 2%

      - name: Check gates
        run: |
          ./target/release/benchmark-bmb gate 3.4 --strict

      - name: Upload results
        uses: actions/upload-artifact@v4
        with:
          name: benchmark-results-${{ github.sha }}
          path: ecosystem/benchmark-bmb/results/
```

---

## Phase 5: 대시보드 (v0.6) 📋 계획

### 목표
웹 기반 벤치마크 결과 시각화

### 태스크

| ID | 태스크 | 우선순위 | 상태 |
|----|--------|----------|------|
| 6.1 | 결과 JSON API | P0 | 📋 계획 |
| 6.2 | 시계열 그래프 | P0 | 📋 계획 |
| 6.3 | 언어별 비교 차트 | P1 | 📋 계획 |
| 6.4 | bench.bmb.dev 배포 | P1 | 📋 계획 |
| 6.5 | GitHub 뱃지 | P2 | 📋 계획 |

### 기능 설계

```
bench.bmb.dev/
├── /                    # 메인 대시보드
├── /history             # 시계열 성능 추이
├── /compare             # 언어별 비교
├── /gates               # Gate 상태
└── /api/v1/results.json # API
```

---

## Phase 6: 확장 (v0.7+) 📋 계획

### 추가 벤치마크

| 스위트 | 벤치마크 수 | 목적 | 우선순위 |
|--------|------------|------|----------|
| PolyBench | 30 | 루프 최적화 | P1 |
| CoreMark | 1 | 임베디드 표준 | P1 |
| Embench | 19 | IoT 워크로드 | P2 |
| SPEC CPU | 선택적 | 산업 표준 | P3 |

### 크로스 플랫폼

| 플랫폼 | 상태 | 우선순위 |
|--------|------|----------|
| x86_64-linux | ✅ 지원 | - |
| x86_64-windows | 📋 계획 | P1 |
| aarch64-linux | 📋 계획 | P1 |
| aarch64-macos | 📋 계획 | P2 |
| wasm32 | 📋 계획 | P2 |

---

## 성공 기준

### v0.4 완료 조건
- [ ] Benchmarks Game 10개 모두 검증 (BMB/C ≤1.05x)
- [ ] Zero-Cost 5개 모두 IR 검증 완료
- [ ] Surpass 5개 중 3개 이상 C보다 빠름 확인
- [ ] 문서 3개 완성 (MASTERPLAN, COMPARISON, ROADMAP)

### v0.5 완료 조건
- [ ] GitHub Actions CI 설정 완료
- [ ] 2% 임계값 자동 검사 작동
- [ ] PR에서 성능 회귀 자동 차단

### v0.6 완료 조건
- [ ] bench.bmb.dev 배포
- [ ] 시계열 그래프 표시
- [ ] API 문서화

---

## 리소스

### 참고 자료
- [Benchmarks Game](https://benchmarksgame-team.pages.debian.net/benchmarksgame/)
- [Programming Language Benchmarks](https://programming-language-benchmarks.vercel.app/)
- [How2Bench Guidelines](https://arxiv.org/html/2501.10711v1)
- [PolyBench](https://github.com/cavazos-lab/PolyBench-ACC)
- [CoreMark](https://github.com/eembc/coremark)

### 도구
- **러너**: Rust (ecosystem/benchmark-bmb/runner/)
- **측정**: `std::time::Instant`, 중앙값 5회
- **비교**: clang -O3, rustc --release

### 연락처
- 이슈: https://github.com/bmb-lang/bmb/issues
- 기여: https://github.com/bmb-lang/bmb/blob/main/CONTRIBUTING.md
