#include "hash_map.h"
#include "qsort.h"
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

RBHashMap<int, std::pair<int, int>> dp;
int n = 0;
int m = 0;
int k = 0;
int ret = 0;

#define dist(x) (std::abs(x - nums[pivot]))

void F(const vector<int> &nums, int pivot) {
  int r = pivot + 1;
  int l = 0;
  if (pivot > 0) {
    auto p = dp[pivot - 1];
    l = p.first;
    r = p.second;
    int n_l = pivot - l;
    int n_r = r - pivot + 1;
    int d = nums[pivot] - nums[pivot - 1];
    ++l;

    int s = r - l + 1 - 1;
    int diff = n_l * d - n_r * d;
    while (r < n) {
      if (dist(nums[l - 1]) < dist(nums[r]) + diff) {
        --r;
        break;
      }
      ++s;
      ++r;
      ret = std::max(ret, s);
    }
    dp[pivot] = {l, r};
    return;
  }

  int sum = 0;
  while (r < n) {
    int rdist = std::abs(nums[r] - nums[pivot]);
    if (sum + rdist > k)
      break;
    sum += rdist;
    ++r;
  }
  dp[pivot] = {l, r - 1};
}

int main() {
  cin >> n >> m >> k;
  vector<int> nums(n, 0);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  qsort(nums.data(), 0, n - 1);

  for (int i = 0; i < n; ++i) {
    F(nums, i);
  }
  cout << ret;
  return 0;
}
