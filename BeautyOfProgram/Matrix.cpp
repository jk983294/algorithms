#include "MyUtility.h"

void transpose_square_matrix(vector<int> &matrix, int n);

void transpose(vector<int> &matrix, int row, int column);

void rotate(vector<int> &matrix, int n);

void rotate(vector<int> &matrix, int row, int column);

int main() {
    vector<int> m1{1, 2, 3, 4};
    transpose_square_matrix(m1, 2);
    cout << "transpose_square_matrix: " << m1 << endl;
    m1 = {1, 2, 3, 4};
    rotate(m1, 2);
    cout << "rotate: " << m1 << endl;

    vector<int> m2{1, 2, 3, 4, 5, 6};
    transpose(m2, 2, 3);
    cout << "transpose: " << m2 << endl;
    m2 = {1, 2, 3, 4, 5, 6};
    rotate(m2, 2, 3);
    cout << "rotate: " << m2 << endl;
    return 0;
}

/**
 * do matrix transpose, then reverse the elements for each row
 */
void rotate(vector<int> &matrix, int n) {
    transpose_square_matrix(matrix, n);
    for (int i = 0; i < n; ++i) {
        reverse(matrix.begin() + i * n, matrix.begin() + (i + 1) * n);
    }
}

/**
 * do matrix transpose, then reverse the elements for each row
 * after transpose, <row, column> change to <column, row>
 */
void rotate(vector<int> &matrix, int row, int column) {
    transpose(matrix, row, column);
    for (int i = 0; i < column; ++i) {
        reverse(matrix.begin() + i * row, matrix.begin() + (i + 1) * row);
    }
}

void transpose_square_matrix(vector<int> &matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            std::swap(matrix[i * n + j], matrix[j * n + i]);
        }
    }
}

/**
 * https://en.wikipedia.org/wiki/In-place_matrix_transposition
 */
void transpose(vector<int> &matrix, int row, int column) {
    for (int i = 0; i < row * column; i++) {
        int targetPos = (i + (row * column - 1) * (i % row)) / row;
        while (targetPos < i) {
            targetPos = (targetPos + (row * column - 1) * (targetPos % row)) / row;
        }
        cout << "transpose swap " << i << " " << targetPos << endl;
        std::swap(matrix[i], matrix[targetPos]);
    }
}
