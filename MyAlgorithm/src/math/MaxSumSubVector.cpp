#include "MaxSumSubVector.h"

using namespace std;

int calculateMaxSum(vector<int> a, int& start, int& end) {
    int maxBest = -99999, currentMax = 0;
    start = -1;
    end = 0;
    int size = static_cast<int>(a.size());
    for (int i = 0; i < size; i++) {
        currentMax += a[i];
        if (currentMax > maxBest) {
            maxBest = currentMax;
            end = i;
        }
        if (currentMax < 0) {
            currentMax = 0;
            start = i;
        }
    }
    ++start;
    return maxBest;
}

int calculateMaxMultiply(vector<int> a, int& start, int& end) {
    int maxBest = 1, currentPositiveMax = 0, currentNegativeMax = 0;
    int currentBeginPos = -1;
    end = 0, start = -1;
    int size = static_cast<int>(a.size());
    for (int i = 0; i < size; i++) {
        maxBest *= a[i];
        if (maxBest > 0 && currentPositiveMax < maxBest) {
            currentPositiveMax = maxBest;
            end = i;
            start = currentBeginPos;
        }
        if (maxBest < 0 && currentNegativeMax < maxBest) {
            currentNegativeMax = maxBest;
        }
        if (maxBest == 0) {
            maxBest = 1;
            currentBeginPos = i;
        }
    }
    ++start;
    return currentPositiveMax;
}
