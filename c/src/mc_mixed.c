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
  double one = 1.0;
  double zero = 0.0;
  double *A, *m1, *m2, *B, *t1, *t2, *C;
  double dtime, dtime_save = DBL_MAX, cs_time = DBL_MAX;

  if (argc < 4) {
    printf("pass me 3 arguments: m, k, n\n");
    return (-1);
  } else {
    m = atof(argv[1]);
    k = atof(argv[2]);
    n = atof(argv[3]);
  }

  int k_half = k / 2;

  for (int it = 0; it < LAMP_REPS; it++) {
    A = (double*)malloc(m * k * sizeof(double));
    m1 = (double*)malloc(k * k_half * sizeof(double));
    m2 = (double*)malloc(k_half * k * sizeof(double));
    B = (double*)malloc(k * n * sizeof(double));

    t1 = (double*)malloc(m * k_half * sizeof(double));
    t2 = (double*)malloc(k_half * n * sizeof(double));
    C = (double*)malloc(m * n * sizeof(double));

    srand48((unsigned)time((time_t*)NULL));

    for (int i = 0; i < m * k; i++)
      A[i] = drand48();
    for (int i = 0; i < k * k_half; i++)
      m1[i] = drand48();
    for (int i = 0; i < k_half * k; i++)
      m2[i] = drand48();
    for (int i = 0; i < k * n; i++)
      B[i] = drand48();

    for (int i = 0; i < m * k_half; i++)
      t1[i] = 0.0;
    for (int i = 0; i < k_half * n; i++)
      t2[i] = 0.0;
    for (int i = 0; i < m * n; i++)
      C[i] = 0.0;

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
    dgemm_("N", "N", &m, &k_half, &k, &one, A, &m, m1, &k, &zero, t1, &m);
    dgemm_("N", "N", &k_half, &n, &k, &one, m2, &k_half, B, &k, &zero, t2, &k_half);
    dgemm_("N", "N", &m, &n, &k_half, &one, t1, &m, t2, &k_half, &zero, C, &m);
    dtime_save = clock_min_diff(dtime_save, dtime);

    /*printf("C = [\n");*/
    /*for (int i = 0; i < m; i++) {*/
    /*for (int j = 0; j < n; j++)*/
    /*printf(" %lf ", C[i + j * m]);*/
    /*printf(";\n");*/
    /*}*/
    /*printf("];\n");*/

    free(A);
    free(B);
    free(C);
    free(t1);
    free(t2);
    free(m1);
    free(m2);
  };

  printf("mc_mixed_guid;%d;%d;%d;%e;%e\n", m, k, n, dtime_save, cs_time);

  return (0);
}
