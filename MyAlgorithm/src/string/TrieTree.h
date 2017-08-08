#ifndef TRIE_TREE_H
#define TRIE_TREE_H

#include <cstring>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

const unsigned int Branch_Num = 26;
const unsigned int Max_Prefix_Len = 100;

/**
 * 前缀树 tire (Re[trie]ve Tree)
 * 对字符串的排序, 若采用一些经典的排序算法, 则时间复杂度一般为O(n*lgn),
 * 但若采用Trie树, 则时间复杂度仅为O(n).
 * Trie树又名字典树, 从字面意思即可理解, 这种树的结构像英文字典一样, 相邻的单词一般前缀相同,
 * 之所以时间复杂度低, 是因为其采用了以空间换取时间的策略.
 * 针对字符串排序的Trie树(假设在这里字符串都是小写字母), 每个结点有26个分支,
 * 每个分支代表一个字母, 结点存放的是从root节点到达此结点的路经上的字符组成的字符串.
 * 将每个字符串插入到trie树中, 到达特定的结尾节点时, 在这个节点上进行标记, 如插入"afb",
 * 第一个字母为a, 沿着a往下, 然后第二个字母为f, 沿着f往下, 第三个为b, 沿着b往下,
 * 由于字符串最后一个字符为'\0', 因而结束, 不再往下了, 然后在这个节点上标记afb.count++, 即其个数增加1.
 * 之后, 通过前序遍历此树, 即可得到字符串从小到大的顺序.
 */

class TrieNode {
public:
    // count > 0 该节点一定是叶节点, 但他可能有子孙, 因为子孙的前缀可能就是一个合法的单词,
    // count 记录该处单词出现的次数
    int count;
    TrieNode* branches[Branch_Num];  // 分支
    char* prefix;                    // 记录到达此处的路径上的所有字母组成的前缀
    TrieNode();
};
TrieNode::TrieNode() {
    count = 0;
    for (unsigned int i = 0; i < Branch_Num; i++) branches[i] = nullptr;
    prefix = new char[Max_Prefix_Len];
    prefix[0] = '\0';
}

class Trie {
public:
    TrieNode* root;
    vector<pair<string, int>> result;  // sort result, <word, frequency>

public:
    Trie() { root = new TrieNode(); };
    ~Trie();
    void insert(const char* str);
    void sort(TrieNode* node);
    void sort();

private:
    void clear(TrieNode* node);
};

Trie::~Trie() { clear(root); }
void Trie::clear(TrieNode* node) {
    if (node != nullptr) {
        for (unsigned int i = 0; i < Branch_Num; i++) {
            clear(node->branches[i]);
        }
        delete node;
    }
}
void Trie::insert(const char* str) {
    int i = 0;
    TrieNode* current_node = root;

    // 将str[i]插入到trie树中
    while (str[i] != '\0') {
        // 如果包含str[i]的分支存在, 则新建此分支
        if (current_node->branches[str[i] - 'a'] == nullptr) {
            current_node->branches[str[i] - 'a'] = new TrieNode();
            // 将父节点中的字符串添加到当前节点的字符串中
            strcat(current_node->branches[str[i] - 'a']->prefix, current_node->prefix);

            char increment_prefix[2];  // 新节点的前缀增加
            increment_prefix[0] = str[i];
            increment_prefix[1] = '\0';

            // 将str[i]添加到当前节点的字符串中
            strcat(current_node->branches[str[i] - 'a']->prefix, increment_prefix);
            current_node = current_node->branches[str[i] - 'a'];
        } else {
            current_node = current_node->branches[str[i] - 'a'];
        }
        i++;
    }
    current_node->count++;
}

// 采用前序遍历
void Trie::sort(TrieNode* node) {
    if (node != nullptr) {
        if (node->count != 0) {
            result.push_back({node->prefix, node->count});
        }
        for (unsigned int i = 0; i < Branch_Num; i++) {
            sort(node->branches[i]);
        }
    }
}

void Trie::sort() {
    result.clear();
    sort(root);
}

#endif
