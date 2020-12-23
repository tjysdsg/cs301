#include "bsearch.h"
#include <gtest/gtest.h>
#include <vector>

using std::vector;

TEST(bsearch_test, ret_upper_bound1) {
  vector<int> arr{1, 2, 5, 6};
  int i = 0;

  i = bsearch(arr, 7, true);
  EXPECT_EQ(i, 3);

  i = bsearch(arr, 3, true);
  EXPECT_EQ(i, 1);

  i = bsearch(arr, -1, true);
  EXPECT_EQ(i, -1);

  i = bsearch(arr, 4, true);
  EXPECT_EQ(i, 1);
}

TEST(bsearch_test, ret_upper_bound2) {
  vector<int> arr{1, 5};
  int i = bsearch(arr, 2, true);
  EXPECT_EQ(i, 0);
}

TEST(bsearch_test, generic) {
  vector<int> arr{5, 6, 10, 200, 215, 999};
  int i = 0;

  i = bsearch(arr, 10);
  EXPECT_NE(i, -1);

  i = bsearch(arr, 215);
  EXPECT_NE(i, -1);

  i = bsearch(arr, 999);
  EXPECT_NE(i, -1);

  i = bsearch(arr, 5);
  EXPECT_NE(i, -1);

  i = bsearch(arr, 9019);
  EXPECT_EQ(i, -1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
