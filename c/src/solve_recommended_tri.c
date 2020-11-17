#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <timer.h>
#include "mkl.h"

int main(int argc, char* argv[])
{
  int n, rhs;
  double one = 1.0;
  double minus_one = -1.0;
  double *A, *B, *B_orig, *A_orig;
  double dtime, dtime_save = DBL_MAX, cs_time = DBL_MAX;

  if (argc < 3) {
    printf("pass me 2 arguments: n, rhs\n");
    return (-1);
  } else {
    n = atof(argv[1]);
    rhs = atof(argv[2]);
  }

  srand48((unsigned)time((time_t*)NULL));

  A = (double*)mkl_malloc(n * n * sizeof(double), 64);
  A_orig = (double*)mkl_malloc(n * n * sizeof(double), 64);
  B = (double*)mkl_malloc(n * rhs * sizeof(double), 64);
  B_orig = (double*)mkl_malloc(n * rhs * sizeof(double), 64);

  for (int it = 0; it < LAMP_REPS; it++) {

    for (int i = 0; i < n * n; i++) A[i] = drand48();
    for (int i = 0; i < n * rhs; i++) {
      B[i] = drand48();
      B_orig[i] = B[i];
    }

    // Create Triangular Matrix
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        if (i < j)
          A[i + j * n] = 0.0;
      }
    for (int i = 0; i < n * n; i++) {
      A_orig[i] = A[i];
    }
    /*printf("A = \n");*/
    /*for (int i = 0; i < n; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf("%2.5f ", A[i + j * n]);*/
    /*printf("\n");*/
    /*}*/

    int solve_info = 0;

    cs_time = cache_scrub();
    dtime = cclock();
    dtrtrs_("L", "N", "N", &n, &rhs, A, &n, B, &n, &solve_info);
    dtime_save = clock_min_diff(dtime_save, dtime);

    dgemm("N", "N", &n, &rhs, &n, &one, A_orig, &n, B, &n, &minus_one, B_orig, &n);
    double max_value = abs(B_orig[0]);
    for (int i = 0; i < n * rhs; i++)
      max_value = fmax(fabs(B_orig[i]), max_value);
    if (max_value > 1e-10) {
      printf("Verification failed...\n");
      return (-1);
    }
  }
  mkl_free(A);
  mkl_free(A_orig);
  mkl_free(B);
  mkl_free(B_orig);

  printf("solve_tri;%d;%d;%d;%e;%e\n", 0, rhs, n, dtime_save, cs_time);

  return (0);
}
