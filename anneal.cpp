#include <algorithm>
#include <cstdio>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

class AnnealState {};

class AnnealManager {
  float temperature_;
  float Cool();
  bool ShouldContinue();
  int Eval(AnnealState);
  AnnealState Neighbor(AnnealState);

 public:
  int Anneal(AnnealState);
};

float AnnealManager::Cool() {
  const float cooling_rate = 0.9;
  return temperature_ * cooling_rate;
}

bool ShouldContinue() {}

int main(void) {
  cout << std::fixed << std::setprecision(10);
  cin.tie(0);
  std::ios::sync_with_stdio(false);

  return 0;
}
