#include "hash.h"
#include "hash_map.h"
#include <algorithm>
#include <chrono>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <vector>

using std::vector;

template <typename M> void find_test(M map) {
  vector<int> nums{1, 3, 999, 6, 21};
  vector<int> not_in{2, 100, 69, 77};
  for (const auto &i : nums) {
    map[i] = i;
  }
  for (const auto &i : nums) {
    EXPECT_EQ(map[i], i);
  }
  for (const auto &i : nums) {
    EXPECT_TRUE(map.find(i));
  }
  for (const auto &i : not_in) {
    EXPECT_FALSE(map.find(i));
  }
}

template <typename M> void get_test(M map) {
  vector<int> nums{1, 3, 999, 6, 21};
  vector<int> not_in{2, 100, 69, 77};
  for (const auto &i : nums) {
    map[i] = i;
  }
  for (const auto &i : nums) {
    EXPECT_EQ(map[i], i);
  }
  for (const auto &i : nums) {
    EXPECT_EQ(map.get(i), i);
  }
  for (const auto &i : not_in) {
    EXPECT_EQ(map.get(i, -1), -1);
  }
}

template <typename M> void generic_test(M map) {
  vector<int> nums{};
  size_t n = 1'000'000;
  nums.reserve(n);

  std::random_device rd;
  auto seed = rd();
  std::cout << "Seed = " << seed << '\n';
  std::mt19937 gen(seed);
  std::uniform_int_distribution<> distrib(-1E9, 1E9);

  /// new values
  for (size_t i = 0; i < n; i++) {
    int val = distrib(gen);
    map[val] = val;
  }

  for (const auto &i : nums) {
    EXPECT_EQ(map[i], i);
  }

  /// reassignment
  for (const auto &i : nums) {
    map[i] = i * 3.f;
  }

  for (const auto &i : nums) {
    EXPECT_EQ(map[i], i * 3.f);
  }
}

TEST(RBHashMap, generic) {
  RBHashMap<int, int> map;
  generic_test(map);
}

TEST(RBHashMap, find) {
  RBHashMap<int, int> map;
  find_test(map);
}

TEST(RBHashMap, get) {
  RBHashMap<int, int> map;
  get_test(map);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
