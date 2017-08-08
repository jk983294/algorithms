#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

int in_stack_priority(char a) {  // 栈内优先级 in stack priority
    if (a == '=' || a == '(' || a == ')')  // ')'优先级难以确定，要特殊处理，这里只是为了能够与运算数区别开来
        return 0;
    else if (a == '+' || a == '-')
        return 1;
    else if (a == '*' || a == '/')
        return 2;
    else
        return 8;  // 数字符号优先，直接不进栈就打印
}
int priority_when_push(char a) {  // 入栈优先级 push into stack priority
    if (a == '=' || a == ')')  // ')'优先级难以确定，要特殊处理，这里只是为了能够与运算数区别开来
        return 0;
    else if (a == '+' || a == '-')
        return 1;
    else if (a == '*' || a == '/')
        return 2;
    else if (a == '(')
        return 3;
    else
        return 8;  // 数字符号优先，直接不进栈就打印
}
string transform_to_postfix_expression(string target) {
    stack<char> s;
    string postfix;
    size_t pos = 0;  // target的游标
    char top;

    for (pos = 0; pos < target.size(); pos++) {
        if (priority_when_push(target[pos]) == 8) {  // 运算数
            postfix += target[pos];
        } else {  // 运算符
            if (s.empty()) {
                s.push(target[pos]);
            }  // 第一个运算符入栈
            else {
                if (target[pos] == ')') {  // 将'('之前的运算符全部弹出
                    do {
                        top = s.top();
                        if (top != '(') postfix += top;
                        s.pop();
                    } while (top != '(');
                } else {  // 栈内运算符优先级高于当前运算符优先级
                    while ((!s.empty()) && (in_stack_priority(top = s.top()) >= priority_when_push(target[pos]))) {
                        postfix += top;
                        s.pop();
                    }
                    s.push(target[pos]);  // 当前运算符压栈
                }
            }
        }
    }

    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
    return postfix;
}
