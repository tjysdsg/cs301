#include <iostream>
#include <vector>
#include <unordered_map>

#define MAX_NUM 1E4

using std::cout;
using std::cin;
using std::vector;

int digit2pow[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int *cache;

inline int get_pow(int n) {
  int orig = n;
  if (cache[n] != 0) { return cache[n]; }
  int ret = 0;
  while (n >= 10) {
    int low = n % 10;
    n = n / 10;
    ret += digit2pow[low];
  }
  ret += digit2pow[n];
  cache[orig] = ret;
  return ret;
}

int main() {
  cache = (int *) calloc(MAX_NUM, sizeof(int));
  std::ios::sync_with_stdio(false);
  int pow = 0;
  cin >> pow;

  int ret = 0;

  pow -= 4; // minus power cost by "+" and "="
  if (pow <= 0) { // not enough power for anything
    cout << 0;
    return 0;
  }

  vector<int> possible_nums;
  possible_nums.reserve(MAX_NUM);
  for (int i = 0; i < MAX_NUM; ++i) {
    if (get_pow(i) < pow) { possible_nums.push_back(i); }
  }

  for (int a : possible_nums) {
    // for (int a = 0; a < MAX_NUM; ++a) {
    int pow_a = get_pow(a);
    if (pow_a >= pow) { continue; }
    // for (int b = 0; b < MAX_NUM; ++b) {
    for (int b : possible_nums) {
      int c = a + b;
      int total_pow = pow_a + get_pow(b) + get_pow(c);
      if (total_pow == pow) {
        ++ret;
        // cout << a << " + " << b << " = " << c << '\n';
      }
    }
  }

  cout << ret;
  return 0;
}
