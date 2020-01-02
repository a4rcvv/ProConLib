#include <algorithm>
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

// Manages Weighted Union-Find Forest.
class WeightedUnionFindForest {
  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> size_;
  std::vector<int> weight_;

 public:
  // Initialize forest.
  // parent_[i]=i, rank_[i]=0, size_[i]=1, weight_[i]=0.
  WeightedUnionFindForest(const int &n);
  // Get the number of the root of the node q.
  int Root(const int &q);
  // Return true if the roots of x and y is same.
  bool IsSame(const int &x, const int &y);
  // Unite the tree x and tree y(weight is w).
  // If x and y already have been united, return false.
  // Weight(y)-Weight(x)=w
  bool Unite(int x, int y, int w);
  // Get the number of nodes which are the same group as node q.
  int Size(const int &q);
  // Get the weight of node q.
  int Weight(const int &q);
  // Get the weights' difference of node x and y(Weight(y)-Weight(x)).
  int Diff(const int &x, const int &y);
};

WeightedUnionFindForest::WeightedUnionFindForest(const int &n) {
  parent_.resize(n);
  rank_.resize(n);
  size_.resize(n);
  weight_.resize(n);
  for (int i = 0; i < n; i++) {
    parent_[i] = i;
    rank_[i]   = 0;
    size_[i]   = 1;
    weight_[i] = 0;
  }
}
int WeightedUnionFindForest::Size(const int &q) {
  return size_[Root(q)];
}
int WeightedUnionFindForest::Root(const int &q) {
  if (parent_[q] == q) {
    return q;
  } else {
    const int r = Root(parent_[q]);
    weight_[q] += weight_[parent_[q]];
    return parent_[q] = r;
  }
}

bool WeightedUnionFindForest::IsSame(const int &x, const int &y) {
  return Root(x) == Root(y);
}

int WeightedUnionFindForest::Weight(const int &q) {
  Root(q);  // compress path
  return weight_[q];
}
int WeightedUnionFindForest::Diff(const int &x, const int &y) {
  if (Root(x) != Root(y)) {
    cerr << "WeightedUnionFindForest: Error" << endl;
    cerr << "Roots of node x and y aren't same" << endl;
    return INT32_MAX;
  }
  return Weight(y) - Weight(x);
}

bool WeightedUnionFindForest::Unite(int x, int y, int w) {
  w += Weight(x);
  w -= Weight(y);
  x = Root(x);
  y = Root(y);

  if (x == y) return false;
  if (rank_[x] < rank_[y]) {
    weight_[x] = w * (-1);
    parent_[x] = y;
    size_[y] += size_[x];
    size_[x] = 0;

  } else {
    weight_[y] = w;
    parent_[y] = x;
    size_[x] += size_[y];
    size_[y] = 0;
    if (rank_[x] == rank_[y]) rank_[x]++;
  }
  return true;
}