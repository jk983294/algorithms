#include "MyUtility.h"

void find_abnormal_number();  // 异形数，数组中有三个数字出现一次，其余出现2次，找出3个中的任意一个
void count_one_in_binary_number(unsigned int num);  // 二进制数中1的个数
void factorial_last_zeros(int num);                 // 阶乘末尾0的个数
void count_of_ones(int num);      // 从1到num的整数中1出现的次数，统计个十百位1的个数
int gcd(int x, int y);            // 求x,y 的最大公约数
void find_fittest_number(int N);  // 给定N，找到最小的M使得乘积N*M的十进制表达式中只有0和1
void max_sub_vector_sum();        // 数组子数组之和最大值
int max_sum_one_dimension_vector(vector<int> &a, int &sureStartPos, int &endPos);
void max_sum_sub_two_dimension_vectors();  // 二维数组最大子数组和
void max_ascend_sub_vector();              // 最长递增子序列
void right_shift();                        // 右移
bool is_palindrome(int a);                 // 正整数  判断是否为回文数字
void test_count_range();                   // 排序好区域内数的个数
void calc_asymptotic_value();              // 渐近求值，求 y = x^2 的极小值
void antCrawlTime();                       // 蚂蚁爬杆最短最长时间
void last_num_wangyi();                    // 网易题目 199循环队列 逢二删除 求最后一个数字
void chinese_left_theorem();               // 中国剩余定理

int main() {
    count_one_in_binary_number(7);  // 二进制数中1的个数  No. 2.1
    factorial_last_zeros(26);       // 阶乘末尾0的个数    No. 2.2
    count_of_ones(9999);            // 从1到num的整数中1出现的次数  No. 2.4
    cout << gcd(9, 4) << endl;      // 求最大公约数 No. 2.7
    find_fittest_number(22);        // 给定N，找到最小的M使得乘积N*M的十进制表达式中只有0和1
    max_sub_vector_sum();           // 数组子数组之和最大值 No.2.14
    max_sum_sub_two_dimension_vectors();  // 二维数组最大子数组和  No. 2.15
    max_ascend_sub_vector();              // 最长递增子序列   No. 2.16
    right_shift();                        // 右移k位  No. 2.17
    cout << is_palindrome(122) << endl;   // 正整数  判断是否为回文数字
    test_count_range();  // 排序好的数组中，在 [ startNum, endNum ](都是闭区间)之间的数有多少个
    calc_asymptotic_value();  // 渐近求值，求 y = x^2 的极小值
    last_num_wangyi();        // 网易题目 199循环队列 逢二删除 求最后一个数字
    chinese_left_theorem();   // 中国剩余定理
    find_abnormal_number();  // 异形数，数组中有三个数字出现一次，其余出现2次，找出3个中的任意一个
    antCrawlTime();  // 蚂蚁爬杆最短最长时间        No. 4.7
    return 0;
}

// low bit表示的是某个数从右往左扫描第一次出现1的位置
int low_bit(int x) { return x & ~(x - 1); }

void find_abnormal_number() {
    int a[] = {1, 3, 7, 9, 5, 9, 4, 3, 6, 1, 7};  // 4,5,6
    int n = sizeof(a) / sizeof(int);
    int xorValue = 0;
    for (int i = 0; i < n; i++) xorValue ^= a[i];
    int num = 0;  // 三个数两两的异或后lowbit有两个相同，一个不同，可以分为两组
    for (int i = 0; i < n; i++) {
        // 表示的是：num = low_bit(a^b) ^ low_bit(a^c) ^ low_bit(b^c) 两个相同的会抵消掉  留下末尾1不同的数字
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

// 中国剩余定理
void chinese_left_theorem() {
    //  x % modulus = residuals  求x
    int modulus[] = {3, 5, 7};    // 模数，互质
    int residuals[] = {2, 3, 2};  // 余数
    int size1 = sizeof(modulus) / sizeof(int);
    vector<int> c(size1, 0);
    int n = 1, m, mf, x = 0;
    for (int i = 0; i < size1; ++i) n *= modulus[i];
    for (int i = 0; i < size1; ++i) {
        m = n / modulus[i];
        mf = 1;
        while ((m * (mf++)) % modulus[i] != 1)
            ;
        c[i] = m * (mf - 1);
    }
    for (int i = 0; i < size1; ++i) x += residuals[i] * c[i];
    x %= n;
    cout << x << endl;
}
void last_num_wangyi() {
    vector<bool> nums(199, false);
    int left = 199, index = 1;
    vector<bool>::iterator itr = nums.begin();
    while (left > 1) {
        ++index;
        do {
            ++itr;
            if (itr == nums.end()) {
                cout << endl;
                itr = nums.begin();
            }
        } while (*itr);
        if (index == 2) {
            cout << (itr - nums.begin()) + 1 << " ";
            *itr = true;
            index = 0;
            --left;
        }
    }
    do {
        ++itr;
        if (itr == nums.end()) itr = nums.begin();
    } while (*itr);
    cout << endl << (itr - nums.begin()) + 1 << endl;
}

void antCrawlTime(double length,  // length of stick
                  double *xPos,   // position of an ant,<=length
                  int antNum,     // number of ant
                  double speed,   // speed of crawl
                  double &min,    // min of leave time
                  double &max)    // max of leave time
{
    double totalTime = length / speed;
    min = 0;
    max = 0;
    for (int i = 0; i < antNum; i++) {
        double tmpMin = 0;
        double tmpMax = 0;
        if (xPos[i] < length / 2) {
            tmpMax = (length - xPos[i]) / speed;
        } else {
            tmpMax = xPos[i] / speed;
        }
        tmpMin = totalTime - tmpMax;

        if (max < tmpMax) {
            max = tmpMax;
        }
        if (min < tmpMin) {
            min = tmpMin;
        }
    }
}

void antCrawlTime() {
    double xPos[] = {3, 7, 11, 17, 23};
    double min, max;
    antCrawlTime(27, xPos, 5, 1, min, max);
    cout << "min:" << min << "    max:" << max << endl;
}

//渐近求值，求 y = x^2 的极小值
void calc_asymptotic_value() {
    double startPos = -10, endPos = 10;
    double third1, third2;
    double r1, r2;
    while (1) {
        third1 = (endPos - startPos) / 3 + startPos;
        third2 = 2 * (endPos - startPos) / 3 + startPos;
        r1 = third1 * third1;
        r2 = third2 * third2;
        if (r1 > r2) {
            startPos = third1;
        } else {
            endPos = third2;
        }
        if (endPos - startPos < 10e-7) break;
    }
    cout << setiosflags(ios::fixed) << setprecision(7) << startPos << endl;
}

void test_count_range() {
    int a[] = {1, 2, 7, 9, 15, 17, 20, 30};
    vector<int> aa = to_vector(a, sizeof(a) / sizeof(int));
    cout << count_sorted_array_range(aa, 0, 0) << endl;
    cout << count_sorted_array_range(aa, 0, 1) << endl;
    cout << count_sorted_array_range(aa, 1, 7) << endl;
    cout << count_sorted_array_range(aa, 6, 10) << endl;
    cout << count_sorted_array_range(aa, 9, 17) << endl;
    cout << count_sorted_array_range(aa, 21, 40) << endl;
    cout << count_sorted_array_range(aa, 31, 40) << endl;
}

bool is_palindrome(int a) {  // 正整数  判断是否为回文数字
    vector<int> digits(50);  // 最多50位10进制数字
    int digitCount = 0;      // 记录该数字有多少位
    do {
        digits[digitCount++] = a % 10;
        a /= 10;
    } while (a != 0);
    int endPos = digitCount - 1, half = digitCount / 2;
    for (int i = 0; i < half; ++i) {
        if (digits[i] != digits[endPos - i]) return false;
    }
    return true;
}

// 右移
void right_shift() {
    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(a1) / sizeof(int);
    vector<int> a = to_vector(a1, size);
    int k = 3;  // 右移位数
    reverse_vector(a, 0, size - k - 1);
    reverse_vector(a, size - k, size - 1);
    reverse_vector(a, 0, size - 1);
    cout << a << endl;
}

// 最长递增子序列
void max_ascend_sub_vector() {
    int a1[] = {1, -1, 2, -3, 4, -5, 6, -7};
    int size = sizeof(a1) / sizeof(int);
    vector<int> a = to_vector(a1, size);
    vector<int> f(size, 1);  // f[i]记录以a[i]为末元素的最长递增子序列长度 //至少为1，因为a[i]自己递增

    // Method 1
    // for (int i =0; i< size; ++i)    {            //O(n^2)
    //     for (int j = 0; j < i; ++j){             //遍历 i 之前所有的以a[j]结尾的最长递增子序列，取最大
    //         if(a[i] > a[j] && ( f[j]+1 > f[i])){
    //             f[i] = f[j] + 1;
    //         }
    //     }
    // }

    // Method 2
    vector<int> MaxV(size + 1);  // MaxV[i] 为所有长度为i的递增子序列中末元素最小的一个，a[j]和最小的比判断是否扩展
    MaxV[1] = a[0];
    int nMaxLIS = 1;  // 最长元素为
    for (int i = 0; i < size; ++i) {
        for (int j = nMaxLIS; j >= 1; --j) {  // 从序列长度递减来观察是否可以扩展 此处可用二分查找来优化O(nlgn)
            if (a[i] > MaxV[j]) {
                f[i] = j + 1;
                break;
            }
        }
        if (f[i] > nMaxLIS) {  // 更新最长序列
            nMaxLIS = f[i];
            MaxV[nMaxLIS] = a[i];
        } else if (a[i] < MaxV[f[i]]) {  // 更新长度为f[i]的末元素最小
            MaxV[f[i]] = a[i];
        }
    }
    cout << *max_element(f.begin(), f.end()) << endl;
}

// 二维数组最大子数组和
void max_sum_sub_two_dimension_vectors() {
    const int clm = 5;
    const int row = 5;
    int a[row][clm] = {{1, 2, 3, 4, 1}, {1, -9, 3, 4, 1}, {1, 2, -4, -20, 1}, {1, -3, 3, 4, 1}, {1, -2, 3, 4, 1}};
    //记录从[0,0] 到 [i,j]矩形内元素和
    vector<vector<int> > sumt;
    make_two_dimension_vector(row, clm, 0, sumt);
    sumt[0][0] = a[0][0];
    for (int i = 1; i < clm; ++i) sumt[0][i] = a[0][i] + sumt[0][i - 1];
    for (int i = 1; i < row; ++i) sumt[i][0] = a[i][0] + sumt[i - 1][0];
    for (int i = 1; i < row; ++i)
        for (int j = 1; j < clm; ++j) sumt[i][j] = a[i][j] + sumt[i - 1][j] + sumt[i][j - 1] - sumt[i - 1][j - 1];

    // 二维问题转一维
    vector<int> partialSum(clm);
    int sum = 0, maxSum = NEGA_BIG_INT;
    int endPos, startPos;
    int clm1, clm2, row1, row2;
    for (int i = 0; i < row; ++i) {
        for (int j = i; j < clm; ++j) {  // 枚举行边界
            fill(partialSum.begin(), partialSum.end(), 0);
            for (int k = 0; k < clm; ++k) {  // 计算上下边界中的柱状总和
                partialSum[k] += sumt[j][k];
                if (k - 1 >= 0) partialSum[k] -= sumt[j][k - 1];
                if (i - 1 >= 0) partialSum[k] -= sumt[i - 1][k];
                if (k - 1 >= 0 && i - 1 >= 0) partialSum[k] += sumt[i - 1][k - 1];
            }
            sum = max_sum_one_dimension_vector(partialSum, startPos, endPos);
            if (sum > maxSum) {  // 记录最优解
                maxSum = sum;
                row1 = i;
                row2 = j;
                clm1 = startPos;
                clm2 = endPos;
            }
        }
    }
    cout << maxSum << "  row1: " << row1 << "  row2: " << row2 << "  clm1: " << clm1 << "  clm2: " << clm2 << endl;
}
int max_sum_one_dimension_vector(vector<int> &a, int &sureStartPos, int &endPos) {
    int size = a.size();
    int sum = 0, maxSum = NEGA_BIG_INT;
    int startPos = 0;
    for (int i = 0; i < size; ++i) {
        sum += a[i];
        if (sum > maxSum) {
            maxSum = sum;
            sureStartPos = startPos;
            endPos = i;
        }
        if (sum < 0) {
            sum = 0;
            startPos = i + 1;
        }
    }
    return maxSum;
}

// 数组子数组之和最大值
void max_sub_vector_sum() {
    int a[] = {-2, 5, 3, -7, 4, -8, -6};
    int size = sizeof(a) / sizeof(int);
    vector<int> x(a, a + size);
    int endPos, startPos;
    cout << max_sum_one_dimension_vector(x, startPos, endPos);
    cout << " start : " << startPos << " to : " << endPos << endl;
}
int parse_number(vector<int> &num) {
    int len = num.size(), x = 0;
    for (int i = len - 1; i >= 0; --i) {
        x += num[i] * pow(10, (double)len - i - 1);
    }
    return x;
}

// 给定N，找到最小的M使得乘积N*M的十进制表达式中只有0和1
void find_fittest_number(int N) {
    int ji, digitCount = 1;
    bool found = false;
    while (digitCount < 12) {
        vector<int> num(digitCount, 0);
        num[0] = 1;  // 第一位为1
        do {
            ji = parse_number(num);
            if (ji % N == 0) {
                found = true;
                break;
            }
        } while (generate_all_k_choices(num, digitCount, 2));
        if (found) break;
        ++digitCount;
    }
    cout << (ji / N) << endl;
}

int gcd(int x, int y) {
    if (y > x) swap(x, y);
    // 辗转相除
    //  if ( x % y == 0)    return y;
    //  else return gcd(x, x%y);
    //  f(x,y) = f(x-y,y)  取模运算被替换为大整数减法, 但是迭代次数增加
    //  if (x - y == 0) return y;
    //  else return gcd(x-y,y);

    //结合的方法
    if (y == 0)
        return x;
    else if (x % 2 == 0 && y % 2 == 0)
        return 2 * gcd(x >> 1, y >> 1);  // f(x,y) = 2*f(x/2,y/2)
    else if (x % 2 == 0 && y % 2 != 0)
        return gcd(x >> 1, y);  // f(x,y) = 2*f(x/2,y)
    else if (x % 2 != 0 && y % 2 == 0)
        return gcd(x, y >> 1);  // f(x,y) = 2*f(x,y/2)
    else
        return gcd(x - y, y);  // f(x,y) = 2*f(x-y,y)
}

// 从1到num的整数中1出现的次数，统计个十百位1的个数
void count_of_ones(int num) {
    int cnt = 0, wei, factors = 1;
    while (factors < num) {
        wei = (num / factors) % 10;  // 取某一位上的值
        switch (wei) {
            case 0:
                cnt += (num / (factors * 10)) * factors;
                break;  // 该位前面的值 * factor
            case 1:
                cnt += (num / (factors * 10)) * factors + (num * 10 / factors) % 10 + 1;
                break;  // 该位前面的值 * factor + 后一位的值 + 1
            default:
                cnt += (num / (factors * 10)) * factors + 1 * factors;
        }
        factors *= 10;
    }
    cout << cnt << endl;
}

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

void factorial_last_zeros(int num) {  // 2^m * 5^k  m>k 所以求5的因子分解个数
    int cnt = 0, factor = 5;
    // for (int i = 1; i <= num; ++i) {
    //     int tmp = i;
    //     while(tmp%5 == 0){
    //         ++cnt;
    //         tmp /= 5;
    //     }
    // }
    while (factor < num) {
        cnt += num / factor;
        factor *= 5;
    }
    cout << cnt << endl;
}
