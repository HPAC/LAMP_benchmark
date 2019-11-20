#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <timer.h>

void dtrmm_(const char*, const char*, const char*, const char*, const int*, const int*, const double*, const double*, const int*, double*, const int*);

int main(int argc, char* argv[])
{
  int m, n;
  double one = 1.0;
  double *A, *B;
  double dtime, dtime_save = DBL_MAX, cs_time = DBL_MAX;

  if (argc < 3) {
    printf("pass me 2 argument: m, n\n");
    return (-1);
  } else {
    m = atof(argv[1]);
    n = atof(argv[2]);
  }

  for (int it = 0; it < LAMP_REPS; it++) {
    A = (double*)malloc(m * m * sizeof(double));
    B = (double*)malloc(m * n * sizeof(double));

    srand48((unsigned)time((time_t*)NULL));

    for (int i = 0; i < m * m; i++)
      A[i] = drand48();
    for (int i = 0; i < m * n; i++)
      B[i] = drand48();

    for (int i = 0; i < m; i++)
      for (int j = 0; j < m; j++)
        if (i < j)
          A[i + j * n] = 0.0;

    /*printf("A = [\n");*/
    /*for (int i = 0; i < m; i++) {*/
    /*for (int j = 0; j < m; j++)*/
    /*printf(" %lf\t", A[i + j * m]);*/
    /*printf("\n");*/
    /*}*/
    /*printf("];\n");*/

    /*printf("B = [\n");*/
    /*for (int i = 0; i < m; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf\t", B[i + j * m]);*/
    /*printf("\n");*/
    /*}*/
    /*printf("];\n");*/

    cs_time = cache_scrub();

    dtime = cclock();
    dtrmm_("L", "L", "N", "N", &m, &n, &one, A, &m, B, &m);
    dtime_save = clock_min_diff(dtime_save, dtime);

    /*printf("B2 = [\n");*/
    /*for (int i = 0; i < m; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf\t", B[i + j * n]);*/
    /*printf("\n");*/
    /*}*/
    /*printf("];\n");*/
    /*printf("using LinearAlgebra\n");*/
    /*printf("B = A * B\n");*/
    /*printf("isapprox(B2, B, atol=1e-4)\n");*/

    free(A);
    free(B);
  };

  printf("trmm_explicit;%d;%d;%d;%e;%e\n", m, 0, n, dtime_save, cs_time);
  printf("trmm_implicit;%d;%d;%d;%e;%e\n", m, 0, n, dtime_save, cs_time);

  return (0);
}
