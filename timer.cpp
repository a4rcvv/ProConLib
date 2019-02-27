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

// // for verifying

// int64_t fib(int n) {
//   if (n == 0) return 0;
//   if (n == 1) return 1;
//   return fib(n - 1) + fib(n - 2);
// }

// int main(void) {
//   cout << std::fixed << std::setprecision(10);
//   cin.tie(0);
//   std::ios::sync_with_stdio(false);

//   Timer timer1, timer2;
//   for (int i = 0; i < 42; i++) {
//     cout << fib(i) << " ";
//   }
//   cout << endl;
//   cout << timer1.LapTime_millisec() << " " << timer2.LapTime_millisec() <<
//   endl; cout << timer1.LapTime_sec() << " " << timer2.LapTime_sec() << endl;
//   cout << "restart timer 1" << endl;
//   timer1.restart();
//   for (int i = 42; i < 45; i++) {
//     cout << fib(i) << " ";
//   }
//   cout << endl;
//   cout << timer1.LapTime_millisec() << " " << timer2.LapTime_millisec() <<
//   endl; cout << timer1.LapTime_sec() << " " << timer2.LapTime_sec() << endl;

//   return 0;
// }
