#include <benchmark/benchmark.h>
#include "hash_map.h"
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <random>

using std::cin;
using std::cout;
using std::endl;
using std::hash;
using std::ios;
using std::pair;
using std::string;
using std::unordered_map;
using std::vector;

using namespace __gnu_pbds;

// typedef cc_hash_table<int, int, hash<int>> ht;
// typedef cc_hash_table<
//     int, int, hash<int>, equal_to<int>, direct_mask_range_hashing<int>,
//     hash_standard_resize_policy<hash_exponential_size_policy<>,
//     hash_load_check_resize_trigger<true>, true>> ht;
typedef gp_hash_table<int, int, hash<int>> pb_map;
using umap = unordered_map<int, int>;
using mymap = RBHashMap<int, int>;

#define map_test(init, name)                                                   \
  static void insert_1M_int_##name(benchmark::State &state) {                  \
    for (auto _ : state) {                                                     \
      state.PauseTiming();                                                     \
      std::random_device rd;                                                   \
      std::mt19937_64 gen(rd());                                               \
      std::uniform_int_distribution<> distrib(INT_MIN, INT_MAX);               \
      constexpr size_t n = 100'000'000;                                        \
      vector<int> input(n, 0);                                                 \
      for (size_t i = 0; i < n; ++i) {                                         \
        input[i] = distrib(gen);                                               \
      }                                                                        \
      state.ResumeTiming();                                                    \
                                                                               \
      init;                                                                    \
      for (size_t i = 0; i < n; ++i) {                                         \
        map[static_cast<int>(input[i])] = 1;                                   \
      }                                                                        \
    }                                                                          \
  }                                                                            \
  BENCHMARK(insert_1M_int_##name)

map_test(pb_map map, pb_map);
map_test(umap map, umap);
map_test(mymap map, HashMap);

BENCHMARK_MAIN();
