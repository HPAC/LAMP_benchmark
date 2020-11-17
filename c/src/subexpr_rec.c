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
  int oni = 1;
  double one = 1.0;
  double zero = 0.0;
  double *A, *B, *C;
  double cs_time = DBL_MAX, dtime, dtime_save = DBL_MAX;

  if (argc < 3) {
    printf("pass me 2 arguments (m=n): m, k\n");
    return (-1);
  } else {
    m = atof(argv[1]);
    k = atof(argv[2]);
  }

  n = m;

  srand48((unsigned)time((time_t*)NULL));

  A = (double*)mkl_malloc(m * k * sizeof(double), 64);
  B = (double*)mkl_malloc(k * n * sizeof(double), 64);
  C = (double*)mkl_malloc(m * n * sizeof(double), 64);

  for (int i = 0; i < m * k; i++) A[i] = drand48();
  for (int i = 0; i < k * n; i++) B[i] = drand48();

  for (int it = 0; it < LAMP_REPS; it++) {

    for (int i = 0; i < m * n; i++) C[i] = 0.0;

    /*int j;*/
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

    int mn = m * n;
    double two = 2.0;
    cs_time = cache_scrub();
    dtime = cclock();
    dgemm("N", "N", &m, &n, &k, &one, A, &m, B, &k, &zero, C, &m);
    dscal(&mn, &two, C, &oni);
    dtime_save = clock_min_diff(dtime_save, dtime);

    /*printf("C = [\n");*/
    /*for (int i = 0; i < m; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf\t", C[i + j * m]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/
  }
  mkl_free(A);
  mkl_free(B);
  mkl_free(C);

  printf("subexpr_rec;%d;%d;%d;%e;%e\n", m, k, n, dtime_save, cs_time);

  return (0);
}
