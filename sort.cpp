#include "heapsort.h"
#include "mergesort.h"
#include "qsort.h"
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

int main() {
  std::ios::sync_with_stdio(false);
  int n = 0;
  cin >> n;
  int *nums = new int[n];
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }

  qsort(nums, 0, n - 1);

  for (int i = 0; i < n; ++i) {
    cout << nums[i];
    if (i != n - 1) {
      cout << ' ';
    }
  }

  return 0;
}
