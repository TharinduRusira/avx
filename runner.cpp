///
//    Test driver
//    Tharindu Patabandi <tharindu at protonmail dot com>
///

#include "dot.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {

  vector<int> sizes = {16,    32,    48,     64,     128,    256,
                       512,   1024,  2048,   4096,   8192,   16384,
                       32768, 65536, 131072, 262144, 524288, 1048576};

  for (int len : sizes) {
    DotOp op(len);
    op.baseline();
    op.vectorized();

    cout << "Vector length: " << len << "\t"
         << "Memory: " << len * sizeof(float) * 2 << " bytes" << endl;
    op.printResult();
    op.printPerformance();
    cout << "---------------------------------------------" << endl;
  }
  return 0;
}