#ifndef ALGORITHMS_MIN_STACK_H
#define ALGORITHMS_MIN_STACK_H

#include <stack>

using namespace std;

/**
 * 设计带有get_min的stack
 */
class MinStack {
private:
    stack<int> dataStack;
    stack<int> minStack;

public:
    void push(int x) {
        dataStack.push(x);
        if (minStack.empty()) {
            minStack.push(x);
        } else if (minStack.top() < x) {
            minStack.push(minStack.top());
        } else {
            minStack.push(x);
        }
    }

    void pop() {
        dataStack.pop();
        minStack.pop();
    }

    int top() { return dataStack.top(); }

    int get_min() { return minStack.top(); }

    bool empty() { return dataStack.empty(); }
};

#endif
