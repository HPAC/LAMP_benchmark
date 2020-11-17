#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <timer.h>
#include "mkl.h"

int main(int argc, char* argv[])
{
  int m, k, n;
  double one = 1.0, zero = 0.0;
  double *A, *M1, *M2, *B, *T1, *T2, *C;
  double dtime, dtime_save = DBL_MAX, cs_time = DBL_MAX;

  if (argc < 4) {
    printf("pass me 3 arguments: m, k, n\n");
    return (-1);
  } else {
    m = atof(argv[1]);
    k = atof(argv[2]);
    n = atof(argv[3]);
  }

  int small = k / 5;

  A = (double*)mkl_malloc(m * k * sizeof(double), 64);
  M1 = (double*)mkl_malloc(k * small * sizeof(double), 64);
  M2 = (double*)mkl_malloc(small * k * sizeof(double), 64);
  B = (double*)mkl_malloc(k * n * sizeof(double), 64);

  T1 = (double*)mkl_malloc(m * small * sizeof(double), 64);
  T2 = (double*)mkl_malloc(small * n * sizeof(double), 64);
  C = (double*)mkl_malloc(m * n * sizeof(double), 64);

  srand48((unsigned)time((time_t*)NULL));
  for (int i = 0; i < m * k; i++) A[i] = drand48();
  for (int i = 0; i < k * small; i++) M1[i] = drand48();
  for (int i = 0; i < small * k; i++) M2[i] = drand48();
  for (int i = 0; i < k * n; i++) B[i] = drand48();

  for (int it = 0; it < LAMP_REPS; it++) {

    for (int i = 0; i < m * small; i++) T1[i] = 0.0;
    for (int i = 0; i < small * n; i++) T2[i] = 0.0;
    for (int i = 0; i < m * n; i++) C[i] = 0.0;

    /*printf("A = [\n");*/
    /*for (int i = 0; i < m; i++) {*/
    /*for (int j = 0; j < k; j++)*/
    /*printf(" %lf ", A[i + j * m]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    /*printf("m1 = [\n");*/
    /*for (int i = 0; i < k; i++) {*/
    /*for (int j = 0; j < k_half; j++)*/
    /*printf(" %lf ", m1[i + j * k]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    /*printf("m2 = [\n");*/
    /*for (int i = 0; i < k_half; i++) {*/
    /*for (int j = 0; j < k; j++)*/
    /*printf(" %lf ", m2[i + j * k_half]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    /*printf("B = [\n");*/
    /*for (int i = 0; i < k; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf ", B[i + j * k]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    /*printf("t1 = A*m1;\n");*/
    /*printf("t2 = m2*B;\n");*/
    /*printf("C1 = t1*t2;\n");*/

    cs_time = cache_scrub();

    dtime = cclock();
    dgemm("N", "N", &m, &small, &k, &one, A, &m, M1, &k, &zero, T1, &m);
    dgemm("N", "N", &small, &n, &k, &one, M2, &small, B, &k, &zero, T2, &small);
    dgemm("N", "N", &m, &n, &small, &one, T1, &m, T2, &small, &zero, C, &m);
    dtime_save = clock_min_diff(dtime_save, dtime);

    /*printf("C = [\n");*/
    /*for (int i = 0; i < m; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf ", C[i + j * m]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/
  }

  mkl_free(A);
  mkl_free(B);
  mkl_free(C);
  mkl_free(T1);
  mkl_free(T2);
  mkl_free(M1);
  mkl_free(M2);

  printf("mc_mixed_guid;%d;%d;%d;%e;%e\n", m, k, n, dtime_save, cs_time);

  return (0);
}
