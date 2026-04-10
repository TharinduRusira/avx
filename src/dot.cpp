///
//    Compute vector dot using AVX-512
//    Tharindu Patabandi <tharindu at protonmail dot com>
///

#include "dot.hpp"
#include "ukernels.h"

void DotOp::initRandom() {

  assert(M >= 16 && M % 16 == 0 && "M mod 16 failed");
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(-10, 10);

  for (size_t i = 0; i < M; i++) {
    A.push_back(dis(gen));
    B.push_back(dis(gen));
  }
}

pair<float, float> DotOp::getResult() {
  return pair<float, float>(base_res, vec_res);
}

void DotOp::printPerformance() {
  cout << "[Performance]\tBaseline: " << performance.base_duration
       << "s\tVectorized: " << performance.vector_duration
       << "s\tSpeedup: " << fixed << setprecision(2)
       << performance.base_duration / performance.vector_duration << endl;
}
void DotOp::printResult() {
  cout << "[Result]\tBaseline: " << scientific << setprecision(4) << base_res
       << "\tVectorized: " << scientific << setprecision(4) << vec_res << "\tDelta: " << fixed
       << setprecision(3) << fabs(base_res - vec_res) << endl;
}

void DotOp::baseline() {
  double total_t = 0;
  float res;
  for (size_t it = 0; it < iter; it++) {
    res = 0.0;
    auto s = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < M; i++)
      res += A[i] * B[i];
    auto e = chrono::high_resolution_clock::now();
    total_t += chrono::duration<double>(e - s).count();
  }
  base_res = res;                             // result of the last iteration
  performance.base_duration = total_t / iter; // average time
}

void DotOp::vectorized() {
  const float *a_ptr = A.data(); // &A[0]
  const float *b_ptr = B.data();

  double total_t = 0;
  float res;
  for (size_t it = 0; it < iter; it++) {
    res = 0.0;
    auto s = chrono::high_resolution_clock::now();
    _avx512_dot_vec_acc_single_reduce(a_ptr, b_ptr, res, M);
    auto e = chrono::high_resolution_clock::now();
    total_t += chrono::duration<double>(e - s).count();
  }
  vec_res = res;
  performance.vector_duration = total_t / iter;
}
