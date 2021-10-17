#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * @brief トポロジカルソートします
 *
 * @param inEdge inEdge[i]: iに入る辺の集合
 * @param outEdge outEdge[i]: iから出る辺の集合
 * @param start start以降の点を考えます(1-indexedの場合は1に)
 * @return vector<int> トポソできないなら空、そうでなければトポソ結果
 */
vector<int> topologicalSort(vector<unordered_set<int>> inEdge,
                            vector<unordered_set<int>> outEdge, int start) {
  set<int> s;
  vector<int> res;
  for (int i = start; i < inEdge.size(); i++) {
    if (inEdge[i].empty()) {
      s.insert(i);
    }
  }

  while (!s.empty()) {
    int curr = *s.begin();
    s.erase(curr);
    res.push_back(curr);

    unordered_set<int> edges = outEdge[curr];
    for (auto to : edges) {
      outEdge[curr].erase(to);
      inEdge[to].erase(curr);
      if (inEdge[to].empty()) {
        s.insert(to);
      }
    }
  }

  for (auto &in : inEdge) {
    if (!in.empty()) {
      return vector<int>(0);
    }
  }

  return res;
}