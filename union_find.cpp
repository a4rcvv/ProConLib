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
  std::vector<int> parent;
  std::vector<int> rank;

 public:
  // Initialize forest.
  // parent[i]=i, rank[i]=0.
  UnionFindForest(int n);
  // Get the number of the root of the node q.
  int Root(int q);
  // Return true if the roots of x and y is same.
  bool is_same(int x, int y);
  // Unite the tree x and tree y.
  void Unite(int x, int y);
};
UnionFindForest::UnionFindForest(int n) {
  for (int i = 0; i < n; i++) {
    parent.push_back(i);
    rank.push_back(0);
  }
}
int UnionFindForest::Root(int q) {
  if (parent[q] == q) {
    return q;
  } else {
    return parent[q] = Root(parent[q]);
  }
}

bool UnionFindForest::is_same(int x, int y) {
  return Root(x) == Root(y);
}

void UnionFindForest::Unite(int x, int y) {
  x = Root(x);
  y = Root(y);
  if (x == y) return;
  if (rank[x] < rank[y]) {
    parent[x] = y;
  } else {
    parent[y] = x;
    if (rank[x] == rank[y]) rank[x]++;
  }
}

// for verifying

// this code solves Disjoint Set: Union Find
// Tree(http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=jp)

int main(void) {
  int n, q;
  cin >> n >> q;
  UnionFindForest UF(n);
  for (int i = 0; i < q; i++) {
    int com, x, y;
    cin >> com >> x >> y;
    switch (com) {
      case 0:
        UF.Unite(x, y);
        break;
      case 1:
        cout << UF.is_same(x, y) << endl;
        break;
    }
  }
}
