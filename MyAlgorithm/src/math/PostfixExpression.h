#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

/**
 * '(' is special operator, when push, its priority is highest, no operator can pop out from stack
 * while in stack, its priority is lowest, only ')' can pop it out
 */

class PostfixExpression {
private:
    map<char, int> priority;

    bool is_operator(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'; }

public:
    PostfixExpression() {
        priority['+'] = 0;
        priority['-'] = 0;
        priority['*'] = 1;
        priority['/'] = 1;
        priority['('] = 2;
    }

    string transform(string prefix_expression) {
        ostringstream oss;
        stack<char> s;
        for (char c : prefix_expression) {
            if (!is_operator(c)) {
                oss << c;
            } else {
                if (c == ')') {  // pop out all operator until meet '('
                    while (!s.empty()) {
                        char topOperator = s.top();
                        s.pop();
                        if (topOperator == '(') {
                            break;
                        } else {
                            oss << topOperator;
                        }
                    }
                } else {
                    while (!s.empty()) {
                        char topOperator = s.top();
                        if (topOperator == '(') {  // only ')' can pop out '('
                            break;
                        } else if (priority[topOperator] < priority[c]) {
                            break;
                        } else {
                            oss << topOperator;
                            s.pop();
                        }
                    }
                    s.push(c);
                }
            }
        }
        while (!s.empty()) {
            oss << s.top();
            s.pop();
        }
        return oss.str();
    }
};
