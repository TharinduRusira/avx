///
//    Test driver
//    Tharindu Patabandi <tharindu at protonmail dot com>
///

#include "dot.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {

  vector<int> sizes = {16, 32, 48, 64, 128, 256, 512, 1024, 2048};

  for (int len : sizes) {
  DotOp op(len);
    op.baseline();
    op.vectorized();

    op.printResult();
    op.printPerformance();
  }
  return 0;
}