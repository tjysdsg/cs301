#include "qsort.h"
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct Pair {
  int a = 0;
  int b = 0;
};

int cmp(const Pair &p1, const Pair &p2) {
  if (p1.a < p2.a)
    return -1;
  else if (p1.a > p2.a)
    return 1;

  if (p1.b < p2.b)
    return -1;
  else if (p1.b > p2.b)
    return 1;
  return 0;
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);

  int n = 0;
  cin >> n;
  vector<Pair> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i].a >> nums[i].b;
  }
  qsort(nums.data(), 0, n - 1, cmp);
  int curr_a = nums[0].a;
  cout << nums[0].b;
  for (int i = 1; i < n; ++i) {
    if (nums[i].a != curr_a) {
      cout << '\n';
      curr_a = nums[i].a;
    } else
      cout << ' ';
    cout << nums[i].b;
  }
  return 0;
}
