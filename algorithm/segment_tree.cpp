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

  Monoid GetRangeOperation(int query_l, int query_r, int node, int l, int r){
    if(r <= query_l || query_r <= l){
      return identity_;
    }else if(query_l <= l && r <= query_r){
      return tree_[node];
    }else{
      Monoid vl = GetRangeOperation(query_l, query_r, LeftChild(node), l,
                                    (l + r) / 2);
      Monoid vr = GetRangeOperation(query_l, query_r, RightChild(node),
                                    (l + r) / 2, r);
      return InternalOperate(vl, vr);
    }

  }

public:

  /// \brief construct the segment tree.
  /// \param identity the element e s.t. a*e = e*a = a  (単位元)
  /// \param v tree initializer
  SegmentTree(const Monoid& identity, const std::vector<Monoid> v): identity_(
      identity){
    int sz = v.size();
    range_ = 1;
    while(range_ < sz){
      range_ *= 2;
    }
    tree_.resize(2 * range_ - 1, identity);
    for(int i = 0; i < sz; i++){
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

  Monoid GetRangeOperation(int l, int r){
    return GetRangeOperation(l, r, 0, 0, range_);
  }
};

// example of implementation

// class RMQTree:public SegmentTree<int64_t>{
//   int64_t Operate(const int64_t& a, const int64_t& b) override {
//     return std::min(a,b);
//   }
// public:
//   RMQTree(const int64_t& identity, const std::vector<int64_t> v):SegmentTree(identity,v){}
// };



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
//     pair result=tree.GetRangeOperation(0,n_compressed);
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

//example of using(RMQ)

// int main(void){
//   cout << std::fixed << std::setprecision(10);
//   cin.tie(0);
//   std::ios::sync_with_stdio(false);
//
//   int n, q;
//   cin >> n >> q;
//   const int64_t        INF = INT32_MAX;
//   RMQTree tree(INF, std::vector<int64_t>(n, INF));
//   for(int              i   = 0; i < q; i++){
//     int command, x, y;
//     cin >> command >> x >> y;
//
//     switch(command){
//       case 0:tree.SetValue(x, y);
//         // tree.OutputTree();
//         break;
//       case 1:cout << tree.GetRangeOperation(x, y + 1) << endl;
//         break;
//     }
//   }
//
//   return 0;
// }



