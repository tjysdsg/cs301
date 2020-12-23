#ifndef __HW__HASH_H__
#define __HW__HASH_H__

#include <cstddef>
#include <cstdint>

template <typename T> T rotr(T x, unsigned k) {
  return (x >> k) | (x << (8U * sizeof(T) - k));
}

template <typename T> size_t default_hash_func(T x);

template <> size_t default_hash_func<uint64_t>(uint64_t x) {
  // inspired by lemire's strongly universal hashing
  // https://lemire.me/blog/2018/08/15/fast-strongly-universal-64-bit-hashing-everywhere/
  //
  // Instead of shifts, we use rotations so we don't lose any bits.
  //
  // Added a final multiplication with a constant for more mixing. It is most
  // important that the lower bits are well mixed.
  auto h1 = x * UINT64_C(0xA24BAED4963EE407);
  auto h2 = rotr(x, 32U) * UINT64_C(0x9FB21C651E98DF25);
  auto h = rotr(h1 + h2, 32U);
  return static_cast<size_t>(h);
}

#define DEFINE_INT_HASH_FUNC(TYPE)                                             \
  template <> size_t default_hash_func<TYPE>(TYPE x) {                         \
    return default_hash_func(static_cast<uint64_t>(x));                        \
  }

DEFINE_INT_HASH_FUNC(int)

DEFINE_INT_HASH_FUNC(unsigned int)

// https://github.com/aappleby/smhasher/blob/master/src/MurmurHash2.cpp
//-----------------------------------------------------------------------------
// MurmurHash2A, by Austin Appleby

// This is a variant of MurmurHash2 modified to use the Merkle-Damgard
// construction. Bulk speed should be identical to Murmur2, small-key speed
// will be 10%-20% slower due to the added overhead at the end of the hash.

// This variant fixes a minor issue where null keys were more likely to
// collide with each other than expected, and also makes the function
// more amenable to incremental implementations.
#define mmix(h, k)                                                             \
  {                                                                            \
    k *= m;                                                                    \
    k ^= k >> r;                                                               \
    k *= m;                                                                    \
    h *= m;                                                                    \
    h ^= k;                                                                    \
  }

uint32_t MurmurHash2A(const void *key, int len, uint32_t seed) {
  const uint32_t m = 0x5bd1e995;
  const int r = 24;
  uint32_t l = len;

  const auto *data = (const unsigned char *)key;

  uint32_t h = seed;

  while (len >= 4) {
    uint32_t k = *(uint32_t *)data;

    mmix(h, k);

    data += 4;
    len -= 4;
  }

  uint32_t t = 0;

  switch (len) {
  case 3:
    t ^= data[2] << 16u;
  case 2:
    t ^= data[1] << 8u;
  case 1:
    t ^= data[0];
  default:
    break;
  };

  mmix(h, t);
  mmix(h, l);

  h ^= h >> 13u;
  h *= m;
  h ^= h >> 15u;

  return h;
}

#endif //__HW__HASH_H__
