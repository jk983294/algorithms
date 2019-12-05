#include <Hashes.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <unordered_map>
#include "TestHelper.h"

using namespace std;

/**
 * count mean sketch
 * used to estimate frequency of element with limited storage, l * b, l is hash count, b is bucket count
 * actually not good for evenly distributed data set, good for biased data set
 */

void naive_way(const vector<uint32_t>& stream_data, const vector<uint32_t>& test_data) {
    std::unordered_map<uint32_t, size_t> data2count;
    for (uint32_t x : stream_data) {
        data2count[x]++;
    }
    cout << "naive way:" << endl;
    for (uint32_t x : test_data) {
        cout << x << " " << data2count[x] << endl;
    }
    cout << endl;
}

int main() {
    vector<uint32_t> stream_data = generate_uniform_int<uint32_t>(200000, 0, 1000000);
    vector<PrimeHashFamily> hashes = generate_hash_family();
    size_t l = hashes.size();
    size_t b = 100;

    std::vector<std::vector<size_t>> count_min_sketch;
    count_min_sketch.resize(l);
    for (auto& item : count_min_sketch) {
        item.resize(b, 0);
    }
    for (uint32_t x : stream_data) {
        for (size_t i = 0; i < l; ++i) {
            uint32_t hashed = hashes[i](x) % b;
            count_min_sketch[i][hashed]++;
        }
    }

    vector<uint32_t> test_data(stream_data.begin(), stream_data.begin() + 10);
    cout << "estimate:\n";
    for (uint32_t x : test_data) {
        size_t minimum = std::numeric_limits<size_t>::max();
        for (size_t i = 0; i < l; ++i) {
            uint32_t hashed = hashes[i](x) % b;
            minimum = min(minimum, count_min_sketch[i][hashed]);
        }
        cout << x << " " << minimum << endl;
    }
    cout << endl;
    naive_way(stream_data, test_data);
    return 0;
}
