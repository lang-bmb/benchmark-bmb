// Spectral norm benchmark (simplified)
// Measures: matrix operations, floating-point arithmetic

const N: usize = 1000;

fn a(i: i64, j: i64) -> f64 {
    1.0 / (((i + j) * (i + j + 1) / 2 + i + 1) as f64)
}

fn mult_av(v: &[f64; N], av: &mut [f64; N], n: usize) {
    for i in 0..n {
        av[i] = 0.0;
        for j in 0..n {
            av[i] += a(i as i64, j as i64) * v[j];
        }
    }
}

fn mult_atv(v: &[f64; N], atv: &mut [f64; N], n: usize) {
    for i in 0..n {
        atv[i] = 0.0;
        for j in 0..n {
            atv[i] += a(j as i64, i as i64) * v[j];
        }
    }
}

fn mult_atav(v: &[f64; N], atav: &mut [f64; N], n: usize, u: &mut [f64; N]) {
    mult_av(v, u, n);
    mult_atv(u, atav, n);
}

fn main() {
    let n = N;
    let mut u = [1.0f64; N];
    let mut v = [0.0f64; N];
    let mut tmp = [0.0f64; N];

    for _ in 0..10 {
        mult_atav(&u, &mut v, n, &mut tmp);
        mult_atav(&v, &mut u, n, &mut tmp);
    }

    let mut vbv = 0.0f64;
    let mut vv = 0.0f64;

    for i in 0..n {
        vbv += u[i] * v[i];
        vv += v[i] * v[i];
    }

    println!("{:.9}", (vbv / vv).sqrt());
}
