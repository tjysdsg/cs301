#include <iostream>

using std::cin;
using std::cout;

int N = 0;
int W = 0;

int dp[10001][10001]{0};
int vals[10001];
int weights[10001];
int maxv = 0;

int main() {
  cin >> N >> W;
  for (int i = 1; i <= 2 * N; i += 2) {
    cin >> weights[i] >> vals[i];
    weights[i + 1] = weights[i];
    vals[i + 1] = vals[i];
  }

  for (int i = 1; i <= 2 * N; ++i) {
    for (int j = 1; j <= W; ++j) {
      if (j - weights[i] >= 0) {
        dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - weights[i]] + vals[i]);
        maxv = std::max(dp[i][j], maxv);
      }
    }
  }
  cout << maxv;
  return 0;
}
