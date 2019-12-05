#ifndef BEAUTY_ALGEBRA_H
#define BEAUTY_ALGEBRA_H

#include "MyUtility.h"

inline vector<vector<double>> matrix_multi(const vector<vector<double>>& A, const vector<vector<double>>& vs);
inline vector<vector<double>> transpose(const vector<vector<double>>& A);
inline double l2_norm(const vector<double>& a, const vector<double>& b);

inline vector<vector<double>> matrix_multi(const vector<vector<double>>& A, const vector<vector<double>>& vs) {
    size_t k = A.size(), d = A[0].size(), l = vs[0].size();
    vector<vector<double>> ret;
    ret.resize(k);
    for (size_t i = 0; i < k; ++i) {
        ret[i].resize(l);
        for (size_t j = 0; j < l; ++j) {
            double sum = 0.0;
            for (size_t m = 0; m < d; ++m) {
                sum += A[i][m] * vs[m][j];
            }
            ret[i][j] = sum;
        }
    }
    return ret;
}

inline vector<vector<double>> transpose(const vector<vector<double>>& A) {
    size_t k = A.size(), d = A[0].size();
    vector<vector<double>> ret;
    ret.resize(d);
    for (size_t i = 0; i < d; ++i) {
        ret[i].resize(k);
        for (size_t j = 0; j < k; ++j) {
            ret[i][j] = A[j][i];
        }
    }
    return ret;
}

inline double l2_norm(const vector<double>& a, const vector<double>& b) {
    double ret = 0.0;
    size_t l = a.size();
    for (size_t i = 0; i < l; ++i) {
        ret += std::pow(a[i] - b[i], 2);
    }
    return ret;
}

template <typename T>
T average(const vector<T>& data) {
    if (data.empty())
        return 0;
    else {
        return std::accumulate(data.begin(), data.end(), T()) / static_cast<double>(data.size());
    }
}

#endif
