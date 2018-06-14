#include <climits>
#include "MyUtility.h"

template <class T>
T flipBit5(T x) {
    uint bit5 = 1 << 4;
    T xWithoutBit5 = x & ~bit5;
    T flippedBit5 = ~(x & bit5) & bit5;
    return flippedBit5 | xWithoutBit5;
}

void count_one_in_binary_number(unsigned int num);  // 二进制数中1的个数
void find_abnormal_number();  // 异形数，数组中有三个数字出现一次，其余出现2次，找出3个中的任意一个
int get_number_sign(int n);
bool is_same_sign(int x, int y);
unsigned int bit_abs(int n);
int bit_min(int x, int y);
int bit_max(int x, int y);
bool is_power_two(int n);

int main() {
    count_one_in_binary_number(7);  // 二进制数中1的个数  No. 2.1
    find_abnormal_number();  // 异形数，数组中有三个数字出现一次，其余出现2次，找出3个中的任意一个

    cout << "flipBit5 test: " << flipBit5(63) << endl;  // 111111 => 101111
    cout << "flipBit5 test: " << flipBit5(47) << endl;  // 101111 => 111111
    cout << "flipBit5 test: " << flipBit5(-63) << endl;
    cout << "flipBit5 test: " << flipBit5(-47) << endl;

    cout << "number sign of 42: " << get_number_sign(42) << endl;    // 1
    cout << "number sign of 0: " << get_number_sign(0) << endl;      // 0
    cout << "number sign of -42: " << get_number_sign(-42) << endl;  // -1

    cout << is_same_sign(4, 2) << endl;   // 1
    cout << is_same_sign(4, -2) << endl;  // 0
    cout << is_same_sign(4, 0) << endl;   // 0
    cout << is_same_sign(-4, 0) << endl;  // 0
    cout << is_same_sign(0, 0) << endl;   // 1

    cout << bit_abs(42) << endl;   // 42
    cout << bit_abs(-42) << endl;  // 42
    cout << bit_abs(0) << endl;    // 0

    cout << bit_min(4, -2) << endl;  // -2
    cout << bit_max(4, 2) << endl;   // 4

    cout << is_power_two(42) << endl;   // 0
    cout << is_power_two(128) << endl;  // 1
    return 0;
}

bool is_power_two(int v) { return v && !(v & (v - 1)); }

int get_number_sign(int n) { return (n != 0) | -(int)((unsigned int)((int)n) >> (sizeof(int) * CHAR_BIT - 1)); }

bool is_same_sign(int x, int y) { return (x == 0 && y == 0) || (x != 0 && y != 0 && (x ^ y) > 0); }

unsigned int bit_abs(int v) {
    int const mask = v >> (sizeof(int) * CHAR_BIT - 1);
    return static_cast<unsigned int>((v + mask) ^ mask);
}

int bit_min(int x, int y) { return y ^ ((x ^ y) & -(x < y)); }
int bit_max(int x, int y) { return x ^ ((x ^ y) & -(x < y)); }

// 二进制数中1的个数
void count_one_in_binary_number(unsigned int num) {
    int cnt = 0;
    // while(num){              //O(总位数)
    //     cnt  += num & 0x1;
    //     num >>= 1;           //右移一位
    // }
    while (num) {          // O(1的个数)
        num &= (num - 1);  // 每次消掉最低位1
        ++cnt;
    }
    cout << cnt << endl;
}

// low bit表示的是某个数从右往左扫描第一次出现1的位置
int low_bit(int x) { return x & ~(x - 1); }

void find_abnormal_number() {
    int a[] = {1, 3, 7, 9, 5, 9, 4, 3, 6, 1, 7};  // 4,5,6
    int n = sizeof(a) / sizeof(int);
    int xorValue = 0;
    for (int i = 0; i < n; i++) xorValue ^= a[i];
    int num = 0;  // 三个数两两的异或后lowBit有两个相同，一个不同，可以分为两组
    for (int i = 0; i < n; i++) {
        // num = low_bit(a^b) ^ low_bit(a^c) ^ low_bit(b^c) 两个相同的会抵消掉  留下末尾1不同的数字
        num ^= low_bit(xorValue ^ a[i]);
    }

    int b = 0;
    for (int i = 0; i < n; i++) {
        /**
         * 如果a[i]是三个不同的数中的一个的话，则其中两个异或xor结果的low_bit和num不同，只有一个相同，
         * 如果a[i]不是三个数中的话，则如果以后结果符合，由于他们每个数都有两个，再和b异或后就变为0，
         * 所以b最后是那三个不同的数的一个。
         */
        if (low_bit(xorValue ^ a[i]) == num) {
            b ^= a[i];
        }
    }
    cout << "find_abnormal_number : " << b << endl;
}
