#include "utilities.h"

vector<int> getIncrementalVector(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    return a;
}
