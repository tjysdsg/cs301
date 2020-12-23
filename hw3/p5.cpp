#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using std::ostream;
using std::vector;
class Bigint {
public:
  static constexpr int MAX_N_DIGITS = 10000;
  static constexpr int base = 100000;
  static constexpr int n_zeros_per_digit = 5;

private:
  vector<int> digits = vector<int>(MAX_N_DIGITS, 0);

public:
  int sign = 1;
  int n_digits = 0;

public:
  Bigint() = default;
  Bigint(long long val) {
    if (!val) {
      sign = 0;
      n_digits = 1;
      return;
    }
    sign = val >= 0 ? 1 : -1;
    val = std::abs(val);
    int i = 0;
    while (val) {
      digits[i] = (int)(val % Bigint::base);
      val /= Bigint::base;
      ++i;
      ++n_digits;
    }
  }
  Bigint(const Bigint &b) = default;
  int operator[](size_t idx) const { return digits[idx]; }
  Bigint operator*(long long b) {
    if (0 == sign || 0 == b)
      return Bigint(0);
    Bigint ret;
    ret.sign = sign * (b >= 0 ? 1 : -1);
    b = std::abs(b);
    {
      Bigint op(b);
      for (int i = 0; i < n_digits; ++i) {
        for (int j = 0; j < n_digits; ++j) {
          ret.digits[i + j] += digits[i] * op.digits[j];
        }
      }
      for (int k = 1; k <= n_digits + op.n_digits; ++k) {
        ret.digits[k] += ret.digits[k - 1] / Bigint::base;
        ret.digits[k - 1] %= Bigint::base;
      }
      ret.n_digits = n_digits + op.n_digits;
    }
    while (ret.digits[ret.n_digits - 1] == 0 && ret.n_digits > 0)
      --ret.n_digits;
    return ret;
  }
  Bigint operator/(long long b) {
    if (Bigint(b) > *this || 0 == b || sign == 0)
      return Bigint(0);
    Bigint ret;
    ret.sign = sign * (b >= 0 ? 1 : -1);
    b = std::abs(b);
    ret.n_digits = n_digits;
    int r = 0;
    for (int i = n_digits - 1; i >= 0; --i) {
      r = r * Bigint::base + digits[i];
      ret.digits[i] = r / b;
      r %= b;
    }
    while (ret.digits[ret.n_digits - 1] == 0 && ret.n_digits > 0)
      --ret.n_digits;
    return ret;
  }
  bool operator>(const Bigint &op) const {
    if (n_digits > op.n_digits)
      return true;
    else if (n_digits < op.n_digits)
      return false;
    for (int i = n_digits - 1; i >= 0; --i) {
      if (digits[i] > op.digits[i])
        return true;
      else if (digits[i] < op.digits[i])
        return false;
    }
    return false;
  }
  std::string to_string() const {
    std::ostringstream ret;
    for (int i = n_digits - 1; i >= 0; --i) {
      if (i != n_digits - 1)
        ret << std::setw(Bigint::n_zeros_per_digit) << std::setfill('0');
      ret << std::to_string(digits[i]);
    }
    return ret.str();
  }
  friend ostream &operator<<(ostream &out, const Bigint &bi);
};
ostream &operator<<(ostream &out, const Bigint &bi) {
  std::cout << bi.to_string();
  return out;
}
namespace impl {
template <typename T> inline void swap(T *a, T *b) {
  T tmp = *a;
  *a = *b;
  *b = tmp;
}
template <typename T>
int partition(T *arr, int lo, int hi, int (*cmp)(const T &, const T &)) {
  int pivot = lo;
  int i = lo;
  int j = hi + 1;
  T val = arr[pivot];
  while (true) {
    while (-1 == cmp(arr[++i], val)) {
      if (i == hi)
        break;
    }
    while (-1 == cmp(val, arr[--j])) {
      if (j == lo)
        break;
    }
    if (i >= j) {
      break;
    }
    swap<T>(&arr[i], &arr[j]);
  }
  swap<T>(&arr[pivot], &arr[j]);
  return j;
}
template <typename T> int default_cmp(const T &a, const T &b) {
  if (a > b)
    return 1;
  else if (a < b)
    return -1;
  else
    return 0;
}
} // namespace impl
template <typename T>
void qsort(T *arr, int lo, int hi,
           int (*cmp)(const T &, const T &) = impl::default_cmp) {
  if (lo < hi) {
    int p = impl::partition<T>(arr, lo, hi, cmp);
    qsort<T>(arr, lo, p - 1, cmp);
    qsort<T>(arr, p + 1, hi, cmp);
  }
}
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
