#include <vector>
#include <string>
#include <iostream>
#include<complex>

using std::cout;
using std::endl;
using std::cin;

//Copy from this line!

typedef std::complex<double> Complex;

std::vector<Complex> DFT(std::vector<Complex> func, int size, int sign){
  if(size==1) return func;

  std::vector<Complex> result(size);
  std::vector<Complex> func_a(size/2);
  std::vector<Complex> func_b(size/2);
  for(int i=0;i<size/2;i++){
    func_a[i]=func[2*i];
    func_b[i]=func[2*i+1];
  }
  func_a=DFT(func_a,size/2,sign);
  func_b=DFT(func_b,size/2,sign);

  Complex zeta(cos(2.0*M_PI/size),sin(2.0*M_PI/size)*sign);
  Complex zeta_pow(1);
  for(int i=0;i<size;i++){
    result[i]=func_a[i%(size/2)]+zeta_pow*func_b[i%(size/2)];
    zeta_pow*=zeta;
  }
  return result;
}

std::vector<Complex> InvDFT(std::vector<Complex> func, int size){
  std::vector<Complex> result=DFT(func, size, -1);
  for(int i=0;i<size;i++){
    result[i]/=size;
  }
  return result;
}

std::vector<Complex> MultyplyFunction(std::vector<Complex> func_f, std::vector<Complex> func_g){
  int min_size=func_f.size()+func_g.size()+1;
  int size=1;
  while(size<min_size){
    size*=2;
  }
  func_f.resize(size);
  func_g.resize(size);
  func_f=DFT(func_f,size,1);
  func_g=DFT(func_g,size,1);
  std::vector<Complex> func(size);
  for(int i=0;i<size;i++){
    func[i]=func_f[i]*func_g[i];
  }
  return InvDFT(func,size);


}

// int main(void){
//   int n;
//   cin>>n;
//   std::vector<std::complex<double>> a(n+1),b(n+1);
//   a[0]=std::complex<double>(0);
//   b[0]=std::complex<double>(0);
//   for(int i=1;i<=n;i++){
//     int x,y;
//     cin>>x>>y;
//     a[i]=std::complex<double>(x);
//     b[i]=std::complex<double>(y);
//   }
//   std::vector<std::complex<double>> c=MultyplyFunction(a,b);
//   for(int i=1;i<=2*n;i++){
//     cout<<lround(c[i].real())<<endl;
//   }
// }





