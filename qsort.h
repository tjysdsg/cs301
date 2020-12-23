#ifndef __HW__QSORT_H__
#define __HW__QSORT_H__

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

/**
 * \brief quick sort
 * \note Requires operator> and operator<
 * */
template <typename T>
void qsort(T *arr, int lo, int hi,
           int (*cmp)(const T &, const T &) = impl::default_cmp) {
  if (lo < hi) {
    int p = impl::partition<T>(arr, lo, hi, cmp);
    qsort<T>(arr, lo, p - 1, cmp);
    qsort<T>(arr, p + 1, hi, cmp);
  }
}

#endif //__HW__QSORT_H__
