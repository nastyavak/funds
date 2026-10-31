#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

typedef struct {
    double *coords;
    int n;
} Vector;

typedef double (*NormFunc)(Vector, void *); //тип данных из-заьtypedef

double norma_inf(Vector v, void *skip) {
    double max = fabs(v.coords[0]);
    for (int i = 1; i < v.n; i++) {
        double abs_val = fabs(v.coords[i]);
        if (abs_val > max)
            max = abs_val;
    }
    return max;
}

double norma_p(Vector v, void *pp) {
    double p = *(double *)pp;
    double res = 0;
    for (int i = 0; i < v.n; i++) {
        res += pow(fabs(v.coords[i]), p);
    }
    return pow(res, 1.0 / p);
}

double norma_A(Vector v, void *matr) {
    double *A = (double *)matr;
    double *Ax = (double *)malloc(v.n * sizeof(double));
    for (int i = 0; i < v.n; i++) {
        Ax[i] = 0;
        for (int j = 0; j < v.n; j++) {
            Ax[i] += A[i * v.n + j] * v.coords[j];
        }
    }
    double dot = 0;
    for (int i = 0; i < v.n; i++) {
        dot += Ax[i] * v.coords[i];
    }
    free(Ax);
    return sqrt(dot);
}

void func(int n, int vec_count, Vector *vecs, int norm_count, ...) {
    va_list args;
    va_start(args, norm_count);
    for (int k = 0; k < norm_count; k++) {
        NormFunc f = va_arg(args, NormFunc);
        void *params = va_arg(args, void *);

        double max_norm = -1;
        int *idx = (int *)malloc(vec_count * sizeof(int));
        int count = 0;
        for (int i = 0; i < vec_count; i++) {
            double norm_val = f(vecs[i], params);
            if (norm_val > max_norm) {
                max_norm = norm_val;
                count = 0;
                idx[count] = i;
                count++;
            }
        }
        printf("норма %d, макс длина = %.5f\nвекторы ", k + 1, max_norm);
        for (int i = 0; i < count; i++) {
            printf("%d ", idx[i] + 1);
        }
        printf("\n");
        free(idx);
    }
    va_end(args);
}

int main() {
    double coords1[] = {1, 2, 3};
    double coords2[] = {4, -1, 2};
    double coords3[] = {-2, 5, 1};
    Vector v1 = {coords1, 3};
    Vector v2 = {coords2, 3};
    Vector v3 = {coords3, 3};
    Vector vecs[] = {v1, v2, v3};

    double p = 2.0;
    double A[] = {2, 1, 0,
                  1, 3, 1,
                  0, 1, 2};

    func(3, 3, vecs, 3, norma_inf, NULL, norma_p, &p, norma_A, A);

    return 0;
}
