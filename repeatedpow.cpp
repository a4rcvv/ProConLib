#include <algorithm>
#include <cmath>
#include <cstdio>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

class RepeatedPow {
  static const int MAX_EXPONENT = 64;
  std::vector<int64_t> memo;
  int prev_base = 0;

public:
  RepeatedPow(void) {
    memo.resize(MAX_EXPONENT + 1);
  }
  int64_t GetValue(int64_t base, int64_t exponent) {
    cerr << "\033[93m" << base << " " << exponent << "\033[m" << endl;
    if (base != prev_base) {
      prev_base = base;
      memo.clear();
      memo.resize(MAX_EXPONENT + 1);
    }
    if (base == 0) {
      return 0;
    } else if (exponent == 0) {
      return 0;
    } else if (exponent == 1) {
      memo[1] = base;
      return base;
    } else if (memo[exponent] != 0) {
      return memo[exponent];
    }
    int64_t floor       = exponent / 2;
    int64_t ceil        = exponent - floor;
    int64_t floor_value = GetValue(base, floor);
    int64_t ceil_value  = GetValue(base, ceil);
    int64_t result      = floor_value * ceil_value;
    memo[exponent]      = result;
    return result;
  }
};

// for verifying
// int main(void) {
//   cout << std::fixed << std::setprecision(10);
//   cin.tie(0);
//   std::ios::sync_with_stdio(false);

//   RepeatedPow p;
//   for (int i = 0; i < 10; i++) {
//     int b, e;
//     cin >> b >> e;
//     cout << p.GetValue(b, e) << endl;
//   }

//   return 0;
// }
