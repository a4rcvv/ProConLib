#include <algorithm>
#include <chrono>
#include <cstdio>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

// HOW TO USE THIS CLASSES
// 1. Set the default temperature in AnnealManager.
// 2. Define AnnealState
// 2. Define AnnealManager::Cool(), ShouldContinue(),Eval(AnnealState),
// Neighbor(AnnealState),ShouldMoveToLowScore(int64_t,int64_t,float).
// 3. Instance AnnealState and make the first state.
// 4. Use Anneal(AnnealState) in main(void).

class AnnealState {};

class AnnealManager {
  float temperature_ = 100.0;
  float Cool();
  bool ShouldContinue();
  int64_t Eval(AnnealState);
  AnnealState Neighbor(AnnealState);
  bool ShouldMoveToLowScore(int64_t, int64_t, float);

 public:
  AnnealState Anneal(AnnealState);
};

// These 5 functions should be defined.
float AnnealManager::Cool() {}
bool AnnealManager::ShouldContinue() {}
int64_t AnnealManager::Eval(AnnealState state) {}
AnnealState AnnealManager::Neighbor(AnnealState state) {}
bool ShouldMoveToLowScore(int64_t prev_e, int64_t next_e, float temperature) {
  // If prev<next, this function must return true.
  if (prev_e < next_e) return true;
}

AnnealState AnnealManager::Anneal(AnnealState start_state) {
  AnnealState state      = start_state;
  int64_t e              = Eval(state);
  AnnealState best_state = state;
  int64_t best_e         = e;
  while (ShouldContinue()) {
    AnnealState next_state = Neighbor(state);
    int64_t next_e         = Eval(next_state);
    temperature_           = Cool();
    if (next_e > best_e) {
      best_state = next_state;
      best_e     = next_e;
      state      = next_state;
      e          = next_e;
    } else if (ShouldMoveToLowScore(e, next_e, temperature_)) {
      state = next_state;
      e     = next_e;
    }
  }
  return best_state;
}

int main(void) {
  cout << std::fixed << std::setprecision(10);
  cin.tie(0);
  std::ios::sync_with_stdio(false);

  return 0;
}
