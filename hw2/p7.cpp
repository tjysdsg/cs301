#include <iomanip>
#include <iostream>
#include <vector>
#include "qsort.h"

using std::cin;
using std::cout;
using std::vector;

inline int digits2int(vector<int>::const_iterator first,
                      vector<int>::const_iterator last) {
  int ret = 0;
  while (first < last) {
    ret = ret * 10 + *first;
    ++first;
  }
  return ret;
}

vector<int> int2digits(int val, int size) {
  vector<int> ret(size, 0);
  size_t i = size - 1;
  while (i >= 0 && val > 0) {
    ret[i] = val % 10;
    val /= 10;
    --i;
  }
  return ret;
}

void _get_permutations(const vector<int> &digits, vector<int> curr, size_t pos,
                       int target) {
  int n = digits.size();
  size_t size = curr.size();
  if (pos == size - 1) {
    for (int i = 0; i < n; ++i) {
      curr[pos] = digits[i];
      /// check if current digits are valid
      int denominator = digits2int(curr.begin(), curr.begin() + 5);
      int numerator = denominator * target;
      vector<int> all_digits(curr);
      if (numerator > 99999) { // FIXME: calculate 10^size - 1
        continue;
      }
      auto denom_digits = int2digits(numerator, size);
      all_digits.insert(all_digits.end(), denom_digits.begin(),
                        denom_digits.end());
      /// check for duplicated digits
      qsort(all_digits.data(), 0, size * 2 - 1);
      bool valid = true;
      for (int j = 0; j < all_digits.size() - 1; ++j) {
        if (all_digits[j] == all_digits[j + 1]) {
          valid = false;
          break;
        }
      }
      /// print
      if (valid) {
        cout << std::setfill('0') << std::setw(size);
        cout << numerator << " / ";
        cout << std::setfill('0') << std::setw(size);
        cout << denominator;
        cout << " = " << target << '\n';
      }
    }
  } else {
    for (int i = 0; i < n; ++i) {
      vector<int> tmp(digits);
      curr[pos] = digits[i];
      tmp.erase(tmp.begin() + i);
      _get_permutations(tmp, curr, pos + 1, target);
    }
  }
}

void get_permutations(const vector<int> &digits, size_t size, int target) {
  vector<int> init(size, 0);
  _get_permutations(digits, init, 0, target);
}

int main() {
  int n = 0;
  cin >> n;
  vector<int> digits{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  get_permutations(digits, 5, n);
  return 0;
}
