#include <algorithm>
#include <chrono>
#include <cstdio>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

// Measure the time.
// Note: This class uses <chrono>. When you use and error is occurred, check
// whether you include it.
class Timer {
  std::chrono::system_clock::time_point start_time_;

 public:
  // restart the clock.
  void restart(void) {
    start_time_ = std::chrono::system_clock::now();
  }
  // When instantced, this timer restart itself automatically.
  Timer(void) {
    restart();
  }
  // Get the lap time(milliseconds).
  long long LapTime_millisec(void) {
    auto lap_time = std::chrono::system_clock::now();
    auto dur      = lap_time - start_time_;
    auto msec =
        std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    return msec;
  }
  // Get the lap time(seconds).
  long long LapTime_sec(void) {
    auto lap_time = std::chrono::system_clock::now();
    auto dur      = lap_time - start_time_;
    auto sec = std::chrono::duration_cast<std::chrono::seconds>(dur).count();
    return sec;
  }
};