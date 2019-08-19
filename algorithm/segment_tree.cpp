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

// This class is an obstacle class.
// You have to inherit it and override Compare() and QueryCompare().
template <typename T>
class SegmentTree {
 private:
  // the size of original data.
  int range_;
  // initializer.
  T initializer_;
  // the data of SegTree. implemented as array.
  std::vector<T> tree_;
  // call Compare(int,int,int) recursively.
  void Merge(const int &parent);
  // return LeftChild's position from parent's position.
  int LeftChild(const int &parent);
  // RightChild version

  int RightChild(const int &parent);
  // return parent's position from left/right child's position.
  int Parent(const int &child);

  // The function which is used to answer a query internally.
  T PrivateQuery(const int &query_left, const int &query_right, const int &node,
                 const int &node_left, const int &node_right);

  // Compare two query and return the result.
  // This function is used to answer a query.
  // You must override this function.
  virtual T CompareQuery(const T &left, const T &right) = 0;
  // Compare LeftChild and RightChild,and update parent.
  // You must override this function.
  virtual T Compare(const T &left, const T &right) = 0;

 public:
  // call Initialize().
  SegmentTree(const int &n, const T &initializer);
  // resize tree_ and initialize tree_ as initializer.
  void Initialize(const int &n, const T &initializer);
  // update pos and its parent, grandparent,
  // great grangparent, great great grandparent, and more...
  void Update(int pos, const T &data);
  // Throw query and get answer.
  // Range is [left,right).
  T Query(const int &left, const int &right);
  // output tree(for debugging).
  void OutputTree(void);
};

template <typename T>
int SegmentTree<T>::LeftChild(const int &parent) {
  if (range_ == 1) return 0;
  return parent * 2 + 1;
}
template <typename T>
int SegmentTree<T>::RightChild(const int &parent) {
  if (range_ == 1) return 0;
  return parent * 2 + 2;
}
template <typename T>
int SegmentTree<T>::Parent(const int &child) {
  if (range_ == 1) return 0;
  return (child - 1) / 2;
}

template <typename T>
SegmentTree<T>::SegmentTree(const int &n, const T &initializer) {
  Initialize(n, initializer);
}

template <typename T>
void SegmentTree<T>::Initialize(const int &n, const T &initializer) {
  int64_t temp = 1;
  while (temp < n) temp *= 2;  //要素数を2のべき乗にするといいらしい
  range_       = temp;
  initializer_ = initializer;

  tree_.resize(range_ * 2 - 1);
  for (int i = 0; i < tree_.size(); i++) {
    tree_[i] = initializer;
  }
}

template <typename T>
void SegmentTree<T>::Update(int pos, const T &data) {
  pos += range_ - 1;
  tree_[pos] = data;
  Merge(Parent(pos));
}

template <typename T>
void SegmentTree<T>::Merge(const int &parent) {
  tree_[parent] = Compare(tree_[LeftChild(parent)], tree_[RightChild(parent)]);
  if (parent > 0) Merge(Parent(parent));
}

template <typename T>
T SegmentTree<T>::Query(const int &left, const int &right) {
  return PrivateQuery(left, right, 0, 0, range_);
}
template <typename T>
T SegmentTree<T>::PrivateQuery(const int &query_left, const int &query_right,
                               const int &node, const int &node_left,
                               const int &node_right) {
  // cerr << query_left << "\t" << query_right << "\t" << node << "\t" <<
  // node_left
  //  << "\t" << node_right << endl;
  if (query_left <= node_left && node_right <= query_right) {
    // cerr << "return " << tree_[node] << endl;
    return tree_[node];
  }

  else if (node_right <= query_left || query_right <= node_left) {
    // cerr << "return " << initializer_ << endl;
    return initializer_;
  } else {
    T temp_l = PrivateQuery(query_left, query_right, LeftChild(node), node_left,
                            (node_left + node_right) / 2);
    T temp_r = PrivateQuery(query_left, query_right, RightChild(node),
                            (node_left + node_right) / 2, node_right);
    return CompareQuery(temp_l, temp_r);
  }
}

template <typename T>
void SegmentTree<T>::OutputTree(void) {
  cerr << "NodeNumber\tData" << endl;
  for (int i = 0; i < tree_.size(); i++) {
    cerr << i << "\t" << tree_[i] << endl;
  }
}

// // for verifying
// // This code solves AOJ Range Query - Range Minimum Query (RMQ).
// class RMQTree : public SegmentTree<int> {
//  private:
//   int CompareQuery(const int &left, const int &right);
//   int Compare(const int &left, const int &right);

//  public:
//   RMQTree(const int &n, const int &initializer) : SegmentTree(n,
//   initializer){};
// };
// int RMQTree::CompareQuery(const int &left, const int &right) {
//   if (left < right)
//     return left;
//   else
//     return right;
// }
// int RMQTree::Compare(const int &left, const int &right) {
//   if (left < right)
//     return left;
//   else
//     return right;
// }

// int main(void) {
//   cout << std::fixed << std::setprecision(10);
//   cin.tie(0);
//   std::ios::sync_with_stdio(false);

//   int n, q;
//   cin >> n >> q;
//   RMQTree tree(n, INT32_MAX);
//   // tree.OutputTree();
//   for (int i = 0; i < q; i++) {
//     int command, x, y;
//     cin >> command >> x >> y;

//     switch (command) {
//       case 0:
//         tree.Update(x, y);
//         // tree.OutputTree();
//         break;
//       case 1:
//         cout << tree.Query(x, y + 1) << endl;
//         break;
//     }
//   }

//   return 0;
// }
