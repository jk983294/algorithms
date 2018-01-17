#ifndef ALGORITHMS_MAX_LENGTH_SUB_ARRAY_H
#define ALGORITHMS_MAX_LENGTH_SUB_ARRAY_H

#include <unordered_map>
#include <vector>

using namespace std;

class MaxLengthSubArray {
public:
    int process(vector<int>& data, int targetSum) {
        int sum = 0;
        int len = static_cast<int>(data.size());
        unordered_map<int, int> m;
        m[0] = -1;  // means from start, we get sum 0
        int result = 0;
        for (int i = 0; i < len; ++i) {
            sum += data[i];
            if (m.find(sum) == m.end()) {  // only record the earliest partial sum
                m[sum] = i;
            }

            if (m.find(sum - targetSum) != m.end()) {
                result = std::max(result, i - m[sum - targetSum]);
            }
        }
        return result;
    }
};

#endif
