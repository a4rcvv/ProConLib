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

class DynamicMedianArray {
  std::multiset<int64_t> left, right;

  int64_t _leftmax(void) {
    return *(--left.end());
  }
  int64_t _rightmin(void) {
    if(right.empty()){
      return INT64_MIN;
    }
    auto itr=right.begin();
    if(itr==right.end()){
      return INT64_MIN;
    }else{
      return *(right.begin());
    }

  }

public:
  void insert(int64_t n);
  void erase(int64_t n);
  int64_t size(void) {
    return left.size() + right.size();
  }

  int64_t median_il(void) {
    return _leftmax();
  }

  int64_t median_ir(void) {
    if (size() % 2 == 1) {
      return _leftmax();
    } else {
      return _rightmin();
    }
  }

  lint median_f(void) {
    // if (size() % 2 == 1) {
    //   return _leftmax();
    // } else {
    //   return _rightmin();
    // }
    return _leftmax();
  };
};

void DynamicMedianArray::insert(int64_t n) {
  if (size() % 2 == 1) {
    if (_leftmax() <= n) {
      right.insert(n);
    } else {
      right.insert(_leftmax());
      left.erase(left.find(_leftmax()));
      left.insert(n);
    }
  } else {
    if (size() == 0 || n <= _rightmin()) {
      left.insert(n);
    } else {
      left.insert(_rightmin());
      right.erase(right.find(_rightmin()));
      right.insert(n);
    }
  }
}

void DynamicMedianArray::erase(int64_t n) {
  if (left.find(n) != left.end()) {
    left.erase(left.find(n));
    if (size() % 2 == 1) {
      left.insert(_rightmin());
      right.erase(right.find(_rightmin()));
    }
  } else {
    right.erase(right.find(n));
    if (size() % 2 == 0) {
      right.insert(_leftmax());
      left.erase(left.find(_leftmax()));
    }
  }
}

