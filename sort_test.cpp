#include "qsort.h"
#include <gtest/gtest.h>
#include <random>
#include <vector>

using std::vector;

TEST(qsort_test, random100000) {
  int n = 100000;
  vector<int> arr(n, 0);
  std::random_device rd;
  auto seed = rd();
  std::cout << "Seed: " << seed << '\n';
  std::mt19937 gen(seed);
  std::uniform_int_distribution<> dist(std::numeric_limits<int>::min(),
                                       std::numeric_limits<int>::max());

  for (int i = 0; i < n; ++i) {
    arr[i] = dist(gen);
  }

  qsort(arr.data(), 0, n - 1);

  for (int i = 0; i < n - 1; ++i) {
    EXPECT_LE(arr[i], arr[i + 1]);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
