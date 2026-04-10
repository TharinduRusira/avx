///
//    Kernel variants
//    Tharindu Patabandi <tharindu at protonmail dot com>
///

#ifndef _AVX512UKERNEL_HPP
#define _AVX512UKERNEL_HPP

#include <immintrin.h>

void _avx512_dot_vec_acc_inner_reduce(const float *a_ptr, const float *b_ptr,
                                      float &vec_res, size_t M) {
  for (size_t i = 0; i < M; i += 16) {
    __m512 a_vec = _mm512_loadu_ps(
        a_ptr + i); // std::vector does not guarantee 64b alignment
    __m512 b_vec = _mm512_loadu_ps(b_ptr + i);
    __m512 c_vec = _mm512_setzero_ps();
    c_vec = _mm512_fmadd_ps(a_vec, b_vec, c_vec);
    vec_res += _mm512_reduce_add_ps(c_vec);
  }
}

void _avx512_dot_vec_acc_single_reduce(const float *a_ptr, const float *b_ptr,
                                       float &res, size_t M) {
  __m512 c_vec = _mm512_setzero_ps();

  for (size_t i = 0; i < M; i += 16) {
    __m512 a_vec = _mm512_loadu_ps(
        a_ptr + i); // std::vector does not guarantee 64b alignment
    __m512 b_vec = _mm512_loadu_ps(b_ptr + i);

    c_vec = _mm512_fmadd_ps(a_vec, b_vec, c_vec);
  }
  res = _mm512_reduce_add_ps(c_vec);
}

#endif