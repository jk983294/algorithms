#ifndef ALGORITHMS_MAX_SUB_MATRIX_H
#define ALGORITHMS_MAX_SUB_MATRIX_H

#include <climits>
#include <vector>

using namespace std;

/**
 * matrix的值为０或１，求最大子矩阵，该矩阵所有元素都为１
 * cutByLine　为以当前行为底，cutByLine[i]为第i列向上的１的数量
 */

class MaxSubMatrix {
public:
    int process(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) return 0;
        int n = matrix[0].size();
        if (n == 0) return 0;

        int result = 0;
        vector<int> cutByLine(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0)
                    cutByLine[j] = 0;
                else
                    cutByLine[j] += 1;
            }

            result = std::max(result, get_max_sub_area(cutByLine, n));
        }
        return result;
    }

    int get_max_sub_area(vector<int>& data, int n) {
        int maxArea = 0;
        int count = 0;
        int minHeight = INT_MAX;

        for (int i = 0; i < n; ++i) {
            minHeight = std::min(minHeight, data[i]);
            if (data[i] == 0) {
                count = 0;
            } else {
                ++count;
            }
            maxArea = std::max(maxArea, minHeight * count);
        }
        return maxArea;
    }
};

#endif
