/*
#include "qsort.h"
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct GNode {
  std::vector<GNode *> neighbors{};
  int val = 0;
  int i = 0;
  int j = 0;
  vector<int> wells{};
};

int start_cmp(const std::pair<int, int> &a, const std::pair<int, int> &b) {
  if (a.first > b.first)
    return 1;
  if (a.first < b.first)
    return -1;
  return 0;
}

using Mat = vector<vector<GNode *>>;
std::stack<GNode *> s;
vector<std::pair<int, int>> well2plant;
vector<bool> irrigated;

vector<int> dfs(int plant) {
  if (s.empty())
    return {};

  GNode *node = s.top();
  s.pop();

  if (!node->wells.empty()) {
    irrigated[plant] = true;
    for (const auto &w : node->wells) {
      well2plant[w].first = std::min(well2plant[w].first, plant);
      well2plant[w].second = std::max(well2plant[w].second, plant);
    }
    return node->wells;
  }

  if (node->i == 0) {
    irrigated[plant] = true;
    well2plant[node->j].first = std::min(well2plant[node->j].first, plant);
    well2plant[node->j].second = std::max(well2plant[node->j].second, plant);
    node->wells.push_back(node->j);
  }

  for (auto *nbr : node->neighbors) {
    s.push(nbr);
    auto tmp = dfs(plant);
    node->wells.insert(node->wells.end(), tmp.begin(), tmp.end());
  }
  return node->wells;
}

int main() {
  int n, m;
  cin >> n >> m;
  Mat grid(n, vector<GNode *>(m, nullptr));

  well2plant = vector<std::pair<int, int>>(m, {m, 0});
  irrigated = vector<bool>(m, false);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      auto *node = new GNode;
      node->i = i;
      node->j = j;
      cin >> node->val;
      grid[i][j] = node;
    }
  }

  /// build graph
  // reversed direction, so a -> b means water can flow from b to a
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i - 1 >= 0 && grid[i - 1][j]->val > grid[i][j]->val)
        grid[i][j]->neighbors.push_back(grid[i - 1][j]);
      if (i + 1 < n && grid[i + 1][j]->val > grid[i][j]->val)
        grid[i][j]->neighbors.push_back(grid[i + 1][j]);

      if (j - 1 >= 0 && grid[i][j - 1]->val > grid[i][j]->val)
        grid[i][j]->neighbors.push_back(grid[i][j - 1]);
      if (j + 1 < m && grid[i][j + 1]->val > grid[i][j]->val)
        grid[i][j]->neighbors.push_back(grid[i][j + 1]);
    }
  }

  int n_irrigated = 0;
  for (int j = 0; j < m; ++j) {
    s = std::stack<GNode *>{};
    s.push(grid[n - 1][j]);
    dfs(j);
    if (irrigated[j])
      ++n_irrigated;
  }

  if (n_irrigated == m) {
    cout << 1 << '\n';
    qsort(well2plant.data(), 0, m - 1, start_cmp);
    int n_wells = 1;
    int curr_s = well2plant[0].first;  // inclusive
    int curr_e = well2plant[0].second; // inclusive
    vector<std::pair<int, int>> intervals(well2plant.begin() + 1,
                                          well2plant.end());
    while (curr_s > 0 || curr_e < m - 1) {
      int n_intervals = intervals.size();
      int max_end_i = 0;
      for (int i = 0; i < n_intervals; ++i) {
        if (intervals[i].first > intervals[i].second)
          /// this well cannot reach any plant
          continue;

        if (intervals[i].first <= curr_s &&
            intervals[max_end_i].second < intervals[i].second)
          max_end_i = i;
      }
      curr_e = intervals[max_end_i].second;
      intervals.erase(intervals.begin() + max_end_i);
      ++n_wells;
    }
    cout << n_wells << '\n';
  } else {
    cout << 0 << '\n';
    cout << m - n_irrigated << '\n';
  }

  return 0;
}

*/

#include <algorithm>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;

#define nx x + xx[i]
#define ny y + yy[i]

constexpr size_t MAX_N = 501;
int l[MAX_N][MAX_N], r[MAX_N][MAX_N];
int elevation[MAX_N][MAX_N];
int n, m;
bool visited[MAX_N][MAX_N];
int xx[4] = {-1, 0, 1, 0};
int yy[4] = {0, 1, 0, -1};

void dfs(int x, int y) {
  visited[x][y] = true;
  for (int i = 0; i < 4; i++) {
    if (nx < 1 || nx > n || ny < 1 || ny > m)
      continue;
    if (elevation[nx][ny] >= elevation[x][y])
      continue;
    if (!visited[nx][ny])
      dfs(nx, ny);
    l[x][y] = std::min(l[x][y], l[nx][ny]);
    r[x][y] = std::max(r[x][y], r[nx][ny]);
  }
}

int main() {
  cin >> n >> m;
  memset(visited, false, sizeof(visited));
  memset(l, 0x3F, sizeof(l));
  memset(r, 0, sizeof(r));
  for (int i = 1; i <= m; i++) {
    l[n][i] = r[n][i] = i;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> elevation[i][j];
    }
  }

  for (int i = 1; i <= m; i++) {
    if (!visited[1][i])
      dfs(1, i);
  }

  bool flag = false;
  int count = 0;
  for (int i = 1; i <= m; i++) {
    if (!visited[n][i]) {
      flag = true;
      count++;
    }
  }

  if (flag) {
    cout << 0 << '\n';
    cout << count << '\n';
    return 0;
  }
  int left = 1;
  while (left <= m) {
    int maxr = 0;
    for (int i = 1; i <= m; i++) {
      if (l[1][i] <= left)
        maxr = std::max(maxr, r[1][i]);
    }
    count++;
    left = maxr + 1;
  }
  cout << 1 << '\n';
  cout << count << '\n';
}
