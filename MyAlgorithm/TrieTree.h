#ifndef TRIE_TREE_H
#define TRIE_TREE_H

/**
前缀树 tire
对字符串的排序，若采用一些经典的排序算法，则时间复杂度一般为O(n*lgn)，
但若采用Trie树，则时间复杂度仅为O(n)。
Trie树又名字典树，从字面意思即可理解，这种树的结构像英文字典一样，相邻的单词一般前缀相同，
之所以时间复杂度低，是因为其采用了以空间换取时间的策略。
针对字符串排序的Trie树(假设在这里字符串都是小写字母)，每个结点有26个分支，
每个分支代表一个字母，结点存放的是从root节点到达此结点的路经上的字符组成的字符串。
将每个字符串插入到trie树中，到达特定的结尾节点时，在这个节点上进行标记，如插入"afb"，
第一个字母为a，沿着a往下，然后第二个字母为f，沿着f往下，第三个为b，沿着b往下，
由于字符串最后一个字符为'\0'，因而结束，不再往下了，然后在这个节点上标记afb.count++，
即其个数增加1.
之后，通过前序遍历此树，即可得到字符串从小到大的顺序。
*/


#include <iostream>
#include <string.h>
using namespace std;

const unsigned int Branch_Num = 26;
const unsigned int Max_Prefix_Len = 100;

class Node
{
public:
    //count>0,该节点一定是叶节点，但他可能有子孙，因为子孙的前缀可能就是一个合法的单词，
    //count 记录该处单词出现的次数
    int count;
    Node* branches[Branch_Num];    //分支
    char* prefix;                        //记录到达此处的路径上的所有字母组成的前缀
    Node();
};
Node::Node()
{
    count = 0;
    for(unsigned int i = 0; i < Branch_Num; i++)
        branches[i] = NULL;
    prefix = new char[Max_Prefix_Len];
    prefix[0] = '\0';
}

class Trie
{
public:
    Node* root;
public:
    Trie(){    root = new Node();  };
    void insert(char* str);
    void output(Node* &node);
};
void Trie::insert(char* str)
{
    int i = 0;
    Node* current_node = root;

    //将str[i]插入到trie树中
    while(str[i] != '\0')
    {
        //如果包含str[i]的分支存在，则新建此分支
        if(current_node->branches[str[i] - 'a'] == NULL)
        {
            current_node->branches[str[i] - 'a'] = new Node();
            //将父节点中的字符串添加到当前节点的字符串中
            strcat(current_node->branches[str[i] - 'a']->prefix, current_node->prefix);

            char increment_prefix[2];  //新节点的前缀增加
            increment_prefix[0] = str[i];
            increment_prefix[1] = '\0';

            //将str[i]添加到当前节点的字符串中
            strcat(current_node->branches[str[i] - 'a']->prefix, increment_prefix);
            current_node = current_node->branches[str[i] - 'a'];
        }
        else
        {
            current_node = current_node->branches[str[i] - 'a'];
        }
        i++;
    }
    current_node->count++;
}

//采用前序遍历
void Trie::output(Node* &node)
{
    if(node != NULL)
    {
        if(node->count != 0)
        {
            cout<<node->prefix<<" occurs "<<node->count<<" times"<<endl;
        }
        for(unsigned int i = 0; i < Branch_Num; i++)
        {
            output(node->branches[i]);
        }
    }
}


//程序未考虑delete动态内存
void test_TireTree()
{
    //建立trie树
    Trie trie;
    trie.insert("zbdfasd");
    trie.insert("zbcfd");
    trie.insert("zbcdfdasfasf");
    trie.insert("abcdaf");
    trie.insert("defdasfa");
    trie.insert("fedfasfd");
    trie.insert("dfdfsa");
    trie.insert("dadfd");
    trie.insert("dfdfasf");
    trie.insert("abcfdfa");
    trie.insert("fbcdfd");
    trie.insert("abcdaf");
    trie.output(trie.root);
}

#endif