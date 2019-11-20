#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <timer.h>

int dgemm_(char*, char*, int*, int*, int*, double*, double*, int*, double*, int*, double*, double*, int*);

int main(int argc, char* argv[])
{
  int m, k, n;
  double *A, *B, *C;
  double one = 1.0;
  double cs_time = DBL_MAX, dtime, dtime_save = DBL_MAX;

  if (argc < 4) {
    printf("pass me 3 arguments: m k n [name]\n");
    return (-1);
  } else {
    m = atof(argv[1]);
    k = atof(argv[2]);
    n = atof(argv[3]);
  }

  for (int it = 0; it < LAMP_REPS; it++) {
    A = (double*)malloc(m * k * sizeof(double));
    B = (double*)malloc(k * n * sizeof(double));
    C = (double*)malloc(m * n * sizeof(double));

    srand48((unsigned)time((time_t*)NULL));

    for (int i = 0; i < m * k; i++)
      A[i] = drand48();
    for (int i = 0; i < k * n; i++)
      B[i] = drand48();
    for (int i = 0; i < m * n; i++)
      C[i] = drand48();

    /*printf("A = [\n");*/
    /*for (int i = 0; i < m; i++) {*/
    /*for (int j = 0; j < k; j++)*/
    /*printf(" %lf\t", A[i + j * m]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    /*printf("B = [\n");*/
    /*for (int i = 0; i < k; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf\t", B[i + j * k]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    /*printf("C = [\n");*/
    /*for (int i = 0; i < m; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf\t", C[i + j * m]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    cs_time = cache_scrub();

    dtime = cclock();
    dgemm_("N", "N", &m, &n, &k, &one, A, &m, B, &k, &one, C, &m);
    dtime_save = clock_min_diff(dtime_save, dtime);

    /*printf("C2 = [\n");*/
    /*for (int i = 0; i < m; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf\t", C[i + j * m]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/
    /*printf("using LinearAlgebra\n");*/
    /*printf("C += A * B\n");*/
    /*printf("isapprox(C2, C, atol=1e-4)\n");*/

    free(A);
    free(B);
    free(C);
  };

  if (argv[4]) {
    printf("gemm_explicit_%s;%d;%d;%d;%e;%e\n", argv[4], m, k, n, dtime_save, cs_time);
    printf("gemm_implicit_%s;%d;%d;%d;%e;%e\n", argv[4], m, k, n, dtime_save, cs_time);
  } else {
    printf("gemm_explicit;%d;%d;%d;%e;%e\n", m, k, n, dtime_save, cs_time);
    printf("gemm_implicit;%d;%d;%d;%e;%e\n", m, k, n, dtime_save, cs_time);
  }

  return (0);
}
