#ifndef ALGORITHMS_WINDOW_MAX_H
#define ALGORITHMS_WINDOW_MAX_H

#include <deque>
#include <vector>

using namespace std;

/**
 * 求给定数组，给定窗口大小，滑动窗口中最大值组成的数组
 */

class WindowMax {
public:
    vector<int> get_window_max_array(const vector<int>& data, int window) {
        vector<int> result;

        if (window <= 0) return result;
        deque<int> dq;  // push data index into it, not data itself
        int len = static_cast<int>(data.size());
        for (int i = 0; i < len; ++i) {
            if (dq.empty()) {
                dq.push_back(i);
            } else {
                if (i - dq.front() == window) dq.pop_front();  // remove out of window data index

                while (!dq.empty() && data[dq.back()] <= data[i]) {
                    dq.pop_back();  // remove those smaller than current element
                }

                dq.push_back(i);
            }
            result.push_back(data[dq.front()]);
        }

        return result;
    }
};

#endif
