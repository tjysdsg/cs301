#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::vector;

int n;
int m;
vector<vector<vector<double>>> f;

void pathfind() {
  for (int i = 1; i <= n; i++) {
    f[i][i][0] = 0;
  }

  for (int ne = 1; ne <= n; ne++) {
    for (int n3 = 1; n3 <= n; n3++) {
      for (int n1 = 1; n1 <= n; n1++) {
        if (f[n1][n3][ne - 1] != 1e9) {
          for (int n2 = 1; n2 <= n; n2++) {
            if (f[n1][n2][ne] > f[n1][n3][ne - 1] + f[n3][n2][1])
              f[n1][n2][ne] = f[n1][n3][ne - 1] + f[n3][n2][1];
          }
        }
      }
    }
  }
}

int main() {
  f = vector<vector<vector<double>>>(
      55, vector<vector<double>>(55, vector<double>(55, 1e9)));
  cin >> n >> m;
  constexpr double inf = 1e9;
  int a;
  int b;
  int cost;
  while (m--) {
    cin >> a >> b >> cost;
    if (cost < f[a][b][1]) {
      f[a][b][1] = cost;
    }
  }
  pathfind();
  int q;
  cin >> q;
  while (q--) {
    cin >> a >> b;
    double ans = inf;
    bool have_path = false;
    for (int i = 1; i < n; i++) {
      if (f[a][b][i] < inf) {
        have_path = true;
        if (ans * i > f[a][b][i])
          ans = f[a][b][i] / i;
      }
    }
    if (have_path)
      printf("%.3lf\n", ans);
    else
      cout << "OMG!\n";
  }
}
