#include<vector>
#include <cmath>

//参考: http://satanic0258.hatenablog.com/entry/2017/02/23/222647

//FIXME: NOT VERIFIED!
//なんかAtCoderのジャッジがおかしい気がする

template<typename T>
class DoublingMgr{
  //next[k][i]: iの2^k個次の要素
  const int n,log_n;
  std::vector<std::vector<T>> next;
public:
  DoublingMgr(std::vector<int> next_vec):n(next_vec.size()),log_n(floor(log2(next_vec.size()))),
  next(floor(log2(next_vec.size()))+1,std::vector<T>(next_vec.size())){
    for(int i=0;i<n;i++){
      next[0][i]=next_vec[i];
    }
    for(int k=0;k<log_n;k++){
      for(int i=0;i<n;i++){
        if(next[k][i]==-1){
          next[k+1][i]=-1;
        }else{
          next[k+1][i]=next[k][next[k][i]];
        }
      }
    }
  }
  /// \brief p番目の要素のq個次を求める
  T GetValue(int p,int q){
    for(int k=log_n-1;k>=0;k--){
      if(p==-1){
        return p;
      }
      if((q>>k)&1){
        p=next[k][p];
      }
      // if((q>>k)&1){
      //   p=next[k][p];
      //   if(p==n-1) break;
      // }
    }
    return p;
  }
};
