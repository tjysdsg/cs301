#include <iostream>
#include <limits>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

using Mat = vector<vector<int8_t>>;

int n = 0;

int max_submat(const Mat &mat) {
  /*
   * S[i][j] stores sum of sub-matrix formed by row 0 to i-1 and column 0 to
   * j-1
   */
  int S[n + 1][n + 1];

  // pre-process the matrix to fill S[][]
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      if (i == 0 || j == 0)
        S[i][j] = 0;
      else
        S[i][j] =
            S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1] + mat[i - 1][j - 1];
    }
  }

  int ret = std::numeric_limits<int>::min();

  // consider every sub-matrix formed by row i to j
  // and column m to n
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      for (int m = 0; m < n; m++) {
        for (int _n = m; _n < n; _n++) {
          // calculate submatrix sum using S[][] in O(1) time
          int submatrix_sum =
              S[j + 1][_n + 1] - S[j + 1][m] - S[i][_n + 1] + S[i][m];

          if (submatrix_sum > ret)
            ret = submatrix_sum;
        }
      }
    }
  }
  return ret;
}

int main() {
  cin >> n;
  int tmp;
  Mat mat(n, vector<int8_t>(n, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> tmp;
      mat[i][j] = tmp;
      // scanf("%hhd", &mat[i][j]); not portable
    }
  }

  cout << max_submat(mat);
  return 0;
}
