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
      return Operate(vl, vr, identity_);
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
      tree_[i] = Operate(tree_[LeftChild(i)], tree_[RightChild(i)], identity_);
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
          Operate(tree_[LeftChild(pos)], tree_[RightChild(pos)], identity_);
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
//   SegmentTree<int64_t> tree(INF, std::vector<int64_t>(n, INF));
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


// // This class is an obstacle class.
// // You have to inherit it and override Compare() and QueryCompare().
// template <typename T>
// class SegmentTree {
//  private:
//   // the size of original data.
//   int range_;
//   // initializer.
//   T initializer_;
//   // the data of SegTree. implemented as array.
//   std::vector<T> tree_;
//   // call Compare(int,int,int) recursively.
//   void Merge(const int &parent);
//   // return LeftChild's position from parent's position.
//   int LeftChild(const int &parent);
//   // RightChild version
//
//   int RightChild(const int &parent);
//   // return parent's position from left/right child's position.
//   int Parent(const int &child);
//
//   // The function which is used to answer a query internally.
//   T PrivateQuery(const int &query_left, const int &query_right, const int &node,
//                  const int &node_left, const int &node_right);
//
//   // Compare two query and return the result.
//   // This function is used to answer a query.
//   // You must override this function.
//   virtual T CompareQuery(const T &left, const T &right) = 0;
//   // Compare LeftChild and RightChild,and update parent.
//   // You must override this function.
//   virtual T Compare(const T &left, const T &right) = 0;
//
//  public:
//   // call Initialize().
//   SegmentTree(const int &n, const T &initializer);
//   // resize tree_ and initialize tree_ as initializer.
//   void Initialize(const int &n, const T &initializer);
//   // update pos and its parent, grandparent,
//   // great grangparent, great great grandparent, and more...
//   void Update(int pos, const T &data);
//   // Throw query and get answer.
//   // Range is [left,right).
//   T Query(const int &left, const int &right);
//   // output tree(for debugging).
//   void OutputTree(void);
// };
//
// template <typename T>
// int SegmentTree<T>::LeftChild(const int &parent) {
//   if (range_ == 1) return 0;
//   return parent * 2 + 1;
// }
// template <typename T>
// int SegmentTree<T>::RightChild(const int &parent) {
//   if (range_ == 1) return 0;
//   return parent * 2 + 2;
// }
// template <typename T>
// int SegmentTree<T>::Parent(const int &child) {
//   if (range_ == 1) return 0;
//   return (child - 1) / 2;
// }
//
// template <typename T>
// SegmentTree<T>::SegmentTree(const int &n, const T &initializer) {
//   Initialize(n, initializer);
// }
//
// template <typename T>
// void SegmentTree<T>::Initialize(const int &n, const T &initializer) {
//   int64_t temp = 1;
//   while (temp < n) temp *= 2;  //要素数を2のべき乗にするといいらしい
//   range_       = temp;
//   initializer_ = initializer;
//
//   tree_.resize(range_ * 2 - 1);
//   for (int i = 0; i < tree_.size(); i++) {
//     tree_[i] = initializer;
//   }
// }
//
// template <typename T>
// void SegmentTree<T>::Update(int pos, const T &data) {
//   pos += range_ - 1;
//   tree_[pos] = data;
//   Merge(Parent(pos));
// }
//
// template <typename T>
// void SegmentTree<T>::Merge(const int &parent) {
//   tree_[parent] = Compare(tree_[LeftChild(parent)], tree_[RightChild(parent)]);
//   if (parent > 0) Merge(Parent(parent));
// }
//
// template <typename T>
// T SegmentTree<T>::Query(const int &left, const int &right) {
//   return PrivateQuery(left, right, 0, 0, range_);
// }
// template <typename T>
// T SegmentTree<T>::PrivateQuery(const int &query_left, const int &query_right,
//                                const int &node, const int &node_left,
//                                const int &node_right) {
//   // cerr << query_left << "\t" << query_right << "\t" << node << "\t" <<
//   // node_left
//   //  << "\t" << node_right << endl;
//   if (query_left <= node_left && node_right <= query_right) {
//     // cerr << "return " << tree_[node] << endl;
//     return tree_[node];
//   }
//
//   else if (node_right <= query_left || query_right <= node_left) {
//     // cerr << "return " << initializer_ << endl;
//     return initializer_;
//   } else {
//     T temp_l = PrivateQuery(query_left, query_right, LeftChild(node), node_left,
//                             (node_left + node_right) / 2);
//     T temp_r = PrivateQuery(query_left, query_right, RightChild(node),
//                             (node_left + node_right) / 2, node_right);
//     return CompareQuery(temp_l, temp_r);
//   }
// }
//
// template <typename T>
// void SegmentTree<T>::OutputTree(void) {
//   cerr << "NodeNumber\tData" << endl;
//   for (int i = 0; i < tree_.size(); i++) {
//     cerr << i << "\t" << tree_[i] << endl;
//   }
// }
//
// // // for verifying
// // // This code solves AOJ Range Query - Range Minimum Query (RMQ).
// // class RMQTree : public SegmentTree<int> {
// //  private:
// //   int CompareQuery(const int &left, const int &right);
// //   int Compare(const int &left, const int &right);
//
// //  public:
// //   RMQTree(const int &n, const int &initializer) : SegmentTree(n,
// //   initializer){};
// // };
// // int RMQTree::CompareQuery(const int &left, const int &right) {
// //   if (left < right)
// //     return left;
// //   else
// //     return right;
// // }
// // int RMQTree::Compare(const int &left, const int &right) {
// //   if (left < right)
// //     return left;
// //   else
// //     return right;
// // }
//
// // int main(void) {
// //   cout << std::fixed << std::setprecision(10);
// //   cin.tie(0);
// //   std::ios::sync_with_stdio(false);
//
// //   int n, q;
// //   cin >> n >> q;
// //   RMQTree tree(n, INT32_MAX);
// //   // tree.OutputTree();
// //   for (int i = 0; i < q; i++) {
// //     int command, x, y;
// //     cin >> command >> x >> y;
//
// //     switch (command) {
// //       case 0:
// //         tree.Update(x, y);
// //         // tree.OutputTree();
// //         break;
// //       case 1:
// //         cout << tree.Query(x, y + 1) << endl;
// //         break;
// //     }
// //   }
//
// //   return 0;
// // }
