// Matrix Multiplication Benchmark
// Measures: nested loops, memory access patterns, cache behavior

const N: usize = 128;

fn matrix_init(m: &mut [i64], n: usize, seed: i64) {
    for i in 0..n {
        for j in 0..n {
            m[i * n + j] = ((i as i64) * (n as i64) + (j as i64) + seed) % 100;
        }
    }
}

fn matrix_multiply(a: &[i64], b: &[i64], c: &mut [i64], n: usize) {
    for i in 0..n {
        for j in 0..n {
            let mut sum: i64 = 0;
            for k in 0..n {
                sum += a[i * n + k] * b[k * n + j];
            }
            c[i * n + j] = sum;
        }
    }
}

fn matrix_sum(m: &[i64], n: usize) -> i64 {
    let mut sum: i64 = 0;
    for i in 0..n * n {
        sum += m[i];
    }
    sum
}

fn main() {
    let mut result: i64 = 0;

    for _ in 0..40 {
        let mut a = vec![0i64; N * N];
        let mut b = vec![0i64; N * N];
        let mut c = vec![0i64; N * N];

        matrix_init(&mut a, N, 1);
        matrix_init(&mut b, N, 2);
        matrix_multiply(&a, &b, &mut c, N);
        result += matrix_sum(&c, N);
    }

    println!("{}", result);
}
