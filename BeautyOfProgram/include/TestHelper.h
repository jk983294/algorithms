#ifndef BEAUTY_TESTHELPER_H
#define BEAUTY_TESTHELPER_H

#include <random>
#include "MyUtility.h"

vector<uint32_t> generate_stream_data(size_t count) {
    random_device rd;  // non-deterministic generator
    mt19937 generator(rd());
    std::uniform_int_distribution<uint32_t> uid(0, 1000000);
    vector<uint32_t> ret;
    ret.resize(count);
    for (size_t i = 0; i < count; ++i) {
        ret[i] = uid(generator);
    }
    return ret;
}

template <typename T, template <typename> class Dist>
vector<T> generate_random_data(size_t count, T a, T b) {
    random_device rd;  // non-deterministic generator
    mt19937 generator(rd());
    Dist<T> uid(a, b);
    vector<T> ret;
    ret.resize(count);
    for (size_t i = 0; i < count; ++i) {
        ret[i] = uid(generator);
    }
    return ret;
}

template <typename T, template <typename> class Dist>
vector<vector<double>> generate_random_data(size_t m, size_t n, T a, T b) {
    random_device rd;  // non-deterministic generator
    mt19937 generator(rd());
    Dist<double> uid(0.0, 10.0);
    vector<vector<double>> ret;
    ret.resize(m);
    for (size_t i = 0; i < m; ++i) {
        ret[i].resize(n);
        for (size_t j = 0; j < n; ++j) {
            ret[i][j] = uid(generator);
        }
    }
    return ret;
}

template <typename T>
vector<T> generate_uniform_int(size_t count, T from = 0, T to = 1000000) {
    return generate_random_data<T, uniform_int_distribution>(count, from, to);
}

template <typename T>
vector<T> generate_gaussian_int(size_t count, T from = 0, T to = 1) {
    return generate_random_data<T, uniform_real_distribution>(count, from, to);
}

inline vector<vector<double>> generate_gaussian_matrix(size_t m, size_t n, double mean = 0, double delta = 1) {
    return generate_random_data<double, normal_distribution>(m, n, mean, delta);
}

inline vector<vector<double>> generate_uniform_matrix(size_t m, size_t n, double from = 0, double to = 1) {
    return generate_random_data<double, uniform_real_distribution>(m, n, from, to);
}

#endif
