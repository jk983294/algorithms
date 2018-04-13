#include "MyUtility.h"

/**
 * optiver interview question 2
 * given GPS data vector<int> metreSplits, each data means move distance every 5 seconds
 * figure out the fastest 1000 meters speed
 * within 5 seconds, use interpolation
 */

constexpr float secondPerData = 5;
constexpr float targetDistance = 1000;

float calculate(vector<int>& metreSplits, size_t left, size_t right, int distance) {
    if (distance < 1000 || left >= right) return 0;

    right = right - 1;
    float result = 0;
    if (left == right) {
        result = distance / secondPerData;
    } else if (metreSplits[left] < metreSplits[right]) {
        if (distance - 1000 < metreSplits[left]) {  // 1000 must include left data
            float seconds = secondPerData * ((right - left + 1) - (distance - targetDistance) / metreSplits[left]);
            result = targetDistance / seconds;
            cout << "left: " << left << " right: " << right << " distance: " << distance << " speed: " << result
                 << endl;
        }
    } else {
        if (distance - 1000 < metreSplits[right]) {  // 1000 must include right data
            float seconds = secondPerData * ((right - left + 1) - (distance - targetDistance) / metreSplits[right]);
            result = targetDistance / seconds;
            cout << "left: " << left << " right: " << right << " distance: " << distance << " speed: " << result
                 << endl;
        }
    }

    return result;
}

float calculateFastestKilometreSpeed(vector<int> metreSplits) {
    if (metreSplits.empty()) return 0;

    size_t leftIndex = 0, rightIndex = 1, size = metreSplits.size();
    int distance = metreSplits[leftIndex];
    float fastest = calculate(metreSplits, leftIndex, rightIndex, distance);
    while (leftIndex < size) {
        if (distance < 1000) {
            if (rightIndex < size) {
                distance += metreSplits[rightIndex++];
                fastest = max(fastest, calculate(metreSplits, leftIndex, rightIndex, distance));
            } else {
                break;
            }
        } else {
            if (leftIndex < rightIndex) {
                distance -= metreSplits[leftIndex++];
                fastest = max(fastest, calculate(metreSplits, leftIndex, rightIndex, distance));
            } else if (rightIndex < size) {
                distance += metreSplits[rightIndex++];
                fastest = max(fastest, calculate(metreSplits, leftIndex, rightIndex, distance));
            } else {
                break;
            }
        }
    }
    return fastest;
}

int main() {
    vector<int> a{800, 150, 50, 700, 50, 900};
    cout << calculateFastestKilometreSpeed(a) << endl;
    vector<int> metreSplits{
        487, 34, 14, 28, 38, 39, 36, 14, 10, 5,  16, 11, 5,  24, 25, 15, 11, 9,  8,  36, 2,  26, 35, 29, 7,  3,  7,  27,
        37,  10, 11, 1,  20, 2,  12, 40, 10, 31, 10, 37, 11, 18, 15, 25, 2,  33, 38, 29, 30, 38, 1,  7,  9,  38, 36, 34,
        38,  14, 32, 26, 23, 29, 30, 30, 40, 4,  23, 27, 23, 23, 7,  12, 37, 31, 11, 16, 23, 29, 26, 12, 6,  15, 22, 2,
        5,   40, 24, 0,  36, 33, 21, 38, 6,  10, 17, 18, 5,  8,  11, 23, 10, 15, 0,  17, 36, 13, 38, 17, 26, 24, 17, 16,
        34,  34, 1,  11, 18, 29, 10, 27, 14, 6,  29, 3,  22, 39, 10, 26, 7,  8,  13, 36, 5,  39, 28, 20, 21, 5,  31, 40,
        37,  37, 19, 29, 26, 32, 40, 20, 9,  19, 15, 3,  26, 30, 35, 7,  13, 6,  34, 30, 38, 27, 11, 12, 22, 25, 16, 29,
        35,  21, 35, 22, 5,  21, 34, 24, 5,  27, 12, 26, 33, 13, 35, 39, 8,  18, 27, 23, 0,  34, 32, 3,  12, 21, 29, 18,
        33,  28, 22, 38, 23, 24, 37, 28, 12, 36, 20, 10, 38, 36, 6,  36, 23, 3,  22, 25, 7,  25, 40, 10, 2,  21, 28, 37,
        38,  23, 13, 28, 5,  13, 23, 5,  39, 6,  6,  17, 29, 20, 14, 6,  32, 38, 27, 36, 28, 35, 30, 6,  6,  22, 37, 20,
        14,  39, 9,  35, 1,  33, 3,  33, 1,  36, 29, 10, 10, 31, 34, 34, 15, 11, 5,  15, 27, 14, 7,  25, 23, 9,  10, 23,
        24,  23, 33, 37, 28, 22, 17, 10, 33, 33, 39, 1,  37, 38, 11, 23, 34, 33, 28, 6,  26, 10, 37, 12, 20, 0,  11, 20,
        2,   23, 19, 38, 13, 8,  37, 16, 2,  23, 7,  1,  30, 9,  15, 9,  8,  8,  1,  20, 24, 13, 28, 8,  21, 40, 8,  16,
        34,  39, 33, 14, 3,  10, 37, 7,  23, 24, 39, 3,  19, 18, 12, 11, 10, 30, 12, 2,  34, 34, 9,  12, 30, 13, 9,  19,
        9,   32, 2,  29, 30, 9,  40, 34, 24, 39, 38, 7,  14, 2,  20, 2,  2,  35, 24, 2,  30, 23, 35, 2,  8,  27, 21, 30,
        7,   27, 33, 12, 9,  22, 37, 26, 7,  39, 15, 10, 12, 37, 9,  12, 33, 22, 4,  5,  33, 32, 17, 6,  35, 32, 11, 34,
        30,  2,  9,  7,  35, 39, 2,  17, 6,  27, 11, 28, 39, 14, 23, 8,  17, 6,  14, 6,  24, 39, 2,  25, 10, 28, 24, 16,
        7,   10, 29, 37, 27, 39, 29, 31, 21, 31, 17, 38, 9,  25, 25, 26, 27, 30, 35, 23, 26, 10, 6,  4,  29, 22, 7,  10,
        17,  28, 36, 19, 3,  5,  14, 8,  31, 36, 4,  13};
    cout << calculateFastestKilometreSpeed(metreSplits) << endl;
    cout << 4.77528089888 << endl;
    return 0;
}
