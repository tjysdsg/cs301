#include "bigint.h"
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

// leetcode 486

using std::cin;
using std::cout;
using std::vector;

using Mat = vector<vector<int>>;
using BI = Bigint<100, 100000, 5>;

int main() {
  vector<vector<BI>> dp;
  vector<BI> pow2;

  int n, m;
  cin >> n >> m;
  Mat mat(n, vector<int>(m, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> mat[i][j];
    }
  }

  /// pre-calculate power of 2
  pow2 = vector<BI>(m + 1);
  BI pow = 1;
  for (int t = 1; t <= m; ++t) {
    pow = pow * 2;
    pow2[t] = pow;
  }

  BI ret = 0;
  for (int r = 0; r < n; ++r) {
    BI max_r = 0;

    /// reset dp
    dp = vector<vector<BI>>(m + 1, vector<BI>(m + 1, BI(0)));

    // main
    // i inclusive, j exclusive
    for (int i = 0; i < m; ++i) {
      for (int j = m; j >= i; --j) {
        int t = m - (j - i);
        pow = pow2[t];
        if (i > 0)
          dp[i][j] = std::max(dp[i][j], dp[i - 1][j] + pow * mat[r][i - 1],
                              bigint_cmp<100, 100000, 5>);
        if (j < m)
          dp[i][j] = std::max(dp[i][j], dp[i][j + 1] + pow * mat[r][j],
                              bigint_cmp<100, 100000, 5>);
        max_r = std::max(max_r, dp[i][j], bigint_cmp<100, 100000, 5>);
      }
    }
    ret = ret + max_r;
  }
  cout << ret.to_string();
  return 0;
}
