# DotOp on AVX512

Benchmark various implementations of vectorized DotOp against vanilla (scalar) implementation on Intel AVX512.

## Build

```bash
mkdir build
cmake ..
cmake --build .
./runner
```