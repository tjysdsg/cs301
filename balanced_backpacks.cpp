#include <cstring>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

constexpr int MAX_WEIGHT = 10001;
constexpr int MAX_N_ITEMS = 101;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  cin >> n;
  vector<int[MAX_WEIGHT]> weights(n);

  /// use bool so the compiler can highly optimize this code
  /// this does make a huge difference in speed
  vector<bool[MAX_WEIGHT]> dp(n);
  vector<bool[MAX_WEIGHT]> tmp(n); /// tmp: current result, dp prev result

  int ret = 0;
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    int j = 0;
    while (-1 != t) {
      weights[i][j] = t;
      cin >> t;
      ++j;
    }
  }

  for (int bag = 0; bag < n; ++bag) {
    memcpy(tmp[bag], dp[bag], sizeof(bool) * MAX_WEIGHT);
  }
  for (int i = 0; i < MAX_N_ITEMS; ++i) {
    for (int w = 1; w < MAX_WEIGHT; ++w) {
      bool valid = true;
      for (int bag = 0; bag < n; ++bag) {
        int curr_weight = weights[bag][i];

        tmp[bag][curr_weight] = true;
        if (tmp[bag][w])
          continue;

        int remain_w = w - curr_weight;
        if (remain_w < 0 || !dp[bag][remain_w])
          valid = false;
        else
          tmp[bag][w] = true;
      }
      // update max
      if (valid)
        ret = std::max(ret, w);
    }
    /// copy data from dp[bag][i] to dp[bag][i + 1]
    for (int bag = 0; bag < n; ++bag) {
      memcpy(dp[bag], tmp[bag], sizeof(bool) * MAX_WEIGHT);
    }
  }

  cout << ret;
  return 0;
}
