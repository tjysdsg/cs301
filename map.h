#ifndef __HW__MAP_H__
#define __HW__MAP_H__
#include "bsearch.h"
#include <algorithm>
#include <vector>

/**
 * \brief Ordered map
 * \details Doesn't make sure key is not duplicated if using Map::add()
 * \tparam K key type
 * \tparam V value type
 */
template <typename K, typename V> class Map {
public:
  class Iterator {
  public:
    Iterator() = delete;
    Iterator(const Iterator &) = default;
    Iterator &operator=(const Iterator &) = default;
    Iterator(Map &_parent, size_t _key_i) : parent(&_parent), key_i(_key_i) {}
    K key() const { return parent->keys[key_i].key; }
    V value() const { return parent->values[parent->keys[key_i].idx]; }

    bool is_valid() const { return key_i >= 0 && key_i < parent->keys.size(); }

    Iterator operator+(size_t i) {
      Iterator ret(*this);
      ret.key_i += i;
      return ret;
    }

    Iterator operator-(size_t i) {
      Iterator ret(*this);
      ret.key_i -= i;
      return ret;
    }

    Iterator &operator+=(size_t i) {
      key_i += i;
      return *this;
    }

    Iterator &operator-=(size_t i) {
      key_i -= i;
      return *this;
    }

    Iterator &operator++() {
      ++key_i;
      return *this;
    }

    Iterator operator++(int) {
      Iterator ret(*this);
      ++key_i;
      return ret;
    }

    Iterator &operator--() {
      --key_i;
      return *this;
    }

    Iterator operator--(int) {
      Iterator ret(*this);
      --key_i;
      return std::move(ret);
    }

    bool operator==(const Iterator &other) const {
      return key_i == other.key_i;
    }
    bool operator!=(const Iterator &other) const {
      return key_i != other.key_i;
    }

    bool operator<(const Iterator &other) const { return key_i < other.key_i; }
    bool operator<=(const Iterator &other) const {
      return key_i <= other.key_i;
    }
    bool operator>(const Iterator &other) const { return key_i > other.key_i; }
    bool operator>=(const Iterator &other) const {
      return key_i >= other.key_i;
    }

  protected:
    Map *parent;
    size_t key_i = 0;
  };

  V get(const K &key) const {
    auto query = std::find(keys.begin(), keys.end(), key);
    if (query != keys.end()) {
      return values[query->idx];
    }
    return V();
  }

  // bool set(const K &key, const V &val) {
  //   auto query = std::find(keys.begin(), keys.end(), key);
  //   if (query != keys.end()) {
  //     values[query->idx] = val;
  //     return true;
  //   } else {
  //     return false;
  //   }
  // }

  void add(const K &key, const V &val) {
    _Key new_key(key, values.size());
    if (keys.empty()) {
      keys.push_back(new_key);
    } else {
      int idx = bsearch<_Key, K>(keys, key, true);
      keys.insert(keys.begin() + idx + 1, new_key);
    }
    values.push_back(val);
  }

  /**
   * \brief Return iterator to the key-value pair that is less than or equal to
   *    key
   */
  Iterator upper_bound(const K &key) {
    int idx = bsearch<_Key, K>(keys, key, true);
    return Iterator(*this, idx);
  }

  Iterator begin() { return Iterator(*this, 0); }
  Iterator end() { return Iterator(*this, keys.size()); }

  void reserve(size_t size) {
    keys.reserve(size);
    values.reserve(size);
  }

protected:
  class _Key {
  public:
    K key{};
    size_t idx{};

    _Key(const K &_key, size_t _idx) : key(_key), idx(_idx) {}

    bool operator<(const _Key &other) const { return key < other.key; }
    bool operator>(const _Key &other) const { return key > other.key; }
    bool operator==(const _Key &other) const { return key == other.key; }

    bool operator<(const K &other) const { return key < other; }
    bool operator>(const K &other) const { return key > other; }
    bool operator==(const K &other) const { return key == other; }
  };

  std::vector<_Key> keys{};
  std::vector<V> values{};
};

#endif //__HW__MAP_H__
