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




//参考: http://tsutaj.hatenablog.com/entry/2017/03/30/224339
//http://beet-aizu.hatenablog.com/entry/2017/12/01/225955


template<typename VM,typename OM>
class LazySegmentTree{
protected:
  int                 range_;
  VM              value_identity_;
  OM              operator_identity_;
  std::vector<VM> value_tree_;
  std::vector<OM> lazy_tree_;
  //直接実装したほうがよさそう
  virtual VM MergeValue(const VM& a, const VM& b)=0;
  virtual OM MergeOperator(const OM& target,const OM& effector)=0;
  virtual VM Operate(const VM& val, const OM& opl)=0;
  virtual OM GetOperator(const OM& opl, const int n)=0;
  VM InternalMerge(const VM& a, const VM& b){
    if(a==value_identity_){
      return b;
    }else if(b==value_identity_){
      return a;
    }else{
      return MergeValue(a,b);
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
  void Propagate(int node,int len){
    if(lazy_tree_[node]!=operator_identity_){
      if(node*2+2<range_*2){
        lazy_tree_[LeftChild(node)]=MergeOperator(lazy_tree_[LeftChild(node)],lazy_tree_[node]);
        lazy_tree_[RightChild(node)]=MergeOperator(lazy_tree_[RightChild(node)],lazy_tree_[node]);
      }
      value_tree_[node]=Operate(value_tree_[node],GetOperator(lazy_tree_[node],len));
      lazy_tree_[node]=operator_identity_;
    }
  }
  VM GetRangeOperation(int query_l, int query_r, int node, int l, int r){
    Propagate(node,r-l);
    if(r <= query_l || query_r <= l){
      return value_identity_;
    }else if(query_l <= l && r <= query_r){
      return value_tree_[node];
    }else{
      VM vl = GetRangeOperation(query_l, query_r, LeftChild(node), l,
                                    (l + r) / 2);
      VM vr = GetRangeOperation(query_l, query_r, RightChild(node),
                                    (l + r) / 2, r);
      return InternalMerge(vl, vr);
    }
  }
  VM Update(int a,int b, OM opr,int node,int l,int r){
    Propagate(node, r - l);
    if(r <= a || b <= l) return value_tree_[node];
    if(a <= l && r <= b){
      lazy_tree_[node] = MergeOperator(lazy_tree_[node],opr);
      Propagate(node, r - l);
      return Operate(value_tree_[node],GetOperator(lazy_tree_[node],r-l));
    }else{
      Update(a, b, opr, LeftChild(node), l, (l + r) / 2);
      Update(a, b, opr, RightChild(node), (l + r) / 2, r);
      value_tree_[node]= InternalMerge(value_tree_[LeftChild(node)],
                                       value_tree_[RightChild(node)]);
      return value_tree_[node];
    }
  }

public:
  /// \brief construct the segment tree.
  /// \param identity the element e s.t. a*e = e*a = a  (単位元)
  LazySegmentTree(const VM& value_identity, const OM& operator_identity,
      int size): value_identity_(
      value_identity),operator_identity_(operator_identity){
    int sz = size;
    range_ = 1;
    while(range_ < sz){
      range_ *= 2;
    }
    value_tree_.resize(2 * range_ - 1, value_identity);
    lazy_tree_.resize(2*range_-1,operator_identity);
  }
  void Init(const std::vector<VM>& v){
    for(int i = 0; i < v.size(); i++){
      value_tree_[i + range_ - 1] = v[i];
    }
    for(int i = range_ - 2; i >= 0; i--){
      value_tree_[i] =
          InternalMerge(value_tree_[LeftChild(i)], value_tree_[RightChild(i)]);
    }
  }
  void Update(int a,int b, OM opr){
    Update(a,b,opr,0,0,range_);
  }
  /// \brief [l,r)に対して演算をした結果を返す
  /// \param l 範囲左端(lを含む)
  /// \param r 範囲右端(rを含まない)
  /// \return result
  VM GetResult(int l, int r){
    return GetRangeOperation(l, r, 0, 0, range_);
  }
};

