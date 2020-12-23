#include "qsort.h"
#include <deque>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::vector;

int main() {
  int n = 0;
  cin >> n;
  vector<int> nums(n, 0);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  qsort(nums.data(), 0, n - 1);
  if (nums.front() == nums.back()) { /// corner case: all the same number
    cout << 1;
    return 0;
  }

  std::deque<int> start_val(1, nums[0]);
  int n_prev = 0;
  int ret = n;
  int curr = nums[0];
  int n_curr = 1;
  for (int i = 1; i <= n; ++i) {
    if (i < n && nums[i] == curr) {
      ++n_curr;
      if (n_curr > n_prev) {
        start_val.push_back(nums[i]);
      }
    } else {
      if (n_prev > n_curr) {
        for (int j = 0; j < n_prev - n_curr; ++j) {
          int start = start_val.front();
          start_val.pop_front();
          ret = std::min(ret, nums[i - 1 - n_curr] - start + 1);
        }
      }
      if (i < n && curr + 1 != nums[i]) {
        int start = start_val.front();
        start_val.pop_front();
        ret = std::min(ret, nums[i - 1] - start + 1);
        start_val.push_back(nums[i]);
      }
      n_prev = n_curr;
      n_curr = 1;
      curr = nums[i];
    }
  }

  int i = n - 1;
  while (!start_val.empty()) {
    ret = std::min(ret, nums[i--] - start_val.front() + 1);
    start_val.pop_front();
  }
  cout << ret;
  return 0;
}
