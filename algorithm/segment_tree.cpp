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

template<typename Monoid>
Monoid Operate(const Monoid& a, const Monoid& b, const Monoid& identity){

  if(a == identity){
    return b;
  }else if(b == identity){
    return a;
  }else{
    // operation
  }
}

//example of implementation

// template < >
// int64_t Operate<int64_t>(const int64_t& a, const int64_t& b){
//   return std::min(a,b);
// }


//see also: http://tsutaj.hatenablog.com/entry/2017/03/29/204841

template<typename Monoid>
class SegmentTree{
private:
  int                 range_;
  Monoid              identity_;
  std::vector<Monoid> tree_;

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
  //FIXME: コンストラクタ中で仮想関数を使わないようにする
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



//example of using(TAKOYAKIOISIKUNA-RU)

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
//   SegmentTree<pair> tree(std::make_pair(1,0),std::vector<pair>(n_compressed,std::make_pair(1,0)));
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

// example of using(RMQ)

template<typename VM,typename OM>
class LazySegmentTree{
protected:
  int                 range_;
  VM              value_identity_;
  OM              operator_identity_;
  std::vector<VM> value_tree_;
  std::vector<OM> lazy_tree_;

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
  //FIXME: コンストラクタ中で仮想関数を使わないようにする
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

int main(void){
  cout << std::fixed << std::setprecision(10);
  cin.tie(0);
  std::ios::sync_with_stdio(false);

  int n, q;
  cin >> n >> q;
  const int64_t        INF = INT32_MAX;
  RMQTree tree(INF, n);
  tree.Init(std::vector<int64_t>(n,INT32_MAX));
  for(int              i   = 0; i < q; i++){
    int command, x, y;
    cin >> command >> x >> y;

    switch(command){
      case 0:tree.SetValue(x, y);
        // tree.OutputTree();
        break;
      case 1:cout << tree.GetResult(x, y + 1) << endl;
        break;
    }
  }

  return 0;
}



