#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <timer.h>
#include "mkl.h"

int main(int argc, char* argv[])
{
  int n, k;
  double one = 1.0;
  double *A, *B, *C;
  double dtime, dtime_save = DBL_MAX, cs_time = DBL_MAX;

  if (argc < 3) {
    printf("pass me 2 arguments: n, k\n");
    return (-1);
  } else {
    n = atof(argv[1]);
    k = atof(argv[2]);
  }
  srand48((unsigned)time((time_t*)NULL));

  A = (double*)mkl_malloc(n * k * sizeof(double), 64);
  B = (double*)mkl_malloc(n * k * sizeof(double), 64);
  C = (double*)mkl_malloc(n * n * sizeof(double), 64);

  for (int i = 0; i < n * k; i++) A[i] = drand48();
  for (int i = 0; i < n * k; i++) B[i] = drand48();

  for (int it = 0; it < LAMP_REPS; it++) {

    for (int i = 0; i < n * n; i++) C[i] = drand48();

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        C[i + j * n] = C[j + i * n];

    /*printf("A = [\n");*/
    /*for (int i = 0; i < n; i++) {*/
    /*for (int j = 0; j < k; j++)*/
    /*printf(" %lf\t", A[i + j * n]);*/
    /*printf("\n");*/
    /*}*/
    /*printf("];\n");*/

    /*printf("B = [\n");*/
    /*for (int i = 0; i < n; i++) {*/
    /*for (int j = 0; j < k; j++)*/
    /*printf(" %lf\t", B[i + j * n]);*/
    /*printf("\n");*/
    /*}*/
    /*printf("];\n");*/

    /*printf("C = [\n");*/
    /*for (int i = 0; i < n; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf\t", C[i + j * n]);*/
    /*printf("\n");*/
    /*}*/
    /*printf("];\n");*/

    cs_time = cache_scrub();
    dtime = cclock();
    dsyr2k("L", "N", &n, &k, &one, A, &n, B, &n, &one, C, &n);
    dtime_save = clock_min_diff(dtime_save, dtime);

    /*printf("C2 = [\n");*/
    /*for (int i = 0; i < n; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf\t", C[i + j * n]);*/
    /*printf("\n");*/
    /*}*/
    /*printf("];\n");*/
    /*printf("using LinearAlgebra\n");*/
    /*printf("C += A * transpose(B) + B * transpose(A)\n");*/
    /*printf("isapprox(Symmetric(C2, :L), C, atol=1e-4)\n");*/
  }
  mkl_free(A);
  mkl_free(B);
  mkl_free(C);

  printf("syr2k_explicit;%d;%d;%d;%e;%e\n", 0, k, n, dtime_save, cs_time);

  return (0);
}
