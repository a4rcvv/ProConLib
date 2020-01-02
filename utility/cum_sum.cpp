#include <vector>
#include <cstdint>

using namespace std;

using lint=int64_t;
using uint=uint32_t;
using ulint=uint64_t;

template<class T>
using vector2d=vector<vector<T>>;

template<class T>
struct CumulativeSum2D{
  vector2d<T> cum;

  CumulativeSum2D(const vector2d<T>& data):cum(data.size(), vector<T>(data[0].size(),0)){
    cum[0][0]=data[0][0];
    for(int r=1;r<data.size();r++){
      cum[r][0]=cum[r-1][0]+data[r][0];
    }
    for(int c = 1; c < data[0].size(); ++c){
      cum[0][c]=cum[0][c-1]+data[0][c];
    }
    for(int r = 1; r < data.size(); ++r){
      for(int c = 1; c < data[0].size(); ++c){
        cum[r][c]=cum[r-1][c]+cum[r][c-1]-cum[r-1][c-1]+data[r][c];
      }
    }
  }


  /// \return 2頂点が(sr,sc)と(gr,gc)であるような矩形内の和(2頂点を含む)
  T Query(int sr, int sc, int gr, int gc){
    T result=cum[gr][gc];
    if(sr-1>=0){
      result-=cum[sr-1][gc];
    }
    if(sc-1>=0){
      result-=cum[gr][sc-1];
    }
    if(sr-1>=0&&sc-1>=0){
      result+=cum[sr-1][sc-1];
    }
    return result;
  }
};

template<class T>
struct CumulativeSum1D{
  vector<T> cum;

  CumulativeSum1D(const vector<T>& data):cum(data.size(),0){
    cum[0]=data[0];
    for(int i = 1; i < data.size(); ++i){
      cum[i]=cum[i-1]+data[i];
    }
  }


  /// \return 区間[l,r]の和
  T Query(int l, int r){
    return (l>0)?cum[r]-cum[l-1]:cum[r];
  }
};



//verify

// #include <iostream>
//
// template<class T>
// bool UpdateMax(T &a, const T &b){
//   if(a<b){
//     a=b;
//     return true;
//   }else{
//     return false;
//   }
// }
//
// template<class T>
// bool UpdateMin(T &a, const T &b){
//   if(a>b){
//     a=b;
//     return true;
//   }else{
//     return false;
//   }
// }

// int main(){
//   int n;
//   cin>>n;
//   vector2d<lint> a(n, vector<lint>(n, 0));
//   for(int i = 0; i < n; ++i){
//     for(int j = 0; j < n; ++j){
//       cin>>a[i][j];
//     }
//   }
//
//   CumulativeSum2D<lint> cum(a);
//   lint result=INT64_MIN/2;
//
//   for(int sr = 0; sr < n; ++sr){
//     for(int sc = 0; sc < n; ++sc){
//       for(int gr = sr; gr < n; ++gr){
//         for(int gc = sc; gc < n; ++gc){
//           UpdateMax(result,cum.Query(sr,sc,gr,gc));
//         }
//       }
//     }
//   }
//
//   cout<<result<<endl;
//
// }

// int main(){
//   while(true){
//     int n,k;
//     cin>>n>>k;
//     if(n==0) break;
//
//     vector<lint> a(n);
//     for(int i = 0; i < n; ++i){
//       cin>>a[i];
//     }
//     CumulativeSum1D<lint> cum(a);
//     lint result=INT64_MIN;
//     for(lint l=0;l<n;l++){
//       lint r=l+k-1;
//       if(r>=n) break;
//       UpdateMax(result,cum.Query(l,r));
//     }
//     cout<<result<<endl;
//   }
//
//
// }