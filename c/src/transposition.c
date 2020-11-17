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
  double one = 1.0;
  double zero = 0.0;
  double *A, *B, *C;
  double cs_time = DBL_MAX,
         dtime_nn, dtime_save_nn = DBL_MAX,
         dtime_nt, dtime_save_nt = DBL_MAX,
         dtime_tn, dtime_save_tn = DBL_MAX,
         dtime_tt, dtime_save_tt = DBL_MAX;

  if (argc < 4) {
    printf("pass me 3 arguments: m, k, n\n");
    return (-1);
  } else {
    m = atof(argv[1]);
    k = atof(argv[2]);
    n = atof(argv[3]);
  }
  srand48((unsigned)time((time_t*)NULL));

  A = (double*)mkl_malloc(m * k * sizeof(double), 64);
  B = (double*)mkl_malloc(k * n * sizeof(double), 64);
  C = (double*)mkl_malloc(m * n * sizeof(double), 64);

  for (int i = 0; i < m * k; i++) A[i] = drand48();
  for (int i = 0; i < k * n; i++) B[i] = drand48();

  for (int it = 0; it < LAMP_REPS; it++) {

    /*int j;*/
    /*printf("A = [\n");*/
    /*for(int i=0; i<m; i++ ){*/
    /*for(int j=0; j<k; j++ ) printf(" %lf\t", A[i+j*m] );*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    /*printf("B = [\n");*/
    /*for(int i=0; i<k; i++ ){*/
    /*for(int j=0; j<n; j++ ) printf(" %lf\t", B[i+j*k] );*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    /*printf("C = [\n");*/
    /*for(int i=0; i<m; i++ ){*/
    /*for(int j=0; j<n; j++ ) printf(" %lf\t", C[i+j*m] );*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    cs_time = cache_scrub();
    dtime_tn = cclock();
    dgemm("T", "N", &m, &n, &k, &one, A, &n, B, &m, &zero, C, &n);
    dtime_save_tn = clock_min_diff(dtime_save_tn, dtime_tn);

    cs_time = cache_scrub();
    dtime_nt = cclock();
    dgemm("N", "T", &m, &n, &k, &one, A, &n, B, &m, &zero, C, &n);
    dtime_save_nt = clock_min_diff(dtime_save_nt, dtime_nt);

    cs_time = cache_scrub();
    dtime_tt = cclock();
    dgemm("T", "T", &m, &n, &k, &one, A, &n, B, &m, &zero, C, &n);
    dtime_save_tt = clock_min_diff(dtime_save_tt, dtime_tt);

    cs_time = cache_scrub();
    dtime_nn = cclock();
    dgemm("N", "N", &m, &n, &k, &one, A, &n, B, &m, &zero, C, &n);
    dtime_save_nn = clock_min_diff(dtime_save_nn, dtime_nn);

    /*printf("C2 = [\n");*/
    /*for(int i=0; i<m; i++ ){*/
    /*for(int j=0; j<n; j++ ) printf(" %lf\t", C[i+j*m] );*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/
  }
  mkl_free(A);
  mkl_free(B);
  mkl_free(C);

  printf("tr_nn_explicit;%d;%d;%d;%e;%e\n", m, k, n, dtime_save_nn, cs_time);
  printf("tr_tn_explicit;%d;%d;%d;%e;%e\n", m, k, n, dtime_save_tn, cs_time);
  printf("tr_nt_explicit;%d;%d;%d;%e;%e\n", m, k, n, dtime_save_nt, cs_time);
  printf("tr_tt_explicit;%d;%d;%d;%e;%e\n", m, k, n, dtime_save_tt, cs_time);
  return (0);
}
