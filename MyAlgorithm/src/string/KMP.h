#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class KMP {
public:
    void fail() {  // calculate pat fail function
        int len = pattern.length();
        f.resize(len);
        f[0] = -1;
        for (int i = 1; i < len; i++) {
            int m = f[i - 1];
            while ((m >= 0) && (pattern[i] != pattern[m + 1])) m = f[m];  // find max m
            if (pattern[i] == pattern[m + 1]) {
                f[i] = m + 1;
            } else
                f[i] = -1;
        }
    };

    void printFail() {
        for (vector<int>::iterator itr = f.begin(); itr < f.end(); itr++) {
            cout << *itr << " ";
        }
        cout << endl;
    };

    /**
     * run kmp pattern finding, must run fail first to pre-process pattern string
     * @return -1 means no target pattern string, otherwise the first matched pattern's start position
     */
    int kmp() {  // find pat in s
        fail();

        int i = 0, j = 0;
        int lenS = str.length();
        int lenP = pattern.length();
        while ((i < lenS) && (j < lenP)) {
            if (str[i] == pattern[j]) {
                i++;
                j++;
            } else {
                if (j == 0) {
                    i++;
                } else {
                    j = f[j - 1] + 1;
                }
            }
        }

        if ((j < lenP) || (lenP == 0)) {
            cout << "no target pattern string" << endl;
            return -1;
        } else {  // first matched pattern string pos in s
            return i - lenP;
        }
    }

    void EKMP(string s, string t)  // s[]为主串，t[]为模版串
    {
        vector<int> next, extend;  // extend[i]表示原串以第i开始与模式串的前缀的最长匹配
        int i, j, p, l;
        int len = t.size();
        int len1 = s.size();
        next.resize(len, 0);
        extend.resize(len1, 0);
        next[0] = len;
        j = 0;
        while (1 + j < len && t[j] == t[1 + j]) j++;
        next[1] = j;
        int a = 1;
        for (i = 2; i < len; i++) {
            p = next[a] + a - 1;
            l = next[i - a];
            if (i + l < p + 1)
                next[i] = l;
            else {
                j = max(0, p - i + 1);
                while (i + j < len && t[i + j] == t[0 + j]) j++;
                next[i] = j;
                a = i;
            }
        }
        j = 0;
        while (j < len1 && j < len && s[j] == t[j]) j++;
        extend[0] = j;
        a = 0;
        for (i = 1; i < len1; i++) {
            p = extend[a] + a - 1;
            l = next[i - a];
            if (l + i < p + 1)
                extend[i] = next[i - a];
            else {
                j = max(0, p - i + 1);
                while (i + j < len1 && j < len && s[i + j] == t[j]) j++;
                extend[i] = j;
                a = i;
            }
        }
    }

    string str;
    string pattern;
    vector<int> f;  // fail函数 f(i) 记录最大的k使得  p0...pk = pi-k...pi 找不到则为-1
};
