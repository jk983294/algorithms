#ifndef STRINGHANDLE_H
#define STRINGHANDLE_H
#include "myutility.h"

void basic_string_app();
void my_kmp();
void longest_huiwen_substr();                               //最长回文子串  Manacher算法
bool str_contain_circle_shift(string a,string b);           //字符串移位包含问题
int simlarity_of_two_string(string a,string b);             //两个字符串的相似度 1. 修改一个字符 2. 增加一个字符 3. 删除一个字符
int simlarity_of_two_string(string &a,int abegin,int aend,string &b,int bbegin,int bend );


#endif
