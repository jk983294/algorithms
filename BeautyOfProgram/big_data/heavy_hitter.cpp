#include <Hashes.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <unordered_map>
#include "TestHelper.h"

using namespace std;

/**
 * top k items, heavy hitter problem
 * n items, find those appear at least (n/(k+1) + 1) times
 */

void naive_way(const vector<uint32_t>& stream_data, size_t k) {
    std::unordered_map<uint32_t, size_t> data2count;
    for (uint32_t x : stream_data) {
        data2count[x]++;
    }
    std::vector<std::pair<uint32_t, size_t>> top_k(k);
    std::partial_sort_copy(
        data2count.begin(), data2count.end(), top_k.begin(), top_k.end(),
        [](std::pair<uint32_t, size_t> const& l, std::pair<uint32_t, size_t> const& r) { return l.second > r.second; });
    cout << "naive way:\n";
    for (const auto& item : top_k) {
        cout << item.first << " " << item.second << endl;
    }
    cout << endl;
}

int main() {
    vector<uint32_t> stream_data = generate_uniform_int<uint32_t>(200000, 0, 1000000);
    size_t k = 10;

    std::unordered_map<uint32_t, size_t> data2count;
    for (uint32_t x : stream_data) {
        auto itr = data2count.find(x);
        if (itr == data2count.end()) {
            if (data2count.size() < k) {  // new one, still have room
                data2count[x] = 1;
            } else {  // no room left for new guy, then all old guys decrease by one, remove those count == 0
                std::unordered_map<uint32_t, size_t> new_data2count;
                for (const auto& item : data2count) {
                    if (item.second > 1) {
                        new_data2count[item.first] = item.second - 1;
                    }
                }
                data2count.swap(new_data2count);
            }
        } else {
            ++itr->second;
        }
    }

    for (const auto& item : data2count) {
        cout << item.first << " ";
    }
    cout << endl;
    naive_way(stream_data, k);
    return 0;
}
