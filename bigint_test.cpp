#include "bigint.h"
#include <gtest/gtest.h>
#include <random>
#include <vector>
using std::vector;
using BI = Bigint<>;

int sign(long long val) {
  int ret = 0;
  if (val > 0)
    ret = 1;
  else if (val < 0)
    ret = -1;
  return ret;
}

TEST(bigint_test, multiplication) {
  {
    auto res = BI(0) * 123;
    EXPECT_EQ(res.sign, 0);
    EXPECT_EQ(res.n_digits, 1);
    EXPECT_EQ(res[0], 0);

    res = BI(123) * 0;
    EXPECT_EQ(res.sign, 0);
    EXPECT_EQ(res.n_digits, 1);
    EXPECT_EQ(res[0], 0);
  }

  { // factorial
    auto res = BI(1);
    for (int i = 2; i < 200; ++i) {
      res = res * i;
    }
  }
}

TEST(bigint_test, division) {
  {
    // 0
    auto res = BI(12345) / 54321;
    EXPECT_EQ(res.sign, 0);
    EXPECT_EQ(res.n_digits, 1);
    EXPECT_EQ(res[0], 0);
  }

  {
    // -100
    auto res = BI(12345) / (-123);
    EXPECT_EQ(res.sign, -1);
    EXPECT_EQ(res.n_digits, 1);
    EXPECT_EQ(res[0], 100);
  }

  {
    // 0
    auto res = BI(0) / (-123);
    EXPECT_EQ(res.sign, 0);
    EXPECT_EQ(res.n_digits, 1);
    EXPECT_EQ(res[0], 0);
  }

  {
    // 1
    auto res = BI(123) / 123;
    EXPECT_EQ(res.sign, 1);
    EXPECT_EQ(res.n_digits, 1);
    EXPECT_EQ(res[0], 1);
  }
}

TEST(bigint_test, sum) {
  {
    auto res = BI(0) + 321;
    EXPECT_EQ(res.sign, 1);
    EXPECT_EQ(res.n_digits, 1);
    EXPECT_EQ(res[0], 321);
  }
}

TEST(bigint_test, minus) {
  {
    auto res = BI(0) - 111;
    EXPECT_EQ(res.sign, -1);
    EXPECT_EQ(res.n_digits, 1);
    EXPECT_EQ(res[0], 111);
  }
}

TEST(bigint_test, to_string) {
  {
    BI bi = 123456789;
    bi = bi * 10000000;
    EXPECT_EQ(bi.to_string(), "1234567890000000");
  }

  {
    BI bi(-123406789);
    bi = bi * 10000000;
    EXPECT_EQ(bi.to_string(), "-1234067890000000");
  }

  {
    BI bi(0);
    EXPECT_EQ(bi.to_string(), "0");
  }
}

TEST(bigint_test, random) {
  std::random_device rd;
  auto seed = rd();
  // auto seed = 2189644416;
  std::cout << "Seed: " << seed << '\n';
  std::mt19937_64 gen(seed);
  auto MAX = (long long)sqrt((double)std::numeric_limits<long long>::max());
  std::uniform_int_distribution<long long> distribution(-MAX, MAX);
  for (size_t i = 0; i < 1000; i++) {
    long long integer1 = distribution(gen);
    long long integer2 = distribution(gen);

    BI big_int1(integer1);
    BI big_int2(integer2);

    long long sum = integer1 + integer2;
    int sum_sign = sign(sum);

    long long sub = integer1 - integer2;
    int sub_sign = sign(sub);

    long long mul = integer1 * integer2;
    int mul_sign = sign(mul);

    long long div = integer1 / integer2;
    int div_sign = sign(div);

#define CHECK(x, y)                                                            \
  EXPECT_EQ((x).to_string(), std::to_string(y));                               \
  EXPECT_EQ((x).sign, y##_sign)

    std::cout << "Testing " << integer1 << " + " << integer2 << " = " << sum
              << '\n';
    CHECK(big_int1 + big_int2, sum);
    CHECK(big_int1 + integer2, sum);
    CHECK(big_int2 + big_int1, sum);

    std::cout << "Testing " << integer1 << " - " << integer2 << " = " << sub
              << '\n';
    CHECK(big_int1 - big_int2, sub);
    CHECK(big_int1 - integer2, sub);

    std::cout << "Testing " << integer1 << " * " << integer2 << " = " << mul
              << '\n';
    // FIXME: wrong result when integer2 is big
    CHECK(big_int1 * integer2, mul);

    std::cout << "Testing " << integer1 << " / " << integer2 << " = " << div
              << '\n';
    // CHECK(big_int1 / integer2, div);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
