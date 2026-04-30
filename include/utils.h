///
//    Utils
//    Tharindu Patabandi <tharindu at protonmail dot com>
///

// 32-bit types
template <class T> T ceil_pow_of_2(T n) {
  if (n == 0)
    return 1;
  n--;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  return n + 1;
}
