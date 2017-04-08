#ifndef QUEUEWITHMAX_H
#define QUEUEWITHMAX_H

#include "myutility.h"

#define MAXN    100

class StackWithMax{
public:
        StackWithMax(){
            stackTop = -1;
            maxStackItemIndex = -1;
        }

        bool isEmpty() {     return stackTop == -1;}
        bool isFull() {return stackTop == MAXN - 1; }

        void push(int x) {
            if(this->isFull()) {   cout<<"the stack is full now."<<endl;}
            else {
                stackItem[++stackTop] = x;
                //如果压入堆栈的值比之前记录的最大值大，那么那之前的最大值记录在
                //link2NextMaxItem[stackTop]的位置，把当前最大值在堆栈stackItem
                //中的位置用maxStackItemIndex保存
                if(x > maxValue()) {
                    link2NextMaxItem[stackTop] = maxStackItemIndex;
                    maxStackItemIndex = stackTop;
                }
                else    link2NextMaxItem[stackTop] = -1;
            }
        }

        int pop(){
            int ret;
            if(this->isEmpty()) {    cout<<"the stack is empty."<<endl;    }
            else {
                ret = stackItem[stackTop];
                //如果pop出的值是当前的最大值，那么则需要将之前保存到link2NextMaxItem[stackTop]
                //中的最大值取出，更新maxStackItemIndex的值
                if( stackTop == maxStackItemIndex )    {
                    maxStackItemIndex = link2NextMaxItem[stackTop];
                }
            }
            --stackTop;
            return ret;
        }

        //取出堆栈中当前的最大值
        int maxValue(){
            if(maxStackItemIndex >= 0)
                return stackItem[maxStackItemIndex];
            else{
                return INT_MIN;
            }
        }
        void printItems() {
            for (int i = 0; i <= stackTop; ++i) {
                cout<<" "<<stackItem[i];
            }
        }
        void reversePrintItems() {
            for (int i = stackTop; i >= 0; --i) {
                cout<<" "<<stackItem[i];
            }
        }
    private:
        int stackItem[MAXN];
        int stackTop;
        int link2NextMaxItem[MAXN];     //维护一个按序index
        int maxStackItemIndex;          //|maxStackItemIndex|存储当前堆栈中最大元素的index
};

class QueueWithMax{
public:
        int maxValue(int x, int y) {
            return x>y?x:y;
        }

        //返回队列中最大值
        int max() {
            return maxValue(stackA.maxValue(), stackB.maxValue());
        }

        void printQueue() {
            stackA.reversePrintItems();
            stackB.printItems();
            cout<<endl;
        }

        //在队列末尾插入元素
        void insertQueue(int x) {    stackB.push(x);}

        //删除并返回队首元素,
        //如果stackA中是空，则先将stackB中的所有元素pop到stackA中，
        //这样stackB中先插入的元素就会pop到stackA中的顶部
        int deQueue() {
            if(stackA.isEmpty()) {
                while(!stackB.isEmpty())
                    stackA.push(stackB.pop());
            }
            return stackA.pop();
        }
    private:
        StackWithMax stackA;    //维护出队列操作
        StackWithMax stackB;    //维护入队列操作
};



#endif
