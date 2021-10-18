
//
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Dice {

  // u,n,d,s,l,r
  vector<int> face;      //
  vector<int> direction; // 0なら基準方向、1なら右90度回転

  void getRightRotated(int &v) {
    v++;
    if (v == 4)
      v = 0;
  }
  void getLeftRotated(int &v) {
    v--;
    if (v == -1)
      v = 3;
  }

public:
  void rotateN() {
    int face3 = face[3];
    face[3] = face[2];
    face[2] = face[1];
    face[1] = face[0];
    face[0] = face3;
    getLeftRotated(direction[4]);
    getRightRotated(direction[5]);
  }
  void rotateS() {
    int face0 = face[0];
    face[0] = face[1];
    face[1] = face[2];
    face[2] = face[3];
    face[3] = face0;
    getRightRotated(direction[4]);
    getLeftRotated(direction[5]);
  }
  void rotateE() {
    int face4 = face[4];
    face[4] = face[2];
    face[2] = face[5];
    face[5] = face[0];
    face[0] = face4;

    getRightRotated(direction[3]);
    getLeftRotated(direction[1]);

    getRightRotated(direction[0]);
    getRightRotated(direction[4]);
    getRightRotated(direction[2]);
    getRightRotated(direction[5]);
  }
  void rotateW() {
    int face0 = face[0];
    face[0] = face[5];
    face[5] = face[2];
    face[2] = face[4];
    face[4] = face0;

    getLeftRotated(direction[3]);
    getRightRotated(direction[1]);
    getLeftRotated(direction[0]);
    getLeftRotated(direction[4]);
    getLeftRotated(direction[2]);
    getLeftRotated(direction[5]);
  }
  void rotateL() {
    int face3 = face[3];
    face[3] = face[4];
    face[4] = face[1];
    face[1] = face[5];
    face[5] = face3;

    getLeftRotated(direction[0]);
    getLeftRotated(direction[2]);

    getLeftRotated(direction[1]);
    getLeftRotated(direction[1]);
    getLeftRotated(direction[4]);
    getLeftRotated(direction[4]);
  }
  void rotateR() {
    int face3 = face[3];
    face[3] = face[5];
    face[5] = face[1];
    face[1] = face[4];
    face[4] = face3;

    getRightRotated(direction[0]);
    getRightRotated(direction[2]);

    getLeftRotated(direction[1]);
    getLeftRotated(direction[1]);
    getLeftRotated(direction[5]);
    getLeftRotated(direction[5]);
  }
  vector<pair<int, int>> get() {
    
    vector<pair<int, int>> res(6);
    for (int i = 0; i < 6; i++) {
      res[i] = {face[i], direction[i]};
    }
    return res;
  }

  /**
   * @brief Construct a new Dice object
   *
   * @param initialFace 面の情報。{u,n,d,s,l,r}
   * @param initialDir 面の向きの情報。
   * 基準方向: 上面が北向き
   */
  Dice(vector<int> initialFace, vector<int> initialDir) {
    assert(initialFace.size() == 6 && initialDir.size() == 6);
    for (int i = 0; i < 6; i++) {
      assert(0 <= initialDir[i] && initialDir[i] <= 3);
    }
    this->face = initialFace;
    this->direction = initialDir;
  }
};

// verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0502

int main(void) {
  while (true) {
    int n;
    int res = 0;
    cin >> n;
    if (n == 0)
      break;
    Dice dice(vector<int>{1, 5, 6, 2, 4, 3}, vector<int>{0, 0, 0, 0, 0, 0});
    for (int i = 0; i < n; i++) {
      string s;
      cin >> s;
      if (s == "North") {
        dice.rotateN();
      } else if (s == "East") {
        dice.rotateE();
      } else if (s == "South") {
        dice.rotateS();
      } else if (s == "West") {
        dice.rotateW();
      } else if (s == "Right") {
        dice.rotateR();
      } else {
        dice.rotateL();
      }
      vector<pair<int, int>> curr = dice.get();
      for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
          assert(curr[i] != curr[j]);
        }
      }
      res += curr[0].first;
    }
    cout << res+1 << endl;
  }
}