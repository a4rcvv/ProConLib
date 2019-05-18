#include <algorithm>
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

uint64_t GetCombination(uint_fast64_t, uint_fast64_t);

uint64_t GetPermutation(uint_fast16_t, uint_fast16_t);
uint64_t GetFactorial(uint_fast16_t);

uint64_t GetCombination(uint_fast64_t n, uint_fast64_t r) {
  if (n < r) {
    // error
    return 0;
  }

  if (n / 2 < r) {
    r = n - r;
  }

  if (r == 0) return 1;
  return GetCombination(n - 1, r - 1) + GetCombination(n - 1, r);
}

uint64_t GetPermutation(uint_fast16_t n, uint_fast16_t r) {
  if (n < r) {
    // error
    return 0;
  }
  uint64_t result = 1;
  for (uint_fast16_t i = n; i > n - r; i--) {
    result *= i;
  }
  return result;
}

uint64_t GetFactorial(uint_fast16_t n) {
  uint64_t result = 1;
  for (uint_fast16_t i = 1; i <= n; i++) {
    result *= i;
  }
  return result;
}

// int main(void) {
//   for (int i = 1; i < 10; i++) {
//     for (int j = 1; j < 10; j++) {
//       cout << GetCombination(i, j) << " ";
//     }
//     cout << endl;
//   }
//   return 0;
// }
