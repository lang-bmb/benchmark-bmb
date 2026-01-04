// Spectral norm benchmark (simplified)
// Measures: matrix operations, floating-point arithmetic

#include <stdio.h>
#include <math.h>

#define N 100

double A(int i, int j) {
    return 1.0 / ((i + j) * (i + j + 1) / 2 + i + 1);
}

void mult_Av(double *v, double *Av, int n) {
    for (int i = 0; i < n; i++) {
        Av[i] = 0;
        for (int j = 0; j < n; j++) {
            Av[i] += A(i, j) * v[j];
        }
    }
}

void mult_Atv(double *v, double *Atv, int n) {
    for (int i = 0; i < n; i++) {
        Atv[i] = 0;
        for (int j = 0; j < n; j++) {
            Atv[i] += A(j, i) * v[j];
        }
    }
}

void mult_AtAv(double *v, double *AtAv, int n) {
    double u[N];
    mult_Av(v, u, n);
    mult_Atv(u, AtAv, n);
}

int main() {
    int n = N;
    double u[N], v[N];

    for (int i = 0; i < n; i++) u[i] = 1.0;

    for (int i = 0; i < 10; i++) {
        mult_AtAv(u, v, n);
        mult_AtAv(v, u, n);
    }

    double vBv = 0, vv = 0;
    for (int i = 0; i < n; i++) {
        vBv += u[i] * v[i];
        vv += v[i] * v[i];
    }

    printf("%.9f\n", sqrt(vBv / vv));
    return 0;
}
