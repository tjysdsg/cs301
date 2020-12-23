#include <iostream>
using std::cin;
using std::cout;

inline unsigned largest_pow_of_2(unsigned x) {
  x |= x >> 1u;
  x |= x >> 2u;
  x |= x >> 4u;
  x |= x >> 8u;
  x |= x >> 16u;
  return x ^ (x >> 1u);
}

int main() {
  unsigned v = 0;
  cin >> v;
  cout << largest_pow_of_2(v);
  return 0;
}
