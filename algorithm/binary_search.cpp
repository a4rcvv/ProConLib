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

/* Templates for binary searching.
 HOW TO USE
 1: Implement BinarySearch_Comp().
 2: Copy (BS_LowerBound or BS_UpperBound) and BS_Comp.
 3: Use in main().*/

// Compare vec[key] and something.
bool BinarySearch_Comp(const int key, const std::vector<int>& vec) {
  int target = vec[key];
  // need to implement
}

// Return index number whose element is the LOWER limit returning true in
// BS_Comp().
int BinarySearch_LowerLimit(const std::vector<int>& vec) {
  int left  = -1;
  int right = vec.size();
  int mid;
  while (right - left > 1) {
    mid = left + (right - left) / 2;
    if (BinarySearch_Comp(mid, vec)) {
      right = mid;
    } else {
      left = mid;
    }
  }
  return right;
}

// Return index number whose element is the UPPER limit returning true in
// BS_Comp().
int BinarySearch_UpperLimit(const std::vector<int>& vec) {
  int left  = -1;
  int right = vec.size();
  int mid;
  while (right - left > 1) {
    mid = left + (right - left) / 2;
    if (BinarySearch_Comp(mid, vec)) {
      left = mid;
    } else {
      right = mid;
    }
  }
  return left;
}

// for verifying
// this code solves exawizards2019-C.

// struct Query {
//   char c, d;
// };

// int n, q;
// std::string s;
// std::vector<Query> query;

// bool BinarySearch_Comp_L(const int key, const std::string& vec) {
//   int target = vec[key];
//   // need to implement
//   int pos = key;
//   for (int i = 0; i < q; i++) {
//     if (vec[pos] == query[i].c) {
//       if (query[i].d == 'L') {
//         pos--;
//       } else {
//         pos++;
//       }
//     }
//     if (pos == n)
//       return false;
//     else if (pos == -1)
//       return true;
//   }
//   return false;
// }
// bool BinarySearch_Comp_R(const int key, const std::string& vec) {
//   int target = vec[key];
//   // need to implement
//   int pos = key;
//   for (int i = 0; i < q; i++) {
//     if (vec[pos] == query[i].c) {
//       if (query[i].d == 'L') {
//         pos--;
//       } else {
//         pos++;
//       }
//     }
//     if (pos == n)
//       return true;
//     else if (pos == -1)
//       return false;
//   }
//   return false;
// }

// // Return index number whose element is the LOWER limit returning true in
// // BS_Comp().
// int BinarySearch_LowerLimit(const std::string& vec) {
//   int left  = -1;
//   int right = vec.size();
//   int mid;
//   while (right - left > 1) {
//     mid = left + (right - left) / 2;
//     if (BinarySearch_Comp_R(mid, vec)) {
//       right = mid;
//     } else {
//       left = mid;
//     }
//   }
//   return right;
// }

// // Return index number whose element is the UPPER limit returning true in
// // BS_Comp().
// int BinarySearch_UpperLimit(const std::string& vec) {
//   int left  = -1;
//   int right = vec.size();
//   int mid;
//   while (right - left > 1) {
//     mid = left + (right - left) / 2;
//     if (BinarySearch_Comp_L(mid, vec)) {
//       left = mid;
//     } else {
//       right = mid;
//     }
//   }
//   return left;
// }

// int main(void) {
//   cout << std::fixed << std::setprecision(10);
//   cin.tie(0);
//   std::ios::sync_with_stdio(false);

//   cin >> n >> q;

//   cin >> s;

//   query.resize(q);
//   for (int i = 0; i < q; i++) {
//     Query m1;
//     cin >> m1.c;
//     cin >> m1.d;
//     query[i] = m1;
//   }
//   cerr << "\033[93m" << BinarySearch_LowerLimit(s) << "\033[m" << endl;
//   cerr << "\033[93m" << BinarySearch_UpperLimit(s) << "\033[m" << endl;

//   cout << BinarySearch_LowerLimit(s) - BinarySearch_UpperLimit(s) - 1 <<
//   endl;

//   return 0;
// }