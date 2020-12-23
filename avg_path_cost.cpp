/*
#include <iostream>
#include <limits>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct Edge {
  int src = -1;
  int w = 0;
};

struct State {
  float cost = 0;
  int n_edges = 0;
};

int main() {
  int m, n;
  cin >> n >> m;
  vector<Edge> edges(n); // edges[i] means edges[i].src -> i
  for (int i = 0; i < m; ++i) {
    int a, b, w;
    cin >> a >> b >> w;
    if (edges[b].src != -1 && edges[b].w > w) {
      edges[b].src = a;
      edges[b].w = w;
    } else {
      edges[b].src = a;
      edges[b].w = w;
    }
  }

  int q = 0;
  cin >> q;
  vector<std::pair<int, int>> qs(q, {0, 0});
  for (int i = 0; i < q; ++i) {
    cin >> qs[i].first >> qs[i].second;
  }

  constexpr float FLOAT_MAX = std::numeric_limits<float>::max();

  for (int qi = 0; qi < q; ++qi) {
    int src = qs[qi].first - 1;
    int dest = qs[qi].second - 1;
    vector<vector<vector<State>>> dp(
        n, vector<vector<State>>(n, vector<State>(m)));
    dp[src][dest][0].n_edges = 1;
    dp[src][dest][0].cost = FLOAT_MAX;
    dp[src][src][0].n_edges = 0;
    dp[src][src][0].cost = 0;

    float ret = FLOAT_MAX;
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        float prev_cost = dp[src][dest][j - 1].cost;
        int prev_n_edges = dp[src][dest][j - 1].n_edges;
        float cost =
            (prev_cost * prev_n_edges + edges[dest].w) / (prev_n_edges + 1);
        if (prev_cost > cost) {
          dp[src][dest][j].cost = cost;
          dp[src][dest][j].n_edges = prev_n_edges + 1;
          ret = std::min(ret, cost);
        } else
          ret = std::min(ret, prev_cost);
      }
    }
    cout << ret << '\n';
  }
  return 0;
}
*/

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
