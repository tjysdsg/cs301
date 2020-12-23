#ifndef __HW__QSORT_H__
#define __HW__QSORT_H__

namespace impl {

template <typename T> inline void swap(T *a, T *b) {
  T tmp = *a;
  *a = *b;
  *b = tmp;
}

template <typename T> int partition(T *arr, int lo, int hi) {
  int pivot = lo;
  int i = lo;
  int j = hi + 1;
  T val = arr[pivot];
  while (true) {
    while (arr[++i] < val) {
      if (i == hi) {
        break;
      }
    }
    while (arr[--j] > val) {
      if (j == lo) {
        break;
      }
    }
    if (i >= j) {
      break;
    }
    swap<T>(&arr[i], &arr[j]);
  }
  swap<T>(&arr[pivot], &arr[j]);
  return j;
}

} // namespace impl

/**
 * \brief quick sort
 * \note Requires operator> and operator<
 * */
template <typename T> void qsort(T *arr, int lo, int hi) {
  if (lo < hi) {
    int p = impl::partition<T>(arr, lo, hi);
    qsort<T>(arr, lo, p - 1);
    qsort<T>(arr, p + 1, hi);
  }
}

#endif //__HW__QSORT_H__
