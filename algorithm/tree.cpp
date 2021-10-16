#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

// https://ei1333.hateblo.jp/entry/2018/12/21/004022

using namespace std;

template <typename EdgeData, typename T> class TreeDP {
protected:
  struct Edge {
    int to, rev;
    EdgeData data;
  };

  // 子と子をマージして親の値を求める関数
  virtual T f1(T a, T b) = 0;
  // 子と親への辺をマージして親の値を求める関数
  virtual T f2(T a, EdgeData d) = 0;

  vector<vector<Edge>> g;
  vector<vector<T>> ldp, rdp;
  vector<int> lptr, rptr;
  const T identity;

  // idxの子の値をマージした値を求める
  T dfs(int idx, int par) {

    while (lptr[idx] != par && lptr[idx] < g[idx].size()) {
      auto &e = g[idx][lptr[idx]];
      ldp[idx][lptr[idx] + 1] =
          f1(ldp[idx][lptr[idx]], f2(dfs(e.to, e.rev), e.data));
      ++lptr[idx];
    }
    while (rptr[idx] != par && rptr[idx] >= 0) {
      auto &e = g[idx][rptr[idx]];
      rdp[idx][rptr[idx]] =
          f1(rdp[idx][rptr[idx] + 1], f2(dfs(e.to, e.rev), e.data));
      --rptr[idx];
    }
    if (par < 0)
      return rdp[idx][0];
    return f1(ldp[idx][par], rdp[idx][par + 1]);
  }

public:
  TreeDP(int n, const T &ident)
      : g(n), ldp(n), rdp(n), lptr(n), rptr(n), identity(ident) {}

  void addEdge(int u, int v, const EdgeData &d) {
    g[u].emplace_back((Edge){v, (int)g[v].size(), d});
    g[v].emplace_back((Edge){u, (int)g[u].size() - 1, d});
  }

  vector<T> solve() {
    for (int i = 0; i < g.size(); i++) {
      ldp[i].assign(g[i].size() + 1, identity);
      rdp[i].assign(g[i].size() + 1, identity);
      lptr[i] = 0;
      rptr[i] = (int)g[i].size() - 1;
    }
    vector<T> ret;
    for (int i = 0; i < g.size(); i++) {
      ret.push_back(dfs(i, -1));
    }
    return ret;
  }
};

// verify

using P = pair<int, int>;
const int INF = INT32_MAX;

class Tree : public TreeDP<int, P> {
  pair<int, int> f1(pair<int, int> a, pair<int, int> b) override {
    vector<int> v{a.first, a.second, b.first, b.second};
    sort(v.begin(), v.end(), greater<>());
    return {v[0], v[1]};
  }
  pair<int, int> f2(pair<int, int> a, int d) override {
    return {max(0, a.first) + d, -INF};
  }

public:
  Tree(int n) : TreeDP(n, {-INF, -INF}) {}
};

int main() {
  int n;
  cin >> n;
  if (n == 1) {
    cout << 0 << endl;
    return 0;
  }

  Tree tree(n);
  for (int i = 0; i < n - 1; i++) {
    int s, t, w;
    cin >> s >> t >> w;
    tree.addEdge(s, t, w);
  }

  int ret = 0;
  vector<P> res = tree.solve();
  for (auto p : res) {
    ret = max(ret, p.first);
    ret = max(ret, p.first+p.second);
  }
  cout << ret << endl;
  return 0;
}