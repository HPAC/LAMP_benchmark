#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <timer.h>

int dgemm_(char*, char*, int*, int*, int*, double*, double*, int*, double*, int*, double*, double*, int*);
void daxpy(const int*, const double*, const double*, const int*, double*, const int*);

int main(int argc, char* argv[])
{
  int m, k, n;
  int oni = 1;
  double one = 1.0;
  double zero = 0.0;
  double *A, *B, *C, *D;
  double cs_time = DBL_MAX, dtime, dtime_save = DBL_MAX;

  if (argc < 3) {
    printf("pass me 2 arguments (m=n): m, k\n");
    return (-1);
  } else {
    m = atof(argv[1]);
    k = atof(argv[2]);
  }

  n = m;
  int mn = n * m;

  for (int it = 0; it < LAMP_REPS; it++) {
    A = (double*)malloc(m * k * sizeof(double));
    B = (double*)malloc(k * n * sizeof(double));
    C = (double*)malloc(m * n * sizeof(double));
    D = (double*)malloc(m * n * sizeof(double));

    srand48((unsigned)time((time_t*)NULL));

    for (int i = 0; i < m * k; i++)
      A[i] = drand48();
    for (int i = 0; i < k * n; i++)
      B[i] = drand48();
    for (int i = 0; i < m * n; i++) {
      C[i] = 0.0;
      D[i] = 0.0;
    }

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

    /*printf("D = [\n");*/
    /*for (int i = 0; i < m; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf\t", D[i + j * m]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    cs_time = cache_scrub();

    dtime = cclock();
    dgemm_("N", "N", &m, &n, &k, &one, A, &m, B, &k, &zero, C, &m);
    dgemm_("N", "N", &m, &n, &k, &one, A, &m, B, &k, &zero, D, &m);
    daxpy(&mn, &one, C, &oni, D, &oni);
    dtime_save = clock_min_diff(dtime_save, dtime);

    /*printf("C = [\n");*/
    /*for (int i = 0; i < m; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf\t", C[i + j * m]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    /*printf("D = [\n");*/
    /*for (int i = 0; i < m; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf\t", D[i + j * m]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    free(A);
    free(B);
    free(C);
    free(D);
  };

  printf("subexpr_nai;%d;%d;%d;%e;%e\n", m, k, n, dtime_save, cs_time);

  return (0);
}
