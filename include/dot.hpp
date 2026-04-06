///
//    Compute vector dot using AVX-512
//    Tharindu Patabandi <tharindu at protonmail dot com>
///

#ifndef _AVX512DOT_HPP
#define _AVX512DOT_HPP

#include <cassert>
#include <chrono>
#include <immintrin.h>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
struct Perf {
  double base_duration;
  double vector_duration;
};

class DotOp {
public:
  DotOp(size_t m) : M(m) { initRandom(); }
  void baseline();
  void vectorized();
void vectorized_1();

  pair<float, float> getResult();
  void printResult();
  void printPerformance();

private:
  size_t M;
  vector<float> A, B;
  float base_res = 0.0;
  float vec_res = 0.0;
  // populate A, B with random data
  void initRandom();
  Perf performance;

  // TODO: add iterations to performance collection
};

#endif
