#include "MyUtility.h"

void basic_string_app();
void longest_palindrome_sub_string();               // 最长回文子串  Manacher算法
bool str_contain_circle_shift(string a, string b);  // 字符串移位包含问题
int similarity_of_two_string(string a, string b);  // 两个字符串的相似度 1. 修改一个字符 2. 增加一个字符 3. 删除一个字符
int similarity_of_two_string(string &a, int aBegin, int aEnd, string &b, int bBegin, int bEnd);
int similarity_of_two_string_dp(string a, string b);
void test_occurrence_in_matrix();  // optiver interview question 1

int main() {
    basic_string_app();
    longest_palindrome_sub_string();                               // 最长回文串
    cout << str_contain_circle_shift("AABCD", "CDAA") << endl;     // 字符串移位包含问题 No. 3.1
    cout << similarity_of_two_string("dfjsdf", "kdfasd") << endl;  // 字符串相似度 No. 3.3
    cout << similarity_of_two_string_dp("intention", "execution") << endl;
    cout << similarity_of_two_string_dp("horse", "ros") << endl;
    test_occurrence_in_matrix();
    return 0;
}

void longest_palindrome_sub_string() {
    string source_str = "12212321";
    char startChar = '$', delimiter = '#';  //起始符  分隔符
    string newStr;
    newStr += startChar;
    newStr += delimiter;
    for (auto itr = source_str.begin(); itr != source_str.end(); ++itr) {
        newStr += *itr;
        newStr += delimiter;
    }
    cout << newStr << endl;
    int size1 = newStr.size();
    vector<int> p(size1, 0);
    int mx = 0, id = 0;
    for (int i = 1; i < size1; ++i) {
        if (mx > i)
            p[i] = min(p[2 * id - i], mx - i);  //在边界mx内
        else
            p[i] = 1;  // p[i]超出边界mx，设置为1，然后慢慢累加计算长度
        while (i + p[i] < size1 && newStr[i - p[i]] == newStr[i + p[i]]) ++p[i];
        if (i + p[i] > mx) {  // 更新边界mx以及当前最大回文子串的中心id
            mx = i + p[i];
            id = i;
        }
    }
    int maxLen = 0, ii;
    for (int i = 1; i < size1; ++i) {
        if (p[i] > maxLen) {
            ii = i;
            maxLen = p[i];
        }
    }
    maxLen--;
    string maxSubString;
    int start = ii - maxLen;
    int end = ii + maxLen;
    for (int i = start; i <= end; ++i) {
        if (newStr[i] != delimiter) maxSubString += newStr[i];
    }
    cout << maxSubString << endl;
}

int similarity_of_two_string(string &a, int aBegin, int aEnd, string &b, int bBegin, int bEnd) {
    if (aBegin >= aEnd) {
        return bEnd - bBegin;
    } else if (bBegin >= bEnd) {
        return aEnd - aBegin;
    } else if (a[aBegin] == b[bBegin]) {
        return similarity_of_two_string(a, aBegin + 1, aEnd, b, bBegin + 1, bEnd);
    } else {
        // 将b[bBegin]拷到a串对应处  或者 将b[bBegin]在b中删除
        int sim1 = similarity_of_two_string(a, aBegin, aEnd, b, bBegin + 1, bEnd);
        // 将a[aBegin]拷到b串对应处  或者 将a[aBegin]在a中删除
        int sim2 = similarity_of_two_string(a, aBegin + 1, aEnd, b, bBegin, bEnd);
        // 将a[aBegin]修改为b[bBegin]  或者 将b[bBegin]修改为a[aBegin]
        int sim3 = similarity_of_two_string(a, aBegin + 1, aEnd, b, bBegin + 1, bEnd);
        return min(sim1, min(sim2, sim3)) + 1;
    }
}

// 两个字符串的相似度 1. 修改一个字符 2. 增加一个字符 3. 删除一个字符
int similarity_of_two_string(string a, string b) {
    int lenA = a.size(), lenB = b.size();
    return similarity_of_two_string(a, 0, lenA - 1, b, 0, lenB - 1);
}

int similarity_of_two_string_dp(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();

    if (m == 0) return n;
    if (n == 0) return m;

    vector<vector<int>> d;  // d[i][j] = the edit distance between word1[1..i] and word2[1..j]
    d.resize(m + 1);
    for (int i = 0; i < m + 1; ++i) {
        d[i].resize(n + 1, 0);
    }
    for (int i = 0; i < m + 1; ++i) {
        d[i][0] = i;
    }
    for (int j = 0; j < n + 1; ++j) {
        d[0][j] = j;
    }
    for (int i = 1; i < m + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            d[i][j] = min(d[i - 1][j], d[i][j - 1]) + 1;  // delete or insert
            if (word1[i - 1] == word2[j - 1]) {           // no need to replace
                d[i][j] = min(d[i][j], d[i - 1][j - 1]);
            } else {  // replace
                d[i][j] = min(d[i][j], d[i - 1][j - 1] + 1);
            }
        }
    }
    return d[m][n];
}

//字符串移位包含问题
bool str_contain_circle_shift(string a, string b) {
    a += a;
    cout << a << " " << b << endl;
    return a.find(b) != a.npos;
}

void basic_string_app() {
    vector<int> x{3, 7, 4, 9, 5, 8, 1, 10, 13, 6, -1};
    int size = x.size();
    vector<int> indexVector;
    indexVector.resize(size);
    std::iota(indexVector.begin(), indexVector.end(), 0);
    cout << indexVector << endl;
    cout << x << endl;
    quick_sort_with_original_order(x, indexVector, 0, size - 1);
    cout << indexVector << endl;
    cout << x << endl;
    cout << "basic_string_app finish" << endl;
}

int getOptiverCount(string &str) {
    static string pattern{"OPTIVER"};
    static string pattern1{"REVITPO"};
    static size_t strSize = pattern.size();
    size_t idx = 0;
    int count = 0;
    while ((idx = str.find(pattern, idx)) != string::npos) {
        ++count;
        /**
         * kmp algorithm, pattern failed function idea
         * no need to traceback one character like ++idx
         * but to escape pattern.size() since no common part for pattern
         */
        idx += strSize;
        if (idx >= str.size()) break;
    }
    idx = 0;
    while ((idx = str.find(pattern1, idx)) != string::npos) {
        ++count;
        idx += strSize;
        if (idx >= str.size()) break;
    }
    return count;
}

int countOptiverOccurrences(vector<string> characterGrid) {
    int count = 0;
    for (string &s : characterGrid) {
        count += getOptiverCount(s);
    }

    if (characterGrid.size() > 0) {
        int row = characterGrid.size();
        int column = characterGrid[0].size();

        vector<string> transposeGrid;
        transposeGrid.resize(column);
        for (int i = 0; i < column; ++i) {
            transposeGrid[i].resize(row + 1, '\0');
        }
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                transposeGrid[j][i] = characterGrid[i][j];
            }
        }

        for (string &s : transposeGrid) {
            count += getOptiverCount(s);
        }
    }
    return count;
}

/**
 * given a matrix, find occurrence of OPTIVER
 * horizontal order, horizontal reverse order, vertical order, vertical reverse order
 */
void test_occurrence_in_matrix() {
    vector<string> characterGrid{{"SJQLFPQKJQLFPQK"}, {"JDDPQDMDDDPQDMD"}, {"AQEROBPTQEROBPT"}, {"FOPTIVEROPTIVER"},
                                 {"BJDLQPFKJDLQPFK"}, {"VJFPQIEFJFPQIEF"}, {"PQKDIQDPQKDIQDP"}, {"AERIDQPLERIDQPL"},
                                 {"SJQLFPQKJQLFPQK"}, {"JDDPQDMDDDPQDMD"}, {"AQEROBPTQEROBPT"}, {"FOPTIVEROPTIVER"},
                                 {"BJDLQPFKJDLQPFK"}, {"VJFPQIEFJFPQIEF"}, {"PQKDIQDPQKDIQDP"}, {"AERIDQPLERIDQPL"}};
    cout << countOptiverOccurrences(characterGrid) << endl;
}
