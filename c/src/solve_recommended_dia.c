#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <timer.h>

void daxpy(const int*, const double*, const double*, const int*, double*, const int*);
void dgemm_(const char*, const char*, const int*, const int*, const int*, const double*, const double*, const int*, const double*, const int*, const double*, double*, const int*);

int main(int argc, char* argv[])
{
  int n, rhs;
  double one = 1.0;
  double minus_one = -1.0;
  double *A, *B, *C;
  double dtime, dtime_save = DBL_MAX, cs_time = DBL_MAX;

  if (argc < 3) {
    printf("pass me 2 arguments: n, rhs\n");
    return (-1);
  } else {
    n = atof(argv[1]);
    rhs = atof(argv[2]);
  }

  for (int it = 0; it < LAMP_REPS; it++) {

    A = (double*)malloc(n * n * sizeof(double));
    B = (double*)malloc(n * rhs * sizeof(double));
    C = (double*)malloc(n * rhs * sizeof(double));

    srand48((unsigned)time((time_t*)NULL));

    for (int i = 0; i < n * n; i++)
      A[i] = drand48();
    for (int i = 0; i < n * rhs; i++) {
      B[i] = drand48();
      C[i] = 0.0;
    }

    // Create Diagonal Matrix
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        if (i != j)
          A[i + j * n] = 0.0;
      }

    /*printf("A = \n");*/
    /*for (int i = 0; i < n; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf("%2.5f ", A[i + j * n]);*/
    /*printf("\n");*/
    /*}*/

    cs_time = cache_scrub();
    dtime = cclock();
    double temp;
    for (int i = 0; i < n; i++) {
      temp = 1 / A[i + i * n];
      daxpy(&rhs, &temp, &B[i], &n, &C[i], &n);
    }
    dtime_save = clock_min_diff(dtime_save, dtime);

    dgemm_("N", "N", &n, &rhs, &n, &one, A, &n, C, &n, &minus_one, B, &n);
    double max_value = abs(B[0]);
    for (int i = 0; i < n * rhs; i++)
      max_value = fmax(fabs(B[i]), max_value);
    if (max_value > 1e-10) {
      printf("Verification failed...\n");
      return (-1);
    }

    free(A);
    free(B);
    free(C);
  };

  printf("solve_dia;%d;%d;%d;%e;%e\n", 0, rhs, n, dtime_save, cs_time);

  return (0);
}
