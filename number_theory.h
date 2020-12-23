#ifndef __HW__NUMBER_THEORY_H__
#define __HW__NUMBER_THEORY_H__

/// all prime number can be 6k +- 1 except 2 and 3
bool is_prime(int number) {
  if (number == 2 || number == 3)
    return true;

  if (number % 2 == 0 || number % 3 == 0)
    return false;

  int divisor = 6;
  while (divisor * divisor - 2 * divisor + 1 <= number) {
    if (number % (divisor - 1) == 0)
      return false;
    if (number % (divisor + 1) == 0)
      return false;
    divisor += 6;
  }

  return true;
}

int next_prime(int a) {
  while (!is_prime(++a)) {
  }
  return a;
}

inline bool is_odd(int x) { return x & 1; }

#endif //__HW__NUMBER_THEORY_H__
