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

// template for "Meguru's Binary Search".
uint64_t BinarySearch(int key, std::vector<int> target) {
  int ng = -1;
  int ok = (int)target.size();
  while (abs(ok - ng) > 1) {
    int mid = (ok + ng) / 2;
    if (target[mid] >= key) {
      ok = mid;
    } else {
      ng = mid;
    }
  }
  return ok;
}

int main(void) {
  cout << std::fixed << std::setprecision(10);
  cin.tie(0);
  std::ios::sync_with_stdio(false);

  return 0;
}
