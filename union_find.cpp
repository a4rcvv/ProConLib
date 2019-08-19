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

// Manages Union-Find Forest.
class UnionFindForest {
  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> size_;

 public:
  // Initialize forest.
  // parent_[i]=i, rank_[i]=0, size_[i]=1.
  UnionFindForest(const int &n);
  // Get the number of the root of the node q.
  int Root(const int &q);
  // Return true if the roots of x and y is same.
  bool IsSame(const int &x, const int &y);
  // Unite the tree x and tree y.
  void Unite(int x, int y);
  // Get the number of nodes which are the same group as node q.
  int Size(const int &q);
};
UnionFindForest::UnionFindForest(const int &n) {
  parent_.resize(n);
  rank_.resize(n);
  size_.resize(n);
  for (int i = 0; i < n; i++) {
    parent_[i] = i;
    rank_[i]   = 0;
    size_[i]   = 1;
  }
}
int UnionFindForest::Size(const int &q) {
  return size_[Root(q)];
}

int UnionFindForest::Root(const int &q) {
  if (parent_[q] == q) {
    return q;
  } else {
    return parent_[q] = Root(parent_[q]);
  }
}

bool UnionFindForest::IsSame(const int &x, const int &y) {
  return Root(x) == Root(y);
}

void UnionFindForest::Unite(int x, int y) {
  x = Root(x);
  y = Root(y);
  if (x == y) return;
  if (rank_[x] < rank_[y]) {
    parent_[x] = y;
    size_[y] += size_[x];
    size_[x] = 0;

  } else {
    parent_[y] = x;
    size_[x] += size_[y];
    size_[y] = 0;
    if (rank_[x] == rank_[y]) rank_[x]++;
  }
}

// for verifying

// this code solves Disjoint Set: Union Find
// Tree(http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=jp)

// int main(void) {
//   int n, q;
//   cin >> n >> q;
//   UnionFindForest UF(n);
//   for (int i = 0; i < q; i++) {
//     int com, x, y;
//     cin >> com >> x >> y;
//     switch (com) {
//       case 0:
//         UF.Unite(x, y);
//         break;
//       case 1:
//         cout << UF.IsSame(x, y) << endl;
//         break;
//     }
//   }
// }
