// for verifying anneal.cpp

// This code solves RCO 3rd A -
// ツーリストXの旅行計画(https://atcoder.jp/contests/rco-contest-2019-qual/tasks/rco_contest_2019_qual_a).

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

class RandomRealNumber {
  std::mt19937_64 mt_maker_;
  std::uniform_real_distribution<double> range_maker_;

 public:
  RandomRealNumber(double min, double max) {
    std::random_device seed_maker;
    mt_maker_.seed(seed_maker());
    // range_maker_.min = min;
    // range_maker_.max = max;
    std::uniform_real_distribution<double>::param_type param(min, max);
    range_maker_.param(param);
  }

  double Make(void) {
    return range_maker_(mt_maker_);
  }
  double operator()(void) {
    return Make();
  }
};

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

class Timer {
  std::chrono::system_clock::time_point start_time_;

 public:
  // restart the clock.
  void restart(void) {
    start_time_ = std::chrono::system_clock::now();
  }
  // When instantced, this timer restart itself automatically.
  Timer(void) {
    restart();
  }
  // Get the lap time(milliseconds).
  long long LapTime_millisec(void) {
    auto lap_time = std::chrono::system_clock::now();
    auto dur      = lap_time - start_time_;
    auto msec =
        std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    return msec;
  }
  // Get the lap time(seconds).
  long long LapTime_sec(void) {
    auto lap_time = std::chrono::system_clock::now();
    auto dur      = lap_time - start_time_;
    auto sec = std::chrono::duration_cast<std::chrono::seconds>(dur).count();
    return sec;
  }
};

int n;
int point_x[200], point_y[200];
double distance(int prev, int aft) {
  return sqrt(std::pow(point_x[prev] - point_x[aft], 2) +
              std::pow(point_y[prev] - point_y[aft], 2));
}

struct AnnealState {
  int path[200];
};

class AnnealManager {
  float temperature_  = 100000.0;
  float cooling_rate_ = 0.999;
  Timer timer_;
  RandomRealNumber rand1_;
  RandomIntNumber rand198_;

  float Cool();
  bool ShouldContinue();
  double Eval(AnnealState);
  AnnealState Neighbor(AnnealState);
  bool ShouldMoveToLowScore(double, double, float);

 public:
  AnnealManager(void);
  AnnealState Anneal(AnnealState);
};

AnnealManager::AnnealManager(void)
    : timer_(), rand1_(0.0, 1.0), rand198_(0, n - 2) {}

// These 5 functions should be defined.
float AnnealManager::Cool() {
  return temperature_ * cooling_rate_;
}
bool AnnealManager::ShouldContinue() {
  return timer_.LapTime_millisec() < 1990;
}
double AnnealManager::Eval(AnnealState state) {
  double average = 0.0;
  for (int i = 0; i < n - 1; i++) {
    average += distance(state.path[i], state.path[i + 1]);
  }
  average += distance(state.path[n - 1], state.path[0]);
  average /= n;
  double variance = 0.0;
  for (int i = 0; i < n - 1; i++) {
    variance +=
        std::pow(distance(state.path[i], state.path[i + 1]) - average, 2);
  }
  variance += std::pow(distance(state.path[n - 1], state.path[0]) - average, 2);
  variance /= n;
  // cout << variance << "\t";
  return variance;
}
AnnealState AnnealManager::Neighbor(AnnealState state) {
  int swap_left             = rand198_();
  int tempdata              = state.path[swap_left];
  state.path[swap_left]     = state.path[swap_left + 1];
  state.path[swap_left + 1] = tempdata;
  return state;
}
bool AnnealManager::ShouldMoveToLowScore(double prev_e, double next_e,
                                         float temperature) {
  // If prev>next, this function must return true.
  // cout << "probability:" << exp((prev_e - next_e) / temperature) << endl;
  if (prev_e > next_e)
    return true;
  else if (exp((prev_e - next_e) / temperature) > rand1_())
    return true;
  else
    return false;
}

AnnealState AnnealManager::Anneal(AnnealState start_state) {
  AnnealState state      = start_state;
  double e               = Eval(state);
  AnnealState best_state = state;
  double best_e          = e;
  timer_.restart();
  while (ShouldContinue()) {
    AnnealState next_state = Neighbor(state);
    double next_e          = Eval(next_state);
    temperature_           = Cool();
    // cout << "temp:" << temperature_ << "\t";
    if (next_e < best_e) {
      // cout << "probability:" << 1 << endl;
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

  cin >> n;
  AnnealState first_state;
  AnnealManager manager;
  for (int i = 0; i < n; i++) {
    cin >> point_x[i] >> point_y[i];
    first_state.path[i] = i;
  }
  AnnealState result = manager.Anneal(first_state);

  for (int i = 0; i < n; i++) {
    cout << result.path[i] << endl;
  }

  return 0;
}
