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


//see also: http://tsutaj.hatenablog.com/entry/2017/03/29/204841

template<typename Monoid>
class SegmentTree{
private:
  int                 range_;
  Monoid              identity_;
  std::vector<Monoid> tree_;

  //直接実装したほうがよさそう
  virtual Monoid Operate(const Monoid& a, const Monoid& b)=0;

  Monoid InternalOperate(const Monoid& a, const Monoid& b){
    if(a==identity_){
      return b;
    }else if(b==identity_){
      return a;
    }else{
      return Operate(a,b);
    }
  }

  int Parent(const int child) const{
    return (child - 1) / 2;
  }

  int LeftChild(const int parent) const{
    return parent * 2 + 1;
  }

  int RightChild(const int parent) const{
    return parent * 2 + 2;
  }

  Monoid GetResult(int query_l, int query_r, int node, int l, int r){
    if(r <= query_l || query_r <= l){
      return identity_;
    }else if(query_l <= l && r <= query_r){
      return tree_[node];
    }else{
      Monoid vl = GetResult(query_l, query_r, LeftChild(node), l,
                            (l + r) / 2);
      Monoid vr = GetResult(query_l, query_r, RightChild(node),
                            (l + r) / 2, r);
      return InternalOperate(vl, vr);
    }

  }

public:

  /// \brief construct the segment tree.
  /// \param identity the element e s.t. a*e = e*a = a  (単位元)
  /// \param v tree initializer
  SegmentTree(const Monoid& identity, const int size): identity_(
      identity){
    int sz = size;
    range_ = 1;
    while(range_ < sz){
      range_ *= 2;
    }
    tree_.resize(2 * range_ - 1, identity);

  }

  void Init(const std::vector<Monoid>& v){
    for(int i = 0; i < v.size(); i++){
      tree_[i + range_ - 1] = v[i];
    }
    for(int i = range_ - 2; i >= 0; i--){
      tree_[i] = InternalOperate(tree_[LeftChild(i)], tree_[RightChild(i)]);
    }
  }

  /// \brief set the value and refresh the tree
  /// \param pos position
  /// \param val value
  void SetValue(int pos, const Monoid& val){
    pos += (range_ - 1);

    tree_[pos] = val;
    while(pos > 0){
      pos = Parent(pos);
      tree_[pos] =
          InternalOperate(tree_[LeftChild(pos)], tree_[RightChild(pos)]);
    }
  }

  /// \brief [l,r)に対して演算をした結果を返す
  /// \param l 範囲左端(lを含む)
  /// \param r 範囲右端(rを含まない)
  /// \return result

  Monoid GetResult(int l, int r){
    return GetResult(l, r, 0, 0, range_);
  }
};

// example of implementation

class RMQTree:public SegmentTree<int64_t>{
  int64_t Operate(const int64_t& a, const int64_t& b) override {
    return std::min(a,b);
  }
public:
  RMQTree(const int64_t& identity, const int n):SegmentTree(identity,n){}
};

