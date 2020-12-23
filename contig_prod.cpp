#include "bigint.h"
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
  int c1 = p1.a * p1.b;
  int c2 = p2.a * p2.b;

  if (c1 < c2)
    return -1;
  else if (c1 > c2)
    return 1;

  if (p1.b < p2.b)
    return -1;
  else if (p1.b > p2.b)
    return 1;
  return 0;
}

int main() {
  int n;
  cin >> n;
  vector<Pair> pairs(n + 1);
  for (int i = 0; i <= n; ++i) {
    cin >> pairs[i].a >> pairs[i].b;
  }
  Bigint ret(0);
  qsort(pairs.data(), 1, n, cmp);
  Bigint prod(1);
  for (int i = 0; i < n; ++i) {
    prod = prod * pairs[i].a;
    Bigint s = prod / pairs[i + 1].b;
    if (s > ret)
      ret = s;
  }
  cout << ret;
  return 0;
}
