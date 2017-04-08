#include "stringhandle.h"



void longest_huiwen_substr(){
    string source_str = "12212321";
    char startchar = '$', delimiter = '#';                      //起始符  分隔符
    string newstr;
    newstr += startchar;    newstr += delimiter;
    for(int i = 0; i < source_str.size(); i++){    newstr += source_str[i];        newstr += delimiter;}
    cout << newstr << endl;
    int size1 = newstr.size();
    vector<int> p(size1 , 0);
    int mx = 0, id = 0;
    for(int i = 1; i <  size1; ++i){
        if(mx > i) p[i] = min( p[2*id - i] , mx - i );          //在边界mx内
        else p[i] = 1;                                          //p[i]超出边界mx，设置为1，然后慢慢累加计算长度
        while(i + p[i] < size1 && newstr[i - p[i]] == newstr[i + p[i]])  ++p[i];
        if(i + p[i] > mx){                                      //更新边界mx以及当前最大回文子串的中心id
            mx = i + p[i];
            id = i;
        }
    }
    int maxlen = 0, ii;
    for(int i = 1; i < size1; ++i){
        if(p[i] > maxlen){
            ii = i;
            maxlen = p[i];
        }
    }
    maxlen--;
    string maxsubstr;
    int start = ii - maxlen ;
    int end = ii + maxlen;
    for(int i = start; i <= end; ++i){
        if(newstr[i] != delimiter)
            maxsubstr += newstr[i];
    }
    cout <<maxsubstr<< endl;
}
int simlarity_of_two_string(string &a,int abegin,int aend,string &b,int bbegin,int bend ){
    if(abegin >= aend){
        return bend - bbegin;
    }else if (bbegin >= bend){
        return aend - abegin;
    }else if(a[abegin] == b[bbegin]){
        return simlarity_of_two_string(a,abegin+1,aend,b,bbegin+1,bend);
    }else{
        int sim1 = simlarity_of_two_string(a,abegin,aend,b,bbegin+1,bend);      //将b[bbegin]拷到a串对应处  或者 将b[bbegin]在b中删除
        int sim2 = simlarity_of_two_string(a,abegin+1,aend,b,bbegin,bend);      //将a[abegin]拷到b串对应处  或者 将a[abegin]在a中删除
        int sim3 = simlarity_of_two_string(a,abegin+1,aend,b,bbegin+1,bend);    //将a[abegin]修改为b[bbegin]  或者 将b[bbegin]修改为a[abegin]
        return min(sim1,min(sim2,sim3)) + 1;
    }
}

//两个字符串的相似度 1. 修改一个字符 2. 增加一个字符 3. 删除一个字符
int simlarity_of_two_string(string a,string b){
    int lena = a.size() , lenb = b.size();
    return simlarity_of_two_string(a,0,lena-1,b,0,lenb-1);
}

void my_kmp(){
    string target = "abaabaabkda";
    string patternstr = "abcabcacab";
    int len1 = target.size(), len2 = patternstr.size();
    vector<int> failed_pos(len2,-1);                        //f(i) 记录最大的k使得  p0...pk = pi-k...pi 找不到则为-1
    int i, j, before ;
    for ( i=1; i < len2; ++i ){                             //计算fail函数
        before =failed_pos[i -1]+1;
        while(before >= 0){
            if(patternstr[i] == patternstr[before]){
                failed_pos[i] = before;                     //回退之后找到头尾相等，记录
                break;
            }
            if(before == 0) {                               //一直退到pattern[0]还是头尾不等，则设置为-1
                failed_pos[i] = -1; break;
            }
            else before =failed_pos[before -1]+1;           //还是不相等，继续回溯
        }
    }
    cout<<"failed_pos : "<<failed_pos<<endl;
    i = j = 0;
    while(i < len1 && j < len2){
        if(target[i] == patternstr[j]){     //该位字符匹配，两串一起移动
            ++i;
            ++j;
        }
        else if(j == 0 ){                   //第一个字符就不匹配，则target字符串移动
            ++i;
        }
        else{                               //不匹配的时候，pattern串回退到fail[j-1] +1位置
            j = failed_pos[j-1] + 1;
        }
    }
    if(j == len2){    cout<<"find: "<<i-len2<<endl;}
    else{    cout<<"not found"<<endl;    }
}
//字符串移位包含问题
bool str_contain_circle_shift(string a,string b){
    a += a;
    cout<<a<<" "<<b<<endl;
    return a.find(b) != a.npos;
}
void basic_string_app(){
    char *a = "fdsffkadskasdf";
    char *b = "ads";
    cout<<strstr(a,b) - a<<endl;

    my_kmp();

    int v[] = { 3,7,4,9,5,8,1,10,13,6,-1};
    int size = sizeof(v)/sizeof(int);
    vector<int> index1;
    vector<int> x(v,v+size);
    make_vector_index(index1,size);
    cout<<index1<<endl;cout<<x<<endl;
    quicksort(x,index1,0,size-1);
    cout<<index1<<endl;cout<<x<<endl;
}
