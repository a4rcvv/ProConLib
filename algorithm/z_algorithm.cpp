#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::endl;

/// \brief return a vector: vec[i]="LCP of s and s[i,|s|)"
/// \param s
/// \return
std::vector<int> ZAlgorithm(const std::string& s){
  int c=0;
  std::vector<int> result(s.size());
  for(int i=1;i<s.size();i++){
    if(i+result[i-c]<c+result[c]){
      result[i]=result[i-c];
    }else{
      int j=std::max(0,c+result[c]-i);
      while(i+j<s.size()&&s[j]==s[i+j]){
        ++j;
      }
      result[i]=j;
      c=i;
    }
  }
  result[0]=s.size();
  return result;
}

// int main(void){
//   std::vector<int> hoge=ZAlgorithm("aaabaaaab");
//   for(auto v:hoge){
//     cout<<v<<endl;
//   }
//   return 0;
// }
