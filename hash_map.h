#ifndef __HW__HASH_MAP_H__
#define __HW__HASH_MAP_H__

#include "hash.h"
#include "number_theory.h"
#include <limits>
#include <vector>

/**
 * \brief Robin Hood hash map
 */
template <typename K, typename V> class RBHashMap {
public:
  using hash_func_t = size_t (*)(K key);
  RBHashMap() {
    table = std::vector<Node>(13);
    size = 13;
    hash_func = default_hash_func<K>;
  };

  explicit RBHashMap(hash_func_t hf) {
    table = std::vector<Node>(13);
    size = 13;
    hash_func = hf;
  };

#define PSL(node) (node.data & 0xFFFF0000)
#define HAS_VALUE(node) (node.data & 0x0000FFFF)
#define COMBINE_PSL_HAS_VALUE(psl, has_value) ((psl << 2u) | has_value)
#define MAX_TABLE_SIZE (std::numeric_limits<size_t>::max())

  V &operator[](const K &key) { return set_or_add(key); }

  V &set_or_add(K key) {
    size_t psl = 0;
    size_t i = hash_func(key) % size;

    while (i < size) {
      Node &node = table[i];
      if (node.key == key || !HAS_VALUE(node)) { /// found
        node.data = COMBINE_PSL_HAS_VALUE(psl, true);
        node.key = key;
        return node.value;
      } else { /// collision
        if (PSL(node) > psl) {
          // swap rich and poor
          K tmpk = node.key;
          size_t tmppsl = PSL(node);
          node.key = key;
          node.data = COMBINE_PSL_HAS_VALUE(psl, true);
          key = tmpk;
          psl = tmppsl + 1;
          continue;
        }
        ++i;
        ++psl;
      }
    }

    if (size <= MAX_TABLE_SIZE) { /// prevent OOM
      this->resize(next_prime(size * 2));
      return set_or_add(key);
    } else {
      throw "Failed to set/add key or resize";
    }
  }

  V get(const K &key, K default_val = V{}) const {
    size_t psl = 0;
    size_t i = hash_func(key) % size;

    while (i < size) {
      const Node &node = table[i];
      if (!HAS_VALUE(node)) /// not found
        return default_val;
      else if (node.key == key) /// found
        return node.value;
      else { /// collision
        if (PSL(node) > psl)
          break; /// not found
        ++i;
        ++psl;
      }
    }
    return default_val;
  }

  V operator[](const K &key) const { this->get(key); }

  bool find(const K &key) const {
    size_t psl = 0;
    size_t i = hash_func(key) % size;

    while (i < size) {
      const Node &node = table[i];
      if (!HAS_VALUE(node)) /// not found
        return false;
      else if (node.key == key) /// found
        return true;
      else { /// collision
        if (PSL(node) > psl)
          break; /// not found
        ++i;
        ++psl;
      }
    }
    return false;
  }

  void resize(size_t new_size) {
    std::vector<Node> old_table(table);
    table = std::vector<Node>(new_size);
    size_t old_size = size;
    size = new_size;
    for (size_t i = 0; i < old_size; ++i) {
      if (HAS_VALUE(old_table[i]))
        this->set_or_add(old_table[i].key) = old_table[i].value;
    }
  }

protected:
  hash_func_t hash_func = nullptr;

  struct Node {
    uint32_t data = 0;
    K key{};
    V value{};
  };

  std::vector<Node> table;
  size_t size;
};
#endif //__HW__HASH_MAP_H__
