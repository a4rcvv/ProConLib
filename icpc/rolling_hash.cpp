#include<algorithm>
#include<iostream>
#include<random>
#include<vector>
#include<string>
#include<cassert>
#include <iomanip>

using std::cout;
using std::endl;
using std::cerr;
using std::cin;

// return base^exponent (MOD. mod).
int64_t RepeatedPowMod(int64_t base, int64_t exponent, int64_t mod) {
  if (exponent == 0)
    return 1;
  else if (exponent % 2 == 0) {
    int64_t root = RepeatedPowMod(base, exponent / 2, mod);
    return (root * root) % mod;
  } else {
    return (base * RepeatedPowMod(base, exponent - 1, mod)) % mod;
  }
}

class RandomIntNumber {
  std::mt19937_64 mt_maker_;
  std::uniform_int_distribution<int64_t> range_maker_;

public:
  RandomIntNumber(int64_t min, int64_t max) {
    std::random_device seed_maker;
    mt_maker_.seed(seed_maker());
    // range_maker_.min = min;
    // range_maker_.max = max;
    std::uniform_int_distribution<int64_t>::param_type param(min, max);
    range_maker_.param(param);
  }
  int64_t Make(void) {
    return range_maker_(mt_maker_);
  }
  int64_t operator()(void) {
    return Make();
  }
};

class RollingHash{
  static const int64_t MOD_=1000000007;
  std::vector<int64_t> hash_;
  std::string str_;
  RandomIntNumber random_int_number_;
  int64_t base_;

public:
  RollingHash(const std::string& str):random_int_number_(2,MOD_-2),str_(str){
    base_=random_int_number_.Make();
    for(int i=0;i<str.size();i++){
      if(i==0){
        hash_.push_back(int64_t(str[0]));
      }else{
        int64_t result(hash_[i-1]);
        result*=int64_t(base_);
        result%=MOD_;
        result+=int64_t(str[i]);
        result%=MOD_;
        hash_.push_back(result);
      }
    }
  }
  RollingHash(const std::string& str,int64_t base):random_int_number_(2,MOD_-2),str_(str),base_(base){
    for(int i=0;i<str.size();i++){
      if(i==0){
        hash_.push_back(int64_t(str[0]));
      }else{
        int64_t result(hash_[i-1]);
        result*=int64_t(base_);
        result%=MOD_;
        result+=int64_t(str[i]);
        result%=MOD_;
        hash_.push_back(result);
      }
    }

  }
  int64_t GetHash(int front,int back){
    if(front>back){
      cerr<<"RollingHash::GetHash() Error: argument\"front\" is larger than \"back\""<<endl;
      abort();
    }
    if(front==0) return hash_[back];
    int64_t result=hash_[back]-hash_[front-1]*int64_t(RepeatedPowMod(base_,back-front+1,MOD_));
    result%=MOD_;
    return result;
  }
  int64_t GetBase(){
    return base_;
  }
};

bool IsContaining(std::string a,std::string b){
  if(a.size()<b.size()){
    std::swap(a,b);
  }
  RollingHash hash_a(a);
  RollingHash hash_b(b,hash_a.GetBase());

  for(int front=0;front+b.size()-1<a.size();front++){
    int back=front+b.size()-1;
    if(hash_a.GetHash(front,back)==hash_b.GetHash(0,b.size()-1)) return true;
  }
  return false;
}



