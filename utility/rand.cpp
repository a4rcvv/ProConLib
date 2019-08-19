#include <algorithm>
#include <cstdio>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

// Make integral number. Range is [min, max].
// Note: When you use this class, you should include <random>. If there is an
// error, check it!
class RandomIntNumber {
  std::mt19937_64 mt_maker_;
  std::uniform_int_distribution<int64_t> range_maker_;

 public:
  RandomIntNumber(int64_t min, int64_t max) {
    std::random_device seed_maker;
    mt_maker_.seed(seed_maker());
    // range_maker_.min = min;
    // range_maker_.max = max;
    std::uniform_int_distribution<int64_t>::param_type param(min, max);
    range_maker_.param(param);
  }
  int64_t Make(void) {
    return range_maker_(mt_maker_);
  }
  int64_t operator()(void) {
    return Make();
  }
};

// Make real number. Range is [min,max).
// Note: When you use this class, you should include <random>. If there is an
// error, check it!
class RandomRealNumber {
  std::mt19937_64 mt_maker_;
  std::uniform_real_distribution<double> range_maker_;

 public:
  RandomRealNumber(double min, double max) {
    std::random_device seed_maker;
    mt_maker_.seed(seed_maker());
    // range_maker_.min = min;
    // range_maker_.max = max;
    std::uniform_real_distribution<double>::param_type param(min, max);
    range_maker_.param(param);
  }

  double Make(void) {
    return range_maker_(mt_maker_);
  }
  double operator()(void) {
    return Make();
  }
};

// for verifying
// int main(void) {
//   cout << std::fixed << std::setprecision(10);
//   cin.tie(0);
//   std::ios::sync_with_stdio(false);
//   RandomIntNumber ri9(0, 9);
//   int count[10] = {};
//   for (int i = 0; i < 100000; i++) {
//     int temp = ri9();
//     // cout << temp << " ";
//     count[temp]++;
//   }
//   cout << endl << "Int" << endl;
//   for (int i = 0; i <= 9; i++) {
//     cout << i << "\t" << count[i] << endl;
//   }

//   RandomRealNumber rr10(0.0, 10.0);
//   int countreal[10] = {};
//   for (int i = 0; i < 100; i++) {
//     double temp = rr10();
//     cout << temp << " ";
//     countreal[(int)temp]++;
//   }
//   cout << endl << "Real" << endl;
//   for (int i = 0; i <= 9; i++) {
//     cout << i << "\t" << countreal[i] << endl;
//   }

//   return 0;
// }
