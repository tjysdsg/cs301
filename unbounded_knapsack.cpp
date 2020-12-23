#include <iostream>
#include <limits>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int N = 0;
int W = 0;

vector<int> dp;
vector<int> vals;
vector<int> weights;
int maxv = 0;

int main() {
  cin >> N >> W;
  vals = vector<int>(N, 0);
  weights = vector<int>(N, 0);
  dp = vector<int>(W + 1, 0);
  for (int i = 0; i < N; ++i) {
    cin >> weights[i] >> vals[i];
  }

  for (int i = 0; i < N; ++i) {
    for (int j = weights[i]; j <= W; ++j) {
      dp[j] = std::max(dp[j], dp[j - weights[i]] + vals[i]);
      maxv = std::max(dp[j], maxv);
    }
  }
  cout << maxv;
  return 0;
}
