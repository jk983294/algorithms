#include <Hashes.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <unordered_map>
#include "Algebra.h"
#include "TestHelper.h"

using namespace std;

/**
 * https://en.wikipedia.org/wiki/Johnson%E2%80%93Lindenstrauss_lemma
 * dimensionality reduction
 */

vector<vector<double>> calc_l2_norm_pairwise(const vector<vector<double>>& data);
vector<vector<double>> sparse_transform_matrix(size_t k, size_t d);

int main() {
    size_t n = 5, d = 10000;
    vector<vector<double>> data = generate_uniform_matrix(n, d, 0, 10);
    cout << "naive way:\n";
    cout << calc_l2_norm_pairwise(data) << endl;

    // k = 20 * log(n) / epsilon^2, assume n > d, here choose n is small so easy to print, manually choose k = 100
    size_t k = 1000;
    cout << "gaussian matrix JL way:\n";
    cout << calc_l2_norm_pairwise(transpose(matrix_multi(generate_gaussian_matrix(k, d), transpose(data)))) << endl;

    cout << "sparse matrix JL way:\n";
    cout << calc_l2_norm_pairwise(transpose(matrix_multi(sparse_transform_matrix(k, d), transpose(data)))) << endl;
    return 0;
}

vector<vector<double>> sparse_transform_matrix(size_t k, size_t d) {
    random_device rd;
    mt19937 generator(rd());
    std::uniform_real_distribution<double> nd(0.0, 1.0);
    vector<vector<double>> ret;
    ret.resize(k);
    for (size_t i = 0; i < k; ++i) {
        ret[i].resize(d);
        for (size_t j = 0; j < d; ++j) {
            double rnd = nd(generator);
            if (rnd < 1.0 / 6) {
                ret[i][j] = rnd * (1.0 / sqrt(k));
            } else if (rnd < 5.0 / 6) {
                ret[i][j] = 0;
            } else {
                ret[i][j] = rnd * (-1.0 / sqrt(k));
            }
        }
    }
    return ret;
}

vector<vector<double>> calc_l2_norm_pairwise(const vector<vector<double>>& data) {
    size_t l = data.size();
    vector<vector<double>> ret;
    ret.resize(l);
    for (size_t i = 0; i < l; ++i) {
        ret[i].resize(l);
        for (size_t j = 0; j < l; ++j) {
            ret[i][j] = l2_norm(data[i], data[j]);
        }
    }
    return ret;
}
