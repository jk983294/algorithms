#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

int isp(char a) //栈内优先级 in stack priority
{
    //')'优先级难以确定，要特殊处理，这里只是为了能够与运算数区别开来
    if(a == '=' || a == '(' || a == ')')
        return 0;
    else if(a == '+' || a == '-')
        return 1;
    else if(a == '*' || a == '/')
        return 2;
    else return 8;  //数字符号优先，直接不进栈就打印
}
int pisp(char a) //入栈优先级 push into stack priority
{
    //')'优先级难以确定，要特殊处理，这里只是为了能够与运算数区别开来
    if(a == '=' || a == ')')
        return 0;
    else if(a == '+' || a == '-')
        return 1;
    else if(a == '*' || a == '/')
        return 2;
    else if(a == '(') return 3;
    else return 8;  //数字符号优先，直接不进栈就打印
}
void transformToPostfixedExpress(string &target){
    stack<char> s;
    string postfixexp;
    int pos = 0;    //target的游标
    char top;

    for(pos = 0;pos <target.size();pos++){
        if(pisp(target[pos]) == 8){      //运算数
            postfixexp += target[pos];
        }
        else{       //运算符
            if(s.empty()){  s.push(target[pos]);}   //第一个运算符入栈
            else {
                if(target[pos] == ')'){ //将'('之前的运算符全部弹出
                    do{
                        top = s.top();
                        if(top!= '(')   postfixexp += top;
                        s.pop();
                    }while(top!= '(');
                }
                else{//栈内运算符优先级高于当前运算符优先级
                    while( (!s.empty()) && (isp(top = s.top()) >= pisp(target[pos]))){
                        postfixexp += top;
                        s.pop();
                    }
                    s.push(target[pos]);    //当前运算符压栈
                }
            }
        }
    }

    while(!s.empty())   {
        postfixexp += s.top();
        s.pop();
    }
    cout<<target<<endl<<postfixexp<<endl;
}


int test_PostFixedExp()
{
    string target("A*(B+C)*D");
    transformToPostfixedExpress(target);

    string target1("A/B-C+D*E-A*C");
    transformToPostfixedExpress(target1);

    string target2("((((A/B)-C)+(D*E))-(A*C))");
    transformToPostfixedExpress(target2);


    return 0;
}
