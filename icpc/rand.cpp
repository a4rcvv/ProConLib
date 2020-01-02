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
