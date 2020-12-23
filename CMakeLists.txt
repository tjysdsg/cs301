cmake_minimum_required(VERSION 2.8.2)
project(hw CXX)

set(CMAKE_CXX_STANDARD 14)

# =========== gtest ==========
#configure_file(cmake/CMakeLists.txt.in googletest-download/CMakeLists.txt)
#execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#        RESULT_VARIABLE result
#        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
#if (result)
#    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
#endif ()
#execute_process(COMMAND ${CMAKE_COMMAND} --build .
#        RESULT_VARIABLE result
#        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
#if (result)
#    message(FATAL_ERROR "Build step for googletest failed: ${result}")
#endif ()

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif ()

# ===== google benchmark =====
find_package(benchmark REQUIRED)
# ============================

add_executable(sort sort.cpp)
add_executable(light_board light_board.cpp)
add_executable(genius_voting genius_voting.cpp)
add_executable(pass_most_exams pass_most_exams.cpp)
add_executable(sum_of_three sum_of_three.cpp)
add_executable(ten_integers ten_integers.cpp)
add_executable(contig_prod contig_prod.cpp)
add_executable(set_partition set_partition.cpp)
add_executable(submatrix_w_max_sum submatrix_w_max_sum.cpp)
add_executable(balanced_backpacks balanced_backpacks.cpp)
add_executable(unbounded_knapsack unbounded_knapsack.cpp)
add_executable(sort_iv sort_iv.cpp)
add_executable(max_num_points max_num_points.cpp)
add_executable(max_odd_val max_odd_val.cpp)
add_executable(matrix_game matrix_game.cpp)
add_executable(irrigating_plants irrigating_plants.cpp)
add_executable(avg_path_cost avg_path_cost.cpp)
add_executable(two_knapsack two_knapsack.cpp)

add_executable(hash_map_bench hash_map_bench.cpp)
target_link_libraries(hash_map_bench benchmark::benchmark)
# ============================

# ==== tests ====
add_executable(sort_test sort_test.cpp)
target_link_libraries(sort_test gtest_main)

add_executable(bsearch_test bsearch_test.cpp)
target_link_libraries(bsearch_test gtest_main)

add_executable(map_test map_test.cpp)
target_link_libraries(map_test gtest_main)

add_executable(hash_map_test hash_map_test.cpp)
target_link_libraries(hash_map_test gtest_main)

add_executable(bigint_test bigint_test.cpp)
target_link_libraries(bigint_test gtest_main)

# target_link_libraries(hw1 gtest_main)
# add_test(NAME hw1_test COMMAND hw1)
