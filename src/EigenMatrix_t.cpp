#include <Eigen/Dense>
#include <iostream>
#include <sys/time.h>

static const int MATRIX_SIZE = 10000;
static const int ITERATION = 1000;

int main()
{


  for(unsigned long j = 100; j < MATRIX_SIZE; j*=2){
    std::cout << "Start benchmark for matrix size " << j << ", iteration " << ITERATION << "\n";
    Eigen::MatrixXf A = Eigen::MatrixXf::Random(j, j);
    Eigen::MatrixXf B = Eigen::MatrixXf::Random(j, j);
    Eigen::MatrixXf C;
    timeval t1, t2, t;
    gettimeofday(&t1, NULL);  

    for (int i = 0; i < ITERATION; ++i) {
      C = A * B;
    } 

    gettimeofday(&t2, NULL);
    timersub(&t2, &t1, &t);
    // std::cout << "A*B: " << A * B << "\n";
    std::cout << (t.tv_sec * 1000.0 + t.tv_usec /1000.0) / ITERATION << " Milliseconds, iteration(" << ITERATION
              << ") O(n^3): " << j*j*j/1000000.0 << " MFLOPS-- Eigen\n";
  }

  std::cout << "Benchmark complete" << std::endl;
}