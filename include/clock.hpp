///
//    A simple header-only clock
//    Tharindu Patabandi <tharindu at protonmail dot com>
///

#ifndef _CLOCK_HPP
#define _CLOCK_HPP

#include <cassert>
#include <chrono>
#include <iostream>

class Clock {
private:
  std::chrono::high_resolution_clock::time_point start_t, end_t;
  bool _stopped;

public:
  Clock() { _stopped = false; }
  inline void start();
  inline void end();
  inline double duration();
};

void Clock::start() {
  start_t = std::chrono::high_resolution_clock::now();
  _stopped = false;
}

void Clock::end() {
  end_t = std::chrono::high_resolution_clock::now();
  _stopped = true;
}
double Clock::duration() {
  assert(_stopped && "[ERROR] clock is still ticking...");
  return std::chrono::duration<double>(end_t - start_t).count();
}

#endif