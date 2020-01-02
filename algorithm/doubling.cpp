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

#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

int main(){

  cin.tie(nullptr);
  std::ios::sync_with_stdio(false);

  int n;
  cin>>n;
  std::vector<int> x(n);
  for(int i=0;i<n;i++){
    cin>>x[i];
  }
  int l,q;
  cin>>l>>q;

  std::vector<int> next_node(n);
  int left=0;
  int right=1;
  while(left<n){
    if(right==n-1||x[right+1]-x[left]>l){
      next_node[left]=right;
      left++;
    }else{
      right++;
    }
  }

  DoublingMgr<int> mgr(next_node);


  int log_n=floor(log2(n));

  std::vector<int> qa(q),qb(q);
  for(int i=0;i<q;i++){
    cin>>qa[i]>>qb[i];
  }

  for(int qi=0;qi<q;qi++){
    int a=qa[qi],b=qb[qi];

    a--;
    b--;
    if(a>b) std::swap(a,b);
    int min=0;
    int max=n;
    int mid=n/2;

    while(max-min>1){
      int node=mgr.GetValue(a,mid);
      if(node>=b){
        max=mid;
        mid=(max-min)/2+min;
      }else{
        min=mid;
        mid=(max-min)/2+min;
      }

    }
    cout<<max<<endl;
  }




  return 0;
}

