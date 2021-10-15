#include <algorithm>
#include <cstdint>
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

//参考: http://tsutaj.hatenablog.com/entry/2017/03/30/224339
// http://beet-aizu.hatenablog.com/entry/2017/12/01/225955

/**
 * @brief 遅延伝搬セグメント木の抽象クラス
 *
 * @tparam V 区間取得の値の型
 * @tparam O 操作を表す値の型
 */
template <typename V, typename O> class LazySegmentTree {
protected:
  int range_;
  V value_identity_;
  O operator_identity_;
  std::vector<V> value;
  std::vector<O> lazy;

  /**
   * @brief 子ノード2つをマージして親ノードのValueを求める
   *
   * @param a 子ノードの値
   * @param b 子ノードの値
   * @return V 親ノードの値
   */
  virtual V mergeValue(const V &a, const V &b) = 0;
  /**
   * @brief targetにeffectorの操作を加えて，新たなOperatorを求める
   *
   * @param target 既存のOperator
   * @param effector 新たに加わるOperator
   * @return O effectorを反映させたあとのOperator
   */
  virtual O mergeOperator(const O &target, const O &effector) = 0;

  /**
   * @brief valにoplを作用させた結果を返す
   *
   * @param val 値
   * @param opl 演算
   * @param n 区間長
   * @return V 演算が作用されたあとの値
   */
  virtual V operate(const V &val, const O &opl, int n) = 0;

  V internalMerge(const V &a, const V &b) {
    if (a == value_identity_) {
      return b;
    } else if (b == value_identity_) {
      return a;
    } else {
      return mergeValue(a, b);
    }
  }

  int parent(const int child) const { return (child - 1) / 2; }

  int leftChild(const int parent) const { return parent * 2 + 1; }

  int rightChild(const int parent) const { return parent * 2 + 2; }

  /**
   * @brief nodeの遅延評価を実行し，子ノードに伝播させる
   *
   * @param node ノード番号
   * @param len そのノードが管理する区間の長さ
   */
  void propagate(int node, int len) {
    if (lazy[node] != operator_identity_) {
      if (node * 2 + 2 < range_ * 2) {
        lazy[leftChild(node)] =
            mergeOperator(lazy[leftChild(node)], lazy[node]);
        lazy[rightChild(node)] =
            mergeOperator(lazy[rightChild(node)], lazy[node]);
      }

      value[node] = operate(value[node], lazy[node], len);
      lazy[node] = operator_identity_;
    }
  }

  /**
   * @brief 範囲取得クエリを実行
   *
   * @param query_l 取得区間左端
   * @param query_r 取得区間右端(半開区間に注意)
   * @param node 今見ているノード
   * @param l 対象のノードの区間左端
   * @param r 対象のノードの区間右端(半開区間に注意)
   * @return V 範囲取得の結果
   */
  V getRange(int query_l, int query_r, int node, int l, int r) {
    propagate(node, r - l);
    if (r <= query_l || query_r <= l) {
      return value_identity_;
    } else if (query_l <= l && r <= query_r) {
      return value[node];
    } else {
      V vl = getRange(query_l, query_r, leftChild(node), l, (l + r) / 2);
      V vr = getRange(query_l, query_r, rightChild(node), (l + r) / 2, r);
      return internalMerge(vl, vr);
    }
  }

  /**
   * @brief 範囲演算を実行
   *
   * @param a 演算区間左端
   * @param b 演算区間右端(半開区間に注意)
   * @param opr 演算
   * @param node 見ているノード
   * @param l 対象のノードの区間左端
   * @param r 対象のノードの区間右端(半開区間に注意)
   * @return V 範囲演算の結果
   */
  V update(int a, int b, O opr, int node, int l, int r) {
    propagate(node, r - l);
    if (r <= a || b <= l) // [a,b)が[l,r)に全く含まれていない場合
      return value[node];
    if (a <= l && r <= b) { // a,b)が[l,r)に完全に含まれている場合
      lazy[node] = mergeOperator(lazy[node], opr);
      propagate(node, r - l);
      return operate(value[node], lazy[node], r - l);
    } else {
      update(a, b, opr, leftChild(node), l, (l + r) / 2);
      update(a, b, opr, rightChild(node), (l + r) / 2, r);
      value[node] =
          internalMerge(value[leftChild(node)], value[rightChild(node)]);
      return value[node];
    }
  }

public:
  /**
   * @brief vでセグ木を初期化する
   *
   * @param v 初期状態の値の配列
   */
  void init(const std::vector<V> &v) {
    for (int i = 0; i < v.size(); i++) {
      value[i + range_ - 1] = v[i];
    }
    for (int i = range_ - 2; i >= 0; i--) {
      value[i] = internalMerge(value[leftChild(i)], value[rightChild(i)]);
    }
  }

  /**
   * @brief [l, r) に対して演算を行う
   *
   * @param l 半開区間左端
   * @param r 半開区間右端
   * @param opr 演算の値
   */
  void update(int l, int r, O opr) { update(l, r, opr, 0, 0, range_); }

  /**
   * @brief [l, r)に対して範囲取得する
   *
   * @param l 半開区間左端
   * @param r 半開区間右端
   * @return V 範囲取得の結果
   */

  V get(int l, int r) { return getRange(l, r, 0, 0, range_); }

  /**
   * @brief Construct a new Lazy Segment Tree object
   *
   * @param value_identity 値の単位元
   * @param operator_identity 演算の単位元
   * @param size セグ木の大きさ
   */
  LazySegmentTree(const V &value_identity, const O &operator_identity, int size)
      : value_identity_(value_identity), operator_identity_(operator_identity) {
    int sz = size;
    range_ = 1;
    while (range_ < sz) {
      range_ *= 2;
    }
    value.resize(2 * range_ - 1, value_identity);
    lazy.resize(2 * range_ - 1, operator_identity);
  }

  /**
   * @brief Construct a new Lazy Segment Tree object
   *
   * @param value_identity 値の単位元
   * @param operator_identity 演算の単位元
   * @param v 値の初期値
   */
  LazySegmentTree(const V &value_identity, const O &operator_identity,
                  const std::vector<V> &v)
      : LazySegmentTree(value_identity, operator_identity, v.size()) {
    init(v);
  }
};

// verify
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I
// 区間変更、区間sum取得に対応
//
class RSQTree : public LazySegmentTree<int64_t, int64_t> {
protected:
  int64_t mergeValue(const int64_t &a, const int64_t &b) override {
    return a + b;
  }
  int64_t mergeOperator(const int64_t &target,
                        const int64_t &effector) override {
    if (effector == operator_identity_) {
      return target;
    } else {
      return effector;
    }
  }
  int64_t operate(const int64_t &val, const int64_t &opl, int n) override {
    if (opl == operator_identity_) {
      return val;
    } else {
      return opl*n;
    }
  }

public:
  RSQTree(int64_t n) : LazySegmentTree(0, INT64_MAX, n) {}
};

int main(void) {
  int64_t n, q;
  cin >> n >> q;
  RSQTree tree(n + 1);
  tree.init(std::vector<int64_t>(n, 0));
  for (int64_t i = 0; i < q; i++) {
    int64_t m;
    cin >> m;
    if (m == 0) {
      int64_t s, t, x;
      cin >> s >> t >> x;
      tree.update(s, t + 1, x);
    } else {
      int64_t s, t;
      cin >> s >> t;
      cout << tree.get(s, t + 1) << endl;
    }
  }
}
