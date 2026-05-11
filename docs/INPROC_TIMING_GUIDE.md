# In-Process Timing Harness Guide

> Created: 2026-05-11 (Cycle 2685)
> Status: Standard pattern for all new compute benches

## 동기

기존 benchmark 측정 방식 (process-level `time` 도구) 의 문제:
- 프로세스 startup overhead (수 ms) 가 짧은 워크로드를 압도
- printf/링크 라이브러리 load 시간 포함
- LLVM 상수 폴딩으로 워크로드 자체가 사라질 위험

In-process timing 패턴 (Cycle 2661 nqueen에서 검증):
- `time_ns()` 로 워크로드 직전/직후 측정
- `bmb_black_box()` 로 DCE/CSE/IPC 방지
- 측정 결과를 stdout에 println

## BMB harness 패턴

```bmb
fn solve(...) -> i64 = ...;  // 측정 대상

// DCE 방지를 위한 black_box 호출
fn run_benchmark(seed: i64, iterations: i64, acc: i64, i: i64) -> i64 =
    if i >= iterations { acc }
    else {
        let input = bmb_black_box(seed);
        let result = solve(input);
        run_benchmark(seed, iterations, acc + bmb_black_box(result), i + 1)
    };

fn main() -> i64 = {
    // Warmup (캐시 워밍 + JIT 효과 제거)
    let warmup = bmb_black_box(15);
    let _w = bmb_black_box(solve(warmup));

    let t0 = time_ns();
    let result = run_benchmark(15, 10, 0, 0);  // iterations = 10
    let t1 = time_ns();
    let elapsed_us = (t1 - t0) / 1000;

    let _r = println(result);       // 결과값 (정확성 가드)
    let _e = println(elapsed_us);   // 측정 시간 (마이크로초)
    0
};
```

## C baseline harness 패턴

```c
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
static int64_t time_ns(void) {
    static LARGE_INTEGER freq = {0};
    if (freq.QuadPart == 0) QueryPerformanceFrequency(&freq);
    LARGE_INTEGER c; QueryPerformanceCounter(&c);
    int64_t s = c.QuadPart / freq.QuadPart;
    int64_t r = c.QuadPart % freq.QuadPart;
    return s * 1000000000LL + (r * 1000000000LL) / freq.QuadPart;
}
#else
static int64_t time_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (int64_t)(ts.tv_sec * 1000000000LL + ts.tv_nsec);
}
#endif

// volatile sink mirrors bmb_black_box 정확히
static volatile int64_t black_sink;
static int64_t black_box(int64_t v) { black_sink = v; return black_sink; }

int64_t solve(...) { ... }

int main(void) {
    int64_t warmup = black_box(15);
    (void)black_box(solve(warmup));

    int64_t t0 = time_ns();
    int64_t result = 0;
    for (int i = 0; i < 10; i++) {
        int64_t input = black_box(15);
        result += black_box(solve(input));
    }
    int64_t t1 = time_ns();
    int64_t elapsed_us = (t1 - t0) / 1000;

    printf("%lld\n%lld\n", (long long)result, (long long)elapsed_us);
    return 0;
}
```

## 빌드 명령

### BMB
```bash
./target/release/bmb build main_inproc.bmb -o main_inproc --release
```

### C (clang baseline)
```bash
clang -O3 -march=native main_inproc.c -o main_inproc_c
```

### C (gcc baseline)
```bash
gcc -O3 -march=native main_inproc.c -o main_inproc_gcc
```

### Rust
```rust
use std::hint::black_box;
use std::time::Instant;

fn main() {
    let warmup = black_box(15i64);
    let _w = black_box(solve(warmup));

    let t0 = Instant::now();
    let mut result: i64 = 0;
    for _ in 0..10 {
        let input = black_box(15i64);
        result += black_box(solve(input));
    }
    let elapsed_us = t0.elapsed().as_micros();

    println!("{}", result);
    println!("{}", elapsed_us);
}
```

빌드: `rustc -C opt-level=3 -C target-cpu=native main.rs -o main_inproc_rust`

## 검증 체크리스트

1. **결과값 일치**: BMB / C / Rust 출력 첫 줄이 같아야 함 (DCE 안 됐는지 확인)
2. **`bmb_black_box` 누락 시**: 컴파일러가 워크로드 전체를 fold 가능 → elapsed_us = 0 또는 비현실적 값
3. **iterations 충분**: 10회 이상, 1회 측정시간 ≥ 1ms 권장 (jitter 압도)
4. **워밍업 필수**: 첫 호출은 항상 측정에서 제외 (cold-path bias)

## 적용 현황 (2026-05-11)

| Bench | inproc 패턴 |
|-------|-------------|
| `compute/nqueen` | ✅ `main_inproc.bmb` 구현 (Cycle 2661) |
| 404 다른 bench | ❌ 미적용 — 점진적 전환 권장 |

## 권장 작업

- 신규 bench 작성 시 본 패턴 표준 사용
- 기존 bench는 우선순위 (Tier 1) 부터 점진 변환
- 자동 변환 스크립트는 main.bmb / main.c 패턴이 다양 → 수동 변환 안전

## 참고

- Cycle 2661 nqueen 첫 적용 사이클
- `bmb_runtime.c`의 `bmb_black_box` / `bmb_time_ns` 구현
- nqueen `main_inproc.bmb` 와 `c/main_inproc.c` 실제 샘플
