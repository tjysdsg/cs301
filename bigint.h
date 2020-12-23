#ifndef __HW__BIGINT_H__
#define __HW__BIGINT_H__
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using std::ostream;
using std::vector;

template <size_t MAX_N_DIGITS = 1000, size_t base = 1000,
          size_t n_zeros_per_digit = 3>
class Bigint {
public:
  using BI = Bigint<MAX_N_DIGITS, base, n_zeros_per_digit>;

private:
  /// in reverse order, i.e. 1234 -> [4, 3, 2, 1]
  vector<unsigned long long> digits =
      vector<unsigned long long>(MAX_N_DIGITS, 0);

  /// shrink n_digits, check if 0
  void calibrate() {
    int i;
    for (i = n_digits - 1; i >= 0 && digits[i] == 0; --i) {
    }
    n_digits = i + 1;
    if (n_digits == 1 && digits[0] == 0) {
      sign = 0;
    }
  }

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
      digits[i] = (int)(val % base);
      val /= base;
      ++i;
      ++n_digits;
    }
  }
  Bigint(const Bigint &b) = default;

  int operator[](size_t idx) const { return digits[idx]; }

  /// sum
  BI operator+(long long b) const { return this->operator+(BI(b)); }

  BI operator+(BI b) const {
    BI ret(*this);
    if (ret.sign == 0)
      return b;
    if (b.sign == 0)
      return ret;

    if (-1 == b.sign && -1 != ret.sign) {
      b.sign = -b.sign;
      return ret - b;
    }

    if (-1 == ret.sign && -1 != b.sign) {
      ret.sign = -ret.sign;
      return b - ret;
    }

    ret = abs_plus(ret, b);
    return ret;
  }

  /// subtraction
  BI operator-(long long val) const { return this->operator-(BI(val)); }

  BI operator-(BI b) const {
    BI a(*this);
    if (a.sign == 0) {
      b.sign = -b.sign;
      return b;
    }
    if (b.sign == 0)
      return a;

    if (a == b) {
      a = BI(0);
      return a;
    }

    // check signs
    if (-1 == b.sign && -1 != a.sign) {
      b.sign = 1;
      return abs_plus(a, b);
    }

    if (-1 == a.sign && -1 != b.sign) {
      b.sign = -1;
      return abs_plus(b, a);
    }

    if (this->abs_lt(b)) {
      BI ret = BI::abs_minus(b, a);
      ret.sign = -ret.sign;
      return ret;
    }
    return BI::abs_minus(a, b);
  }

  static BI abs_minus(const BI &a, const BI &b) {
    BI ret(a);
    int borrow = 0;
    for (int i = 0; i < ret.n_digits; ++i) {
      borrow = ret.digits[i] - borrow;
      if (i < b.n_digits)
        borrow -= b.digits[i];
      ret.digits[i] = (borrow + base) % base;
      if (borrow < 0)
        borrow = 1;
      else
        borrow = 0;
    }

    ret.calibrate();
    return ret;
  }

  static BI abs_plus(const BI &a, const BI &b) {
    BI ret(a);
    int flag = 0;
    int i = 0;
    while (i < ret.n_digits || i < b.n_digits) {
      int val = b.digits[i];
      val += ret.digits[i] + flag;
      flag = val / base;
      val %= base;
      ret.digits[i] = val;
      ++i;
    }

    if (flag)
      ret.digits[i++] = flag;

    ret.n_digits = i;
    return ret;
  }

  /// multiplication
  BI operator*(long long b) {
    if (0 == sign || 0 == b)
      return BI(0);
    BI ret;
    ret.sign = sign * (b >= 0 ? 1 : -1);
    b = std::abs(b);
    {
      BI op(b);
      for (int i = 0; i < n_digits; ++i) {
        for (int j = 0; j < n_digits; ++j) {
          ret.digits[i + j] += digits[i] * op.digits[j];
        }
      }
      for (int k = 1; k <= n_digits + op.n_digits; ++k) {
        ret.digits[k] += ret.digits[k - 1] / base;
        ret.digits[k - 1] %= base;
      }
      ret.n_digits = n_digits + op.n_digits;
    }

    ret.calibrate();
    return ret;
  }

  /// div
  BI operator/(long long b) {
    if (BI(b) > *this || 0 == b || sign == 0)
      return BI(0);
    BI ret;
    ret.sign = sign * (b >= 0 ? 1 : -1);
    b = std::abs(b);
    ret.n_digits = n_digits;

    int r = 0;
    for (int i = n_digits - 1; i >= 0; --i) {
      r = r * base + digits[i];
      ret.digits[i] = r / b;
      r %= b;
    }

    ret.calibrate();
    return ret;
  }

  /// compare
  // bool operator<(const BI &) const;
  bool operator>(const BI &op) const {
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
    // TODO: negative number
    return false;
  }
  // bool operator<=(const BI &) const;
  // bool operator>=(const BI &) const;
  bool operator==(const BI &op) const {
    if (n_digits != op.n_digits || sign != op.sign)
      return false;

    for (int i = n_digits - 1; i >= 0; --i) {
      if (digits[i] != op.digits[i])
        return false;
    }
    return true;
  }
  // bool operator!=(const BI &) const;

  std::string to_string() const {
    std::ostringstream ret;
    if (sign == -1)
      ret << "-";
    for (int i = n_digits - 1; i >= 0; --i) {
      if (i != n_digits - 1)
        ret << std::setw(n_zeros_per_digit) << std::setfill('0');
      ret << std::to_string(digits[i]);
    }
    return ret.str();
  }

  bool is_odd() const {
    if (sign == 0)
      return true;
    return digits[0] % 2;
  }

  bool abs_gt(const BI &op) const {
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

  bool abs_lt(const BI &op) const {
    if (n_digits < op.n_digits)
      return true;
    else if (n_digits > op.n_digits)
      return false;

    for (int i = n_digits - 1; i >= 0; --i) {
      if (digits[i] < op.digits[i])
        return true;
      else if (digits[i] > op.digits[i])
        return false;
    }
    return false;
  }
};

template <size_t MAX_N_DIGITS, size_t base, size_t n_zeros_per_digit>
bool bigint_cmp(const Bigint<MAX_N_DIGITS, base, n_zeros_per_digit> &a,
                const Bigint<MAX_N_DIGITS, base, n_zeros_per_digit> &b) {
  return b > a;
}

#endif //__HW__BIGINT_H__
