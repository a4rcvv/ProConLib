#include <algorithm>
#include <cstdio>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

// This class supports...
// * insert number to the array
// * erase number from the array
// * get the median of the array
class DynamicMedianArray {
  std::multiset<int64_t> left, right;

  int64_t _leftmax(void) {
    return *(--left.end());
  }
  int64_t _rightmin(void) {
    return *(right.begin());
  }

public:
  void insert(int64_t n);
  void erase(int64_t n);
  int64_t size(void) {
    return left.size() + right.size();
  }

  // if (the size of the array)==2n+1:
  //   return n+1th element
  // else:
  //   return nth element
  //   (strictly speaking, this is not the median)
  int64_t median_il(void) {
    return _leftmax();
  }

  // if (the size of the array)==2n+1:
  //   return n+1th element
  // else:
  //   return n+1th element
  //   (strictly speaking, this is not the median)
  int64_t median_ir(void) {
    if (size() % 2 == 1) {
      return _leftmax();
    } else {
      return _rightmin();
    }
  }

  // return the median(strictly)
  // note: this function's type is DOUBLE, not integer
  double median_f(void) {
    if (size() % 2 == 1) {
      return _leftmax();
    } else {
      return (_leftmax() + _rightmin()) / (double)2;
    }
  };
};

void DynamicMedianArray::insert(int64_t n) {
  if (size() % 2 == 1) {
    if (_rightmin() <= n) {
      right.insert(n);
    } else {
      right.insert(_leftmax());
      left.erase(_leftmax());
      left.insert(n);
    }
  } else {
    if (size() == 0 || n <= _leftmax()) {
      left.insert(n);
    } else {
      left.insert(_rightmin());
      right.erase(_rightmin());
      right.insert(n);
    }
  }
}

void DynamicMedianArray::erase(int64_t n) {
  if (left.find(n) != left.end()) {
    left.erase(n);
    if (size() % 2 == 1) {
      left.insert(_rightmin());
      right.erase(_rightmin());
    }
  } else {
    right.erase(n);
    if (size() % 2 == 0) {
      right.insert(_leftmax());
      left.erase(_leftmax());
    }
  }
}

