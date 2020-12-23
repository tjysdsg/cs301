// #include "BigInt.hpp"
#include "qsort.h"
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

using BI = long long;

inline bool is_odd(const BI &val) { return val % 2 != 0; }

int main() {
  int n = 0;
  int m = 0;
  cin >> n;
  vector<int> nums(n, 0);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  cin >> m;
  vector<int> ks(m, 0);
  for (int i = 0; i < m; ++i) {
    cin >> ks[i];
  }

  qsort(nums.data(), 0, n - 1);

  // fill in caches
  vector<int> upper_evens(n, -1);
  vector<int> upper_odds(n, -1);
  {
    int ei = -1;
    int oi = -1;
    for (int i = n - 1; i >= 0; --i) {
      if (is_odd(nums[i]))
        oi = i;
      else
        ei = i;
      upper_evens[i] = ei;
      upper_odds[i] = oi;
    }
  }
  vector<int> lower_evens(n, -1);
  vector<int> lower_odds(n, -1);
  {
    int ei = -1;
    int oi = -1;
    for (int i = 0; i < n; ++i) {
      if (is_odd(nums[i]))
        oi = i;
      else
        ei = i;
      lower_evens[i] = ei;
      lower_odds[i] = oi;
    }
  }

  BI cumsum = 0;
  vector<BI> cache(n, 0);
  for (int i = n - 1; i > 0; --i) {
    cumsum += nums[i];

    BI sum = cumsum;
    if (is_odd(sum)) {
      cache[n - i - 1] = sum;
      continue;
    }

    /// 1. minus an even and add an odd
    BI sum1 = sum;
    {
      int tmp1 = upper_evens[i];
      int tmp2 = lower_odds[i - 1];
      if (tmp1 != -1 && tmp2 != -1) {
        sum1 = sum1 - nums[tmp1] + nums[tmp2];
      }
    }
    if (!is_odd(sum1))
      sum1 = -1;

    /// 2. minus an odd and add an even
    BI sum2 = sum;
    {
      int tmp1 = upper_odds[i];
      int tmp2 = lower_evens[i - 1];
      if (tmp1 != -1 && tmp2 != -1) {
        sum2 = sum2 - nums[tmp1] + nums[tmp2];
      }
    }
    if (!is_odd(sum2))
      sum2 = -1;

    sum = std::max(sum1, sum2);
    cache[n - i - 1] = sum;
  }
  cumsum += nums[0];
  if (is_odd(cumsum)) {
    cache[n - 1] = cumsum;
  } else {
    cache[n - 1] = -1;
  }

  for (const auto &k : ks) {
    if (k > n || k == 0) {
      cout << -1 << '\n';
      continue;
    }
    cout << cache[k - 1] << '\n';
  }

  return 0;
}
