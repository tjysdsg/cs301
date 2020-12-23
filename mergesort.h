#ifndef __HW__MERGESORT_H__
#define __HW__MERGESORT_H__

#include <vector>
using std::vector;

void merge(int *, int, int, int);
void merge_sort(int *arr, int low, int high) {
  int mid;
  if (low < high) {
    mid = (low + high) / 2;
    merge_sort(arr, low, mid);
    merge_sort(arr, mid + 1, high);
    merge(arr, low, high, mid);
  }
}

void merge(int *arr, int low, int high, int mid) {
  vector<int> c(high - low + 1, 0);
  int i = low, j = mid + 1;
  for (int k = low; k <= high; ++k) {
    if (i <= mid && (j > high || arr[i] <= arr[j])) {
      c[k - low] = arr[i];
      ++i;
    } else {
      c[k - low] = arr[j];
      ++j;
    }
  }
  for (int _i = 0; _i <= high - low; ++_i) {
    arr[low + _i] = c[_i];
  }
}

#endif //__HW__MERGESORT_H__
