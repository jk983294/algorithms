#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


class KMP
{
public:
    void fail(){        //calcuulate pat fail function
        int len = pat.length();
        f.resize(len);
        f[0] = -1;
        for (int i =1; i<len;i++)
        {
            int m = f[i-1];
            while((m>=0) && (pat[i] != pat[m+1])) m = f[m];//find max m
            if (pat[i] == pat[m+1])
            {
                f[i] = m+1;
            }
            else f[i] = -1;
        }
    };

    void printfail(){
        for (vector<int>::iterator itr = f.begin(); itr < f.end();itr++)
        {
            cout<<*itr<<" ";
        }
        cout<<endl;
    };

    void kmp(){//find pat in s
        fail();

        int i = 0,j = 0;
        int lenS = s.length();
        int lenP = pat.length();
        while ((i<lenS) && (j<lenP))
        {
            if (s[i] == pat[j])
            {
                i++;
                j++;
            }
            else{
                if (j==0)
                {
                    i++;
                }
                else{
                    j= f[j-1] +1;
                }
            }
        }

        if ((j<lenP) || (lenP== 0))
        {
            cout<<"no target pattern string"<<endl;
        }
        else{//first matched pattern string pos in s
            cout<<"target pattern string in s locate in pos "<<i-lenP<<endl;
        }
    }


    void EKMP(string s,string t)//s[]为主串，t[]为模版串
    {
        vector<int> next,extend; //extend[i]表示原 串以第i开始与模式串的前缀的最长匹配
        int i,j,p,l;
        int len=t.size();
        int len1=s.size();
        next.resize(len,0);
        extend.resize(len1,0);
//        memset(next,0,sizeof(next));
//        memset(extend,0,sizeof(extend));
        next[0]=len;
        j=0;
        while(1+j<len&&t[j]==t[1+j])j++;
        next[1]=j;
        int a=1;
        for(i=2; i<len; i++)
        {
            p=next[a]+a-1;
            l=next[i-a];
            if(i+l<p+1)next[i]=l;
            else
            {
                j=max(0,p-i+1);
                while(i+j<len&&t[i+j]==t[0+j])j++;
                next[i]=j;
                a=i;
            }
        }
        j=0;
        while(j<len1&&j<len&&s[j]==t[j])j++;
        extend[0]=j;
        a=0;
        for(i=1; i<len1; i++)
        {
            p=extend[a]+a-1;
            l=next[i-a];
            if(l+i<p+1)extend[i]=next[i-a];
            else
            {
                j=max(0,p-i+1);
                while(i+j<len1&&j<len&&s[i+j]==t[j])j++;
                extend[i]=j;
                a=i;
            }
        }
    }

    string s;
    string pat;
    vector<int> f;    //fail函数
};

void test_KMP(){

    KMP kmp;
    kmp.s = "fksabcabcacabdjf";
    kmp.pat = "abcabcacab";
    kmp.kmp();
    kmp.printfail();
}
