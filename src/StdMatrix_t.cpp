#include <iostream>
#include <sys/time.h>
#include <Fixed.h>

static const int MATRIX_SIZE = 800;
static const long ITERATION = 100;
typedef numeric::Fixed<16, 16> Fixed16_16;

template <typename T>
void Transpose(int size, T** m)
{
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      std::swap(m[i][j], m[j][i]);
    }
  }
}

template <typename T>
void SeqMatrixMult(int size, T** m1, T** m2, T** result)
{
  Transpose(size, m2);
  for (int i = 0; i < size; i++) {
    const T* tempM1 = m1[i];
    T* temp = result[i];
    for (int j = 0; j < size; j++) {
      T c = 0;
      T* tempM2 = m2[j];
      for (int k = 0; k < size; k++) {
        c += tempM1[k] * tempM2[k];
      }
      temp[j] = c;
    }
  }
  Transpose(size, m2);
}

int main()
{
  float **A, **B, **C;

  A = new float*[MATRIX_SIZE];
  B = new float*[MATRIX_SIZE];
  C = new float*[MATRIX_SIZE];

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

  Fixed16_16 **fixedA, **fixedB, **fixedC;
  fixedA = new Fixed16_16*[MATRIX_SIZE];
  fixedB = new Fixed16_16*[MATRIX_SIZE];
  fixedC = new Fixed16_16*[MATRIX_SIZE];

  for (int i = 0; i < MATRIX_SIZE; i++) {
    fixedA[i] = new Fixed16_16[MATRIX_SIZE];
    fixedB[i] = new Fixed16_16[MATRIX_SIZE];
    fixedC[i] = new Fixed16_16[MATRIX_SIZE];
  }

  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      fixedA[i][j] = Fixed16_16(rand());
      fixedB[i][j] = Fixed16_16(rand());
    }
  }

  timeval t1, t2, t;

  // For naive implementation with floating point
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

  std::cout << (t.tv_sec * 1000.0 + t.tv_usec / 1000.0) / ITERATION
            << " Milliseconds -- Naive floating point" << std::endl;

  // For naive implementation with fixed point
  gettimeofday(&t1, NULL);

  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      fixedC[i][j] = 0;
      for (int k = 0; k < MATRIX_SIZE; k++) {
        fixedC[i][j] += fixedA[i][k] * fixedB[k][j];
      }
    }
  }

  gettimeofday(&t2, NULL);
  timersub(&t2, &t1, &t);

  std::cout << (t.tv_sec * 1000.0 + t.tv_usec / 1000.0) / ITERATION
            << " Milliseconds -- Naive fixed point" << std::endl;

  gettimeofday(&t1, NULL);

  //  for (int i = 0; i < MATRIX_SIZE; i++) {
  //    for (int j = 0; j < MATRIX_SIZE; j++) {
  //      C[i][j] = 0;
  //      for (int k = 0; k < MATRIX_SIZE; k++) {
  //        C[i][j] += A[i][k] * B[k][j];
  //      }
  //    }
  //  }

  for (int i = 0; i < ITERATION; ++i) {
    SeqMatrixMult<float>(MATRIX_SIZE, A, B, C);
  }

  gettimeofday(&t2, NULL);
  timersub(&t2, &t1, &t);

  std::cout << (t.tv_sec * 1000.0 + t.tv_usec / 1000.0) / ITERATION << " Milliseconds -- Optimized"
            << std::endl;

  for (int i = 0; i < MATRIX_SIZE; i++) {
    delete A[i];
    delete B[i];
    delete C[i];
    delete fixedA[i];
    delete fixedB[i];
    delete fixedC[i];
  }

  delete A;
  delete B;
  delete C;
  delete fixedA;
  delete fixedB;
  delete fixedC;
}