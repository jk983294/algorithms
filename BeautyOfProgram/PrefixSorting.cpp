#include "MyUtility.h"

class PrefixSort {
public:
    vector<int> array, upIndex;          //数组，记录第N次的翻转位置
    int size, upBoundTimes, totalTimes;  //数组大小，翻转次数上界，找到最优解总共翻转次数
public:
    PrefixSort(int *a, int len);
    void up_bound();  //找到最大值，然后翻转，最多2(n-1)次，求得上界
    int search_least_time(vector<int> a, int cnt);
    bool has_sorted(vector<int> &a);
};

void test_PrefixSort();

int main() {
    test_PrefixSort();  // No 1.3  烙饼排序
    return 0;
}

void test_PrefixSort() {
    int array[] = {0, 7, 8, 9, 4, 5, 6, 1, 2, 3};
    PrefixSort ps(array, sizeof(array) / sizeof(int));
    ps.up_bound();  //找到上界
    ps.search_least_time(ps.array, 0);
    cout << ps.totalTimes << endl << ps.upBoundTimes << endl << ps.upIndex << endl;
}
bool PrefixSort::has_sorted(vector<int> &a) {
    for (unsigned int i = 0; i < a.size() - 1; ++i) {
        if (a[i] < a[i + 1]) return false;
    }
    return true;
}
int PrefixSort::search_least_time(vector<int> a, int cnt) {
    if (has_sorted(a)) {
        if (cnt < upBoundTimes) upBoundTimes = cnt;
        return cnt;
    }
    if (cnt >= upBoundTimes - 1) return upBoundTimes + 1;

    int min_times = 0x7fffffff, times, upDownIndex;
    for (int i = 0; i < size - 1; ++i) {
        reverse(a.begin() + i, a.end());
        ++totalTimes;
        times = search_least_time(a, cnt + 1);
        if (times < min_times) {
            min_times = times;
            upDownIndex = i;
        }
        if (times == upBoundTimes) {
            upIndex[cnt] = upDownIndex;
        }
        reverse(a.begin() + i, a.end());
    }
    return min_times;
}

// 找到最大值，然后翻转，最多2(n-1)次，求得上界
void PrefixSort::up_bound() {
    vector<int> a;
    a = array;
    vector<int>::iterator itr, base;
    upBoundTimes = 0;
    base = a.begin();
    for (int i = 0; i < size; ++i) {
        itr = max_element(base, a.end());
        if (itr != base) {
            if (itr != a.end() - 1) {
                reverse(itr, a.end());
                upBoundTimes++;
            }
            reverse(base, a.end());
            upBoundTimes++;
        }
        base++;
    }
    upIndex.resize(upBoundTimes);
    cout << "upBoundTimes : " << upBoundTimes << endl;
}

PrefixSort::PrefixSort(int *a, int len) {
    array.resize(len);
    size = len;
    totalTimes = 0;
    copy(a, a + len, array.begin());
    cout << array << endl;
}
