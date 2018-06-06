#include <Eigen/Dense>
#include <iostream>
#include <sys/time.h>

static const int MATRIX_SIZE = 1000;
static const int ITERATION = 1;

int main()
{
  Eigen::MatrixXd A = Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
  Eigen::MatrixXd B = Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
  Eigen::MatrixXd C;
  timeval t1, t2, t;
  gettimeofday(&t1, NULL);

  for (int i = 0; i < ITERATION; ++i) {
    C = A * B;
  }

  gettimeofday(&t2, NULL);
  timersub(&t2, &t1, &t);
  // std::cout << "A*B: " << A * B << "\n";
  std::cout << t.tv_sec + t.tv_usec / 1000.0 << " Milliseconds, iteration(" << ITERATION
            << ") -- Eigen" << std::endl;
}