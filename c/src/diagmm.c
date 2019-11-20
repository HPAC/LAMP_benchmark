#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <timer.h>

void daxpy(const int*, const double*, const double*, const int*, double*, const int*);

int main(int argc, char* argv[])
{
  int n;
  double *A, *B, *C;
  double cs_time = DBL_MAX, dtime, dtime_save = DBL_MAX;

  if (argc < 2) {
    printf("pass me 1 argument: n\n");
    return (-1);
  } else {
    n = atof(argv[1]);
  }

  for (int it = 0; it < LAMP_REPS; it++) {
    A = (double*)malloc(n * n * sizeof(double));
    B = (double*)malloc(n * n * sizeof(double));
    C = (double*)malloc(n * n * sizeof(double));

    srand48((unsigned)time((time_t*)NULL));

    for (int i = 0; i < n * n; i++) {
      A[i] = drand48();
      B[i] = drand48();
      C[i] = 0.0;
    }
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        if (i == j)
          A[i + j * n] = drand48();
        else
          A[i + j * n] = 0.0;
      }

    /*printf("A = [\n");*/
    /*for (int i = 0; i < n; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf\t", A[i + j * n]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    /*printf("B = [\n");*/
    /*for (int i = 0; i < n; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf\t", B[i + j * n]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    /*printf("C = [\n");*/
    /*for (int i = 0; i < n; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf\t", C[i + j * n]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    cs_time = cache_scrub();

    dtime = cclock();
    for (int i = 0; i < n; i++)
      daxpy(&n, &A[i + i * n], &B[i], &n, &C[i], &n);
    dtime_save = clock_min_diff(dtime_save, dtime);

    /*printf("C2 = [\n");*/
    /*for (int i = 0; i < n; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf\t", C[i + j * n]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/
    /*printf("using LinearAlgebra\n");*/
    /*printf("C = A * B\n");*/
    /*printf("isapprox(C2, C, atol=1e-4)\n");*/

    free(A);
    free(B);
    free(C);
  };

  printf("diagmm;%d;%d;%d;%e;%e\n", n, n, n, dtime_save, cs_time);

  return (0);
}
