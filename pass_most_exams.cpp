#include "qsort.h"
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct Exam {
  int time = 0;
  int prep = 0;

  bool operator<(const Exam &other) const { return this->time < other.time; }
  bool operator>(const Exam &other) const { return this->time > other.time; }
};

int argmax(const size_t *vec, size_t start, size_t end) {
  size_t ret = 0;
  for (int i = start; i < end; ++i) {
    if (vec[ret] < vec[i]) {
      ret = i;
    }
  }
  return ret;
}

int main() {
  std::ios::sync_with_stdio(false);
  int n = 0;
  cin >> n;
  vector<Exam> exams(n);
  for (int i = 0; i < n; ++i) {
    cin >> exams[i].time;
  }
  for (int i = 0; i < n; ++i) {
    cin >> exams[i].prep;
  }
  qsort(exams.data(), 0, n - 1);
  size_t max_passed = 0;
  size_t time = 0;
  vector<size_t> prepared(n, 0);
  for (int i = 0; i < n; ++i) {
    int ddl = exams[i].time;
    int prep = exams[i].prep;
    int max_i = argmax(prepared.data(), 0, max_passed);
    int max = prepared[max_i];
    if (ddl - prep > time) {
      prepared[max_passed++] = prep;
      time = time + prep + 1;
    } else if (max > prep) {
      time = time - max + prep;
      prepared[max_i] = prep;
    }
  }

  cout << max_passed;
  return 0;
}
