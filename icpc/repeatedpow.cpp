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

// return base^exponent (MOD. mod).
int64_t RepeatedPowMod(int64_t base, int64_t exponent, int64_t mod) {
  if (exponent == 0)
    return 1;
  else if (exponent % 2 == 0) {
    int64_t root = RepeatedPowMod(base, exponent / 2, mod);
    return (root * root) % mod;
  } else {
    return (base * RepeatedPowMod(base, exponent - 1, mod)) % mod;
  }
}

// return base^exponent.
// std::pow() is too slow, so if you want to calc (int)^(int), use this func.
int64_t RepeatedPow(int64_t base, int64_t exponent) {
  if (exponent == 0)
    return 1;
  else if (exponent % 2 == 0) {
    int64_t root = RepeatedPow(base, exponent / 2);
    return (root * root) % mod;
  } else {
    return (base * RepeatedPow(base, exponent - 1));
  }
}
