#ifndef ALGORITHMS_MIN_SUM_PATH_OF_MATRIX_H
#define ALGORITHMS_MIN_SUM_PATH_OF_MATRIX_H

#include <vector>

using namespace std;

class MinSumPath {
public:
    int process(const vector<vector<int>>& matrix) {
        int m = static_cast<int>(matrix.size());
        if (m == 0) return 0;
        int n = static_cast<int>(matrix.size());
        vector<vector<int>> result;
        result.resize(m);
        for (int i = 0; i < m; ++i) {
            result[i].resize(n, 0);
        }
        result[0][0] = matrix[0][0];
        for (int i = 1; i < m; ++i) {
            result[i][0] = result[i - 1][0] + matrix[i][0];
        }
        for (int i = 1; i < n; ++i) {
            result[0][i] = result[0][i - 1] + matrix[0][i];
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                result[i][j] = std::min(result[i - 1][j], result[i][j - 1]) + matrix[i][j];
            }
        }
        return result[m - 1][n - 1];
    }
};

#endif
