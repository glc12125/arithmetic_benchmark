#include <iostream>
#include <sys/time.h>

static const int MATRIX_SIZE = 1000;

int main()
{
  float **A, **B, **C;

  A = new float *[MATRIX_SIZE];
  B = new float *[MATRIX_SIZE];
  C = new float *[MATRIX_SIZE];

  for (int i = 0; i < MATRIX_SIZE; i++) {
    A[i] = new float[MATRIX_SIZE];
    B[i] = new float[MATRIX_SIZE];
    C[i] = new float[MATRIX_SIZE];
  }

  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      A[i][j] = rand();
      B[i][j] = rand();
    }
  }

  timeval t1, t2, t;
  gettimeofday(&t1, NULL);

  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      C[i][j] = 0;
      for (int k = 0; k < MATRIX_SIZE; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  gettimeofday(&t2, NULL);
  timersub(&t2, &t1, &t);

  std::cout << t.tv_sec + t.tv_usec / 1000000.0 << " Seconds -- Standard" << std::endl;

  for (int i = 0; i < MATRIX_SIZE; i++) {
    delete A[i];
    delete B[i];
    delete C[i];
  }

  delete A;
  delete B;
  delete C;
}