#include <iostream>
#include <random>
#include <vector>

using namespace std;

/**
 * select k items from a stream of items
 * https://en.wikipedia.org/wiki/Reservoir_sampling
 * 1. Keep the first k items in memory
 * 2. When the i-th item arrives (for i > k):
 *      1) with probability k / i, keep the new item,
 *         discard an old one, selecting which to replace at random, each with chance 1 / k
 *      2) with probability 1 - k / i, keep the old items, ignore the new one
 */

void print(const vector<int>& stream) {
    for (auto i : stream) cout << i << " ";
    cout << endl;
}

vector<int> select(const vector<int>& stream, size_t n, size_t k) {
    if (k >= n) {
        return stream;
    }

    random_device rd;
    mt19937 generator(rd());
    vector<int> reservoir(k, 0);
    for (size_t i = 0; i < k; i++) {
        reservoir[i] = stream[i];
    }

    std::uniform_int_distribution<int> toReplace(0, static_cast<int>(k));
    for (size_t i = k; i < n; i++) {
        std::bernoulli_distribution whether2replace{static_cast<double>(k) / i};
        if (whether2replace(generator)) reservoir[toReplace(generator)] = stream[i];
    }
    return reservoir;
}

int main() {
    vector<int> stream{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    size_t k = 5;
    vector<int> selected = select(stream, stream.size(), k);
    cout << "Following are k randomly selected items \n";
    print(selected);
    return 0;
}
