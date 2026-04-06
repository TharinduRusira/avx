///
//    Compute vector dot using AVX-512
//    Tharindu Patabandi <tharindu at protonmail dot com>
///

#include "dot.hpp"

void DotOp::initRandom() {

  assert(M >= 16 && M % 16 == 0 && "M mod 16 failed");
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(-100, 100);

  for (size_t i = 0; i < M; i++) {
    A.push_back(dis(gen));
    B.push_back(dis(gen));
  }
}

pair<float, float> DotOp::getResult() {
  return pair<float, float>(base_res, vec_res);
}

void DotOp::printPerformance() {
  cout << "Baseline: " << performance.base_duration
       << "s\tVectorized: " << performance.vector_duration
       << "s\tSpeedup: " << fixed << setprecision(2)
       << performance.base_duration / performance.vector_duration << endl;
}
void DotOp::printResult() {
  // assert(fabs(base_res - vec_res) < 1e-3 &&
  //        "Baseline/Vectorized result mismatch");
  cout << "Baseline: " << base_res << "\tVectorized: " << vec_res << "\tfabs: " << fixed << setprecision(3) << fabs(base_res - vec_res) << endl;
}

void DotOp::baseline() {
  auto s = chrono::high_resolution_clock::now();

  for (size_t i = 0; i < M; i++)
    base_res += A[i] * B[i];

  auto e = chrono::high_resolution_clock::now();
  performance.base_duration = chrono::duration<double>(e - s).count();
}

void DotOp::vectorized_1() {
  const float *a_ptr = A.data(); // &A[0]
  const float *b_ptr = B.data();

  auto s = chrono::high_resolution_clock::now();

  for (size_t i = 0; i < M; i += 16) {
    __m512 a_vec = _mm512_loadu_ps(
        a_ptr + i); // std::vector does not guarantee 64b alignment
    __m512 b_vec = _mm512_loadu_ps(b_ptr + i);
    __m512 c_vec = _mm512_setzero_ps();

    c_vec = _mm512_fmadd_ps(a_vec, b_vec, c_vec);
    vec_res += _mm512_reduce_add_ps(c_vec);
  }

  auto e = chrono::high_resolution_clock::now();
  performance.vector_duration = chrono::duration<double>(e - s).count();
}

void DotOp::vectorized() {
  const float *a_ptr = A.data(); // &A[0]
  const float *b_ptr = B.data();

  auto s = chrono::high_resolution_clock::now();
  __m512 c_vec = _mm512_setzero_ps();

  for (size_t i = 0; i < M; i += 16) {
    __m512 a_vec = _mm512_loadu_ps(
        a_ptr + i); // std::vector does not guarantee 64b alignment
    __m512 b_vec = _mm512_loadu_ps(b_ptr + i);

    c_vec = _mm512_fmadd_ps(a_vec, b_vec, c_vec);
  }
  vec_res += _mm512_reduce_add_ps(c_vec);


  auto e = chrono::high_resolution_clock::now();
  performance.vector_duration = chrono::duration<double>(e - s).count();
}
