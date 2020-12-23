#ifndef __HW__BSEARCH_H__
#define __HW__BSEARCH_H__
#include <vector>

template <typename T, typename V>
int bsearch(const std::vector<T> &arr, V val, int lo, int hi,
            bool ret_upper_bound = false) {
  size_t mid = (lo + hi) / 2;
  T p = arr[mid];
  if (p == val) {
    return mid;
  }
  if (lo >= hi) {
    if (ret_upper_bound) {
      if (arr[lo] > val) {
        return lo - 1;
      }
      return lo;
    } else {
      return -1;
    }
  }
  if (p < val) {
    return bsearch<T, V>(arr, val, mid + 1, hi, ret_upper_bound);
  } else {
    return bsearch<T, V>(arr, val, 0, mid - 1, ret_upper_bound);
  }
}

/**
 * \brief Binary search
 * \details Assuming arr is already sorted
 * \tparam T Array element type
 * \tparam V Search value type
 * \param ret_upper_bound Return index of the largest element that is less than
 *      val, if val is not found in arr
 * \return
 *  - Returns the index of the element if found.
 *  - Returns -1 if not found and ret_upper_bound is false.
 *  - Returns the index of the largest element that is less than val,
 *      if not found and ret_upper_bound is true.
 * \note The function will return -1, if all elements are larger than val and
 *      ret_upper_bound is true
 */
template <typename T, typename V>
int bsearch(const std::vector<T> &arr, V val, bool ret_upper_bound = false) {
  int size = arr.size();
  if (size == 0) { /// return -1 even if ret_upper_bound is true
    return -1;
  }
  return bsearch<T, V>(arr, val, 0, size - 1, ret_upper_bound);
}

#endif //__HW__BSEARCH_H__
