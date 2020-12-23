#include <cmath>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

#define INVALID_VALUE -1E9 - 1
#define PRIME 999991
#define TABLE_SIZE 20000003

vector<int> table(TABLE_SIZE, INVALID_VALUE);

int hash(int key, int i) {
  int h1 = key % TABLE_SIZE;
  int h2 = PRIME - (key % PRIME);
  int address = (h1 + i * h2) % TABLE_SIZE;
  return std::abs(address);
}

bool find(int key) {
  int n_prob = 0;
  while (table[hash(key, n_prob)] != INVALID_VALUE) {
    if (table[hash(key, n_prob)] == key)
      return true;
    else
      ++n_prob;
  }
  return false;
}

void insert(vector<int> &L, int key) {
  int round = 0;

  while (true) {
    int address = hash(key, round);
    if (L[address] == INVALID_VALUE) {
      L[address] = key;
      break;
    } else if (L[address] == key) {
      break;
    } else {
      round++;
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  int n = 0;
  cin >> n;
  vector<int> nums;
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    int num = 0;
    cin >> num;
    nums.push_back(num);

    for (int j = 0; j < i; ++j) {
      if (find(nums[i] - nums[j])) {
        ++ret;
        break;
      }
    }

    for (int j = 0; j <= i; ++j) {
      int sum = nums[j] + nums[i];
      insert(table, sum);
    }
  }

  cout << ret;
  return 0;
}
