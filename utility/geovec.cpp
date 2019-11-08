#include <cmath>



struct Vector3{
  double x,y,z;
  Vector3():x(0),y(0),z(0){}
  Vector3(double _x,double _y,double _z):x(_x),y(_y),z(_z){}

  Vector3 operator+()const{
    return *this;
  }

  Vector3 operator-()const{
    return Vector3(-x,-y,-z);
  }

  Vector3 operator+(const Vector3& another)const{
    return Vector3(x+another.x,y+another.y,z+another.z);
  }

  Vector3 operator-(const Vector3& another)const{
    return *this+(-another);
  }
  Vector3& operator+=(const Vector3& another){
    x+=another.x;
    y+=another.y;
    z+=another.z;
    return *this;
  }

  Vector3& operator-=(const Vector3& another){
    x-=another.x;
    y-=another.y;
    z-=another.z;
    return *this;
  }

  Vector3 operator*(const double scalar)const{
    return Vector3(x*scalar,y*scalar,z*scalar);
  }
  Vector3 operator/(const double scalar)const{
    return Vector3(x/scalar,y/scalar,z/scalar);
  }
  Vector3& operator*=(const double scalar){
    x*=scalar;
    y*=scalar;
    z*=scalar;
    return *this;
  }
  Vector3& operator/=(const double scalar){
    x/=scalar;
    y/=scalar;
    z/=scalar;
    return *this;
  }

  Vector3 UnitVector(){
    double abs=Abs();
    return *this/abs;
  }

  double Cos(const Vector3&)const;


  double Abs()const{
    return sqrt(x*x+y*y+z*z);
  }

};

double InnerProduct(Vector3&, Vector3&);
Vector3 OuterProduct(Vector3&,Vector3&);

double Vector3::Cos(const Vector3& another)const{
  return InnerProduct(*this,another)/(*this).Abs()/another.Abs();
}


double InnerProduct(const Vector3& a, const Vector3& b){
  return a.x*b.x+a.y*b.y+a.z*b.z;
}

Vector3 OuterProduct(const Vector3& a, const Vector3& b){
  return Vector3(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}

