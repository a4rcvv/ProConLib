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
// 3. Define AnnealManager::Cool(), ShouldContinue(),Eval(AnnealState),
// Neighbor(AnnealState),ShouldMoveToLowScore(int64_t,int64_t,float).
// 4. Instance AnnealState and make the first state.
// 5. Use Anneal(AnnealState) in main(void).

struct AnnealState {};

class AnnealManager {
  double temperature_ = 100.0;
  double Cool();
  bool ShouldContinue();
  int64_t Eval(AnnealState);
  AnnealState Neighbor(AnnealState);
  bool ShouldMoveToLowScore(int64_t, int64_t, double);

 public:
  AnnealState Anneal(AnnealState);
};

// These 5 functions should be defined.
double AnnealManager::Cool() {}
bool AnnealManager::ShouldContinue() {}
// [IMPORTANT] If "The less a score is, The better a state is" , this function
// MUST return "(true score)*(-1)". This class regards a high score as a good
// state.
int64_t AnnealManager::Eval(AnnealState state) {}
AnnealState AnnealManager::Neighbor(AnnealState state) {}
bool ShouldMoveToLowScore(int64_t prev_e, int64_t next_e, double temperature) {
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
