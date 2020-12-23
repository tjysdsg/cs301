#include <algorithm>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
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
    if (x + xx[i] < 1 || x + xx[i] > n || y + yy[i] < 1 || y + yy[i] > m)
      continue;
    if (elevation[x + xx[i]][y + yy[i]] >= elevation[x][y])
      continue;
    if (!visited[x + xx[i]][y + yy[i]])
      dfs(x + xx[i], y + yy[i]);
    l[x][y] = std::min(l[x][y], l[x + xx[i]][y + yy[i]]);
    r[x][y] = std::max(r[x][y], r[x + xx[i]][y + yy[i]]);
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
