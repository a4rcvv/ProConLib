#include<vector>
#include<iostream>
//参考: https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a#4-%E7%B4%AF%E4%B9%97-an


class ModCombination{
  std::vector<int64_t> fac, finv, inv;
  int64_t max,mod;
public:
  ModCombination(int64_t max_,int64_t mod_):max(max_),mod(mod_),fac(max_+1),finv(max_+1),inv(max_+1){
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < max; i++){
      fac[i] = fac[i - 1] * i % mod;
      inv[i] = mod - inv[mod%i] * (mod / i) % mod;
      finv[i] = finv[i - 1] * inv[i] % mod;
    }
  }
  int64_t GetCombination(int n, int k){
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n - k] % mod) % mod;
  }

};