#include <Hashes.h>
#include <iostream>
#include <random>
#include <unordered_set>
#include "Algebra.h"
#include "TestHelper.h"

using namespace std;

/**
 * https://en.wikipedia.org/wiki/Streaming_algorithm#K-Minimum_Value_Algorithm
 * distinct element number from stream of data
 * application: how many distinct ip within one day for a website visiting
 * use hash(x) ->[0, 1], record Y = min (hash(x[i])
 * E[Y] = 1/(N+1), var(Y) < (1/(N+1))^2, the N is the desired number
 * for high probability, we can use k hash functions to track Z = (1/k) *(∑Y[i])
 * E[Z] = 1/(N+1), var(Z) < 1/(k*(N+1)^2)
 */

size_t naive_way(const vector<uint32_t>& data) {
    std::unordered_set<uint32_t> s;
    s.insert(data.begin(), data.end());
    return s.size();
}

int main() {
    vector<uint32_t> stream_data = generate_uniform_int<uint32_t>(200000, 0, 1000000);
    vector<PrimeHashFamily> hashes = generate_hash_family();

    vector<double> min_value;
    min_value.resize(hashes.size(), 1.0);
    for (uint32_t x : stream_data) {
        for (size_t i = 0; i < hashes.size(); ++i) {
            double hashed = hashes[i].normalized_hash(x);
            if (min_value[i] > hashed) {
                min_value[i] = hashed;
            }
        }
    }

    double z = average<double>(min_value);
    cout << "distinct value count " << static_cast<uint32_t>(1 / z - 1) << " z=" << z << endl;
    cout << "naive distinct value count " << naive_way(stream_data) << endl;
    return 0;
}
