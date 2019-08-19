#include<algorithm>
#include<iostream>

using std::cout;
using std::endl;

constexpr int64_t EuclidMod(int64_t v, int64_t m){
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

constexpr int64_t ModInv(int64_t a, int64_t m){
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

template<int64_t mod>
class ModInt{
  int64_t _value;

public:
  constexpr explicit ModInt(const int64_t x = 0): _value(x % mod){
  };

  constexpr ModInt& operator+=(const ModInt& another){
    _value += another._value;
    _value = EuclidMod(_value, mod);
    return *this;
  }

  constexpr ModInt& operator-=(const ModInt& another){
    _value -= another._value;
    _value = EuclidMod(_value, mod);
    return *this;
  }

  constexpr ModInt& operator*=(const ModInt& another){
    _value *= another._value;
    _value = EuclidMod(_value, mod);
    return *this;
  }

  constexpr ModInt& operator/=(const ModInt& another){
    _value = _value * ModInv(another._value, mod);
    _value = EuclidMod(_value, mod);
    return *this;
  }

  constexpr ModInt& operator++(){
    _value += ModInt(1);
    return *this;
  }

  constexpr ModInt operator++(int){
    ModInt tmp = *this;
    ++tmp;
    return tmp;
  }

  int64_t GetValue() const{
    return _value;
  }

};

template<int64_t mod>
constexpr ModInt<mod>
operator+(const ModInt<mod>& left, const ModInt<mod>& right){
  return ModInt<mod>(left) += right;
}

template<int64_t mod>
constexpr ModInt<mod>
operator-(const ModInt<mod>& left, const ModInt<mod>& right){
  return ModInt<mod>(left) -= right;
}

template<int64_t mod>
constexpr ModInt<mod>
operator/(const ModInt<mod>& left, const ModInt<mod>& right){
  return ModInt<mod>(left) /= right;
}

template<int64_t mod>
constexpr ModInt<mod>
operator*(const ModInt<mod>& left, const ModInt<mod>& right){
  return ModInt<mod>(left) *= right;
}

template<int64_t mod>
std::ostream& operator<<(std::ostream& stream, const ModInt<mod>& mod_int){
  stream << mod_int.GetValue();
  return stream;
}



