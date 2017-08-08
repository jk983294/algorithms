#include <iostream>

using namespace std;

/**
 * 使用动态规划计算矩阵连乘的最佳乘法顺序
 */

static const int MaxN = 100;

class MatrixMultiple {
public:
    int m[MaxN][MaxN];  // 记录最少乘法数
    int s[MaxN][MaxN];  // 记录断开位置
    vector<int> dimensionX;
    vector<int> dimensionY;
    size_t n;

public:
    void set(vector<int> dX, vector<int> dY) {
        dimensionX = dX;
        dimensionY = dY;
        n = dimensionX.size();
    }
    int recursive_m(size_t i, size_t j) {
        int min = 999999999;
        int minIndex = 0;
        int multipleTimes = 0;
        if (m[i][j] != -1)
            return m[i][j];
        else {
            for (size_t k = i; k < j; k++) {
                multipleTimes =
                    recursive_m(i, k) + recursive_m(k + 1, j) + dimensionX[i] * dimensionY[k] * dimensionY[j];

                if (multipleTimes < min) {
                    min = multipleTimes;
                    minIndex = k;
                }
            }
            m[i][j] = min;
            s[i][j] = minIndex;
            return min;
        }
    }

    // n个矩阵，每个矩阵的维数放在数组中
    int multiple() {
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                m[i][j] = -1;
                s[i][j] = -1;
            }
        }
        for (size_t i = 0; i < n; i++) m[i][i] = 0;
        recursive_m(0, n - 1);
        return m[0][n - 1];
    }

    void print_result() {
        cout << m[0][n - 1] << endl;
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                cout << m[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl << "path:  " << endl;
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                cout << s[i][j] << " ";
            }
            cout << endl;
        }
    }
};
