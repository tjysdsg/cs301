#ifndef __HW__FLOYD_H__
#define __HW__FLOYD_H__

#include <limits>

constexpr int INT_MAX = std::numeric_limits<int>::max();

void solve(int n_v) {
  // TODO: init 距离矩阵
  int dist[1000][1000];
  // 路径矩阵
  int path[1000][1000]{0};
  // 核心算法
  for (int k = 0; k < n_v; k++) {
    for (int i = 0; i < n_v; i++) {
      for (int j = 0; j < n_v; j++) {
        // 判断如果 ik距离可达且 kj距离可达 且 i和j的距离是否大于
        // i-> k 与 k->j的距离和
        if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
            dist[i][j] > (dist[i][k] + dist[k][j])) {
          path[i][j] = k;
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }
}

#endif //__HW__FLOYD_H__
