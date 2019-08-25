#include<algorithm>

int64_t EuclidMod(int64_t v, int64_t m){
  if(0 <= v && v < m){
    return v;
  }else if(-m <= v && v < 0){
    return v + m;
  }else{
    int64_t result = v % m;
    if(result < 0){
      result += m;
    }
    return result;
  }
}

int64_t ModInv(int64_t a, int64_t m){
  int64_t b = m, u = 1, v = 0;
  while(b){
    int64_t t = a / b;
    a -= t * b;
    std::swap(a, b);
    u -= t * v;
    std::swap(u, v);
  }
  EuclidMod(u, m);
  return u;
}

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

template<int64_t mod>
class ModInt{
  int64_t value_;

public:
  explicit ModInt(const int64_t x = 0): value_(x % mod){
  };

  ModInt& operator=(const ModInt& another){
    value_=another.value_;
    return *this;
  }

  ModInt& operator^=(const ModInt& another){
    value_=RepeatedPowMod(value_,another.value_,mod);
    return *this;
  }

  ModInt& operator+=(const ModInt& another){
    value_ += another.value_;
    value_ = EuclidMod(value_, mod);
    return *this;
  }

  ModInt& operator-=(const ModInt& another){
    value_ -= another.value_;
    value_ = EuclidMod(value_, mod);
    return *this;
  }

  ModInt& operator*=(const ModInt& another){
    value_ *= another.value_;
    value_ = EuclidMod(value_, mod);
    return *this;
  }

  ModInt& operator/=(const ModInt& another){
    value_ = value_ * ModInv(another.value_, mod);
    value_ = EuclidMod(value_, mod);
    return *this;
  }

  ModInt& operator++(){
    value_ += 1;
    value_=EuclidMod(value_,mod);
    return *this;
  }

  ModInt operator++(int){
    ModInt tmp = *this;
    this->value_+=1;
    this->value_=EuclidMod(this->value_,mod);
    return tmp;
  }

  ModInt& operator--(){
    value_ -= 1;
    value_=EuclidMod(value_,mod);
    return *this;
  }

  ModInt operator--(int){
    ModInt tmp=*this;
    this->value_-=1;
    this->value_=EuclidMod(this->value_,mod);
    return tmp;
  }



  int64_t GetValue() const{
    return value_;
  }

};

template<int64_t mod>
ModInt<mod>
operator+(const ModInt<mod>& left, const ModInt<mod>& right){
  return ModInt<mod>(left) += right;
}

template<int64_t mod>
ModInt<mod>
operator-(const ModInt<mod>& left, const ModInt<mod>& right){
  return ModInt<mod>(left) -= right;
}

template<int64_t mod>
ModInt<mod>
operator/(const ModInt<mod>& left, const ModInt<mod>& right){
  return ModInt<mod>(left) /= right;
}

template<int64_t mod>
ModInt<mod>
operator*(const ModInt<mod>& left, const ModInt<mod>& right){
  return ModInt<mod>(left) *= right;
}

template<int64_t mod>
ModInt<mod>
operator^(const ModInt<mod>& left, const ModInt<mod>& right){
  return ModInt<mod>(left) ^= right;
}

template<int64_t mod>
std::ostream& operator<<(std::ostream& stream, const ModInt<mod>& mod_int){
  stream << mod_int.GetValue();
  return stream;
}


// // for verifying
// int main(void) {
//
//
//   const int64_t MOD =  1000000000+ 7;
//   ModInt<MOD> b(MOD-1);
//   std::cout<<b<<std::endl;
//   b--;
//   std::cout<<b<<std::endl;
//   b--;
//   std::cout<<b<<std::endl;
//
//
//
//   return 0;
// }

