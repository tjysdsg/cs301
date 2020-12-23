#include "map.h"
#include <gtest/gtest.h>
#include <vector>

using std::vector;

TEST(map_test, generic) {
  Map<int, float> map;
  map.reserve(10);
  for (int i = 10; i >= 0; --i) {
    map.add(i, i * 10.f);
  }

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(map.get(i), i * 10.f);
  }

  /// check order of keys
  auto it = map.begin();
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(it.key(), i);
    EXPECT_EQ(it.value(), i * 10.f);
    ++it;
  }
}

TEST(map_test, upper_bound) {
  Map<size_t, float> map;
  map.reserve(6);
  map.add(5, 5.f);
  map.add(1, 1.f);
  map.add(2, 2.f);
  map.add(10, 10.f);
  map.add(0, 0);

  auto it = map.upper_bound(5);
  EXPECT_EQ(it.key(), 5);
  EXPECT_EQ(it.value(), 5.f);

  it = map.upper_bound(100);
  EXPECT_EQ(it.key(), 10);
  EXPECT_EQ(it.value(), 10.f);

  it = map.upper_bound(3);
  EXPECT_EQ(it.key(), 2);
  EXPECT_EQ(it.value(), 2.f);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
