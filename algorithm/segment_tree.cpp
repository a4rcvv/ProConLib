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

// see also: http://tsutaj.hatenablog.com/entry/2017/03/29/204841

template <typename Monoid> class SegmentTree {
private:
  int range_;
  Monoid identity_;
  std::vector<Monoid> tree_;

  virtual Monoid operate(const Monoid &a, const Monoid &b) = 0;

  Monoid internalOperate(const Monoid &a, const Monoid &b) {
    if (a == identity_) {
      return b;
    } else if (b == identity_) {
      return a;
    } else {
      return operate(a, b);
    }
  }

  int parent(const int child) const { return (child - 1) / 2; }

  int leftChild(const int parent) const { return parent * 2 + 1; }

  int rightChild(const int parent) const { return parent * 2 + 2; }

  Monoid getResult(int query_l, int query_r, int node, int l, int r) {
    if (r <= query_l || query_r <= l) {
      return identity_;
    } else if (query_l <= l && r <= query_r) {
      return tree_[node];
    } else {
      Monoid vl = getResult(query_l, query_r, leftChild(node), l, (l + r) / 2);
      Monoid vr = getResult(query_l, query_r, rightChild(node), (l + r) / 2, r);
      return internalOperate(vl, vr);
    }
  }

public:
  /// \brief construct the segment tree.
  /// \param identity the element e s.t. a*e = e*a = a  (単位元)
  /// \param v tree initializer
  SegmentTree(const Monoid &identity, const int size) : identity_(identity) {
    int sz = size;
    range_ = 1;
    while (range_ < sz) {
      range_ *= 2;
    }
    tree_.resize(2 * range_ - 1, identity);
  }

  /**
   * @brief Construct a new Segment Tree object
   *
   * @param identity 単位元
   * @param v 値の初期値
   */
  SegmentTree(const Monoid &identity, const std::vector<Monoid> &v)
      : SegmentTree(identity, v.size()) {
    init(v);
  }

  void init(const std::vector<Monoid> &v) {
    for (int i = 0; i < v.size(); i++) {
      tree_[i + range_ - 1] = v[i];
    }
    for (int i = range_ - 2; i >= 0; i--) {
      tree_[i] = internalOperate(tree_[leftChild(i)], tree_[rightChild(i)]);
    }
  }

  /// \brief set the value and refresh the tree
  /// \param pos position
  /// \param val value
  void set(int pos, const Monoid &val) {
    pos += (range_ - 1);

    tree_[pos] = val;
    while (pos > 0) {
      pos = parent(pos);
      tree_[pos] =
          internalOperate(tree_[leftChild(pos)], tree_[rightChild(pos)]);
    }
  }

  /// \brief [l,r)に対して演算をした結果を返す
  /// \param l 範囲左端(lを含む)
  /// \param r 範囲右端(rを含まない)
  /// \return result

  Monoid get(int l, int r) { return getResult(l, r, 0, 0, range_); }
};

// example of implementation

class RMQTree : public SegmentTree<int64_t> {
  int64_t operate(const int64_t &a, const int64_t &b) override {
    return std::min(a, b);
  }

public:
  RMQTree(const int64_t &identity, const int n) : SegmentTree(identity, n) {}
};

// example of using(TAKOYAKIOISIKUNA-RU)

// struct Info{
//   int64_t p;
//   double a,b;
//   Info(){}
//   Info(int64_t _p,double _a,double _b):p(_p),a(_a),b(_b){}
// };
//
// #include <unordered_map>
// #include <set>
//
//
//
// int main(void) {
//   cout << std::fixed << std::setprecision(10);
//   cin.tie(0);
//   std::ios::sync_with_stdio(false);
//
//   int64_t n,m;
//   cin>>n>>m;
//   std::unordered_map<int64_t,int64_t> compress_map;
//
//   std::vector<Info> info(m);
//   std::set<int64_t> p_set;
//   for(int i=0;i<m;i++){
//     int64_t p;
//     double a,b;
//     cin>>p>>a>>b;
//     info[i]=Info(p,a,b);
//     p_set.insert(p);
//   }
//   int n_compressed=p_set.size();
//   for(int i=0;i<n_compressed;i++){
//     compress_map[*p_set.begin()]=i;
//     p_set.erase(*p_set.begin());
//   }
//   for(auto& i:info){
//     i.p=compress_map[i.p];
//   }
//
//   SegmentTree<pair>
//   tree(std::make_pair(1,0),std::vector<pair>(n_compressed,std::make_pair(1,0)));
//   double min=1,max=1;
//   for(auto i:info){
//     tree.SetValue(i.p,std::make_pair(i.a,i.b));
//     pair result=tree.GetResult(0,n_compressed);
//     max=std::max(max,result.first+result.second);
//     min=std::min(min,result.first+result.second);
//   }
//
//   cout<<min<<endl;
//   cout<<max<<endl;
//
//
//
//
//   return 0;
// }
