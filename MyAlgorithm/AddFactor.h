/*
找到一个数s 的加法因子集合
一个集合，集合中的所有数加起来 = s
集合中的数不重复
**/
#include <iostream>
#include <set>
#include "utilities.h"
using namespace std;

set<int> s;
void print_s(){
    for(set<int>::iterator itr = s.begin(); itr != s.end(); itr++)
        cout<<*itr<<" ";
}
void divideToSub(int n,int morethan){
    int half = n/2;
    int j;
    for(int i = morethan + 1; i <= half; i++){
        j = n - i;
        if(j < morethan) continue;
        else if(i == j) continue;
        else if( (s.find(i)!=s.end()) || (s.find(j)!=s.end()))  continue;
        else {
            cout<<s<<i<<" "<<j<<" "<<endl;
            s.insert(i);
            divideToSub(j,i);
            s.erase(i);
        }
    }
}

void testAddFactor(int s){
    cout<<"testAddFactor begin."<<endl;
    divideToSub(s,0);
    cout<<"testAddFactor end."<<endl;
}
