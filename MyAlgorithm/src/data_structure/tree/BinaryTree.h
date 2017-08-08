#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "utilities.h"

using namespace std;

/**
 * 二叉树(无序), 提供插入, 前中后序遍历,判断data是否在树中, 找路径从root到data, 两个节点之间最近祖先和路径
 */
template <class T>
class TreeNode {
public:
    TreeNode(T x) : data{x} {}

public:
    TreeNode *left{nullptr}, *right{nullptr};
    T data;
};
template <class T>
class StackItem {  // 后序遍历时压栈用
public:
    TreeNode<T> *p;
    bool RCVisited;  // right child visited
};

template <class T>
class BinaryTree {
public:
    BinaryTree() { isRecursive = false; }
    ~BinaryTree() { clear(); }
    void clear() {
        delete_all(root);
        root = nullptr;
    }
    void delete_all(TreeNode<T> *tn) {
        if (tn == nullptr) return;
        if (tn->left != nullptr) delete_all(tn->left);
        if (tn->right != nullptr) delete_all(tn->right);
        delete tn;
    }

    void insert(T parent, T data, bool is_right);  // 将data插入树中parent的左边或右边
    void set_root(T data) { root = new TreeNode<T>(data); }

    void in_order() {  // 中序遍历
        iterateResult.clear();
        isRecursive ? in_order_recursive(root) : in_order_iterative();
    }

    void in_order_recursive(TreeNode<T> *current_node);
    void in_order_iterative();

    void pre_order() {  // 前序遍历
        iterateResult.clear();
        isRecursive ? pre_order_recursive(root) : pre_order_iterative();
    };
    void pre_order_recursive(TreeNode<T> *current_node);
    void pre_order_iterative();

    void post_order() {  // 后续遍历
        iterateResult.clear();
        isRecursive ? post_order_recursive(root) : post_order_iterative();
    };
    void post_order_recursive(TreeNode<T> *current_node);
    void post_order_iterative();

    void level_order();  // 按层次遍历

    vector<T> find_path(T data);                     // 找到从根到data的path
    TreeNode<T> *findNode(T data, TreeNode<T> *tn);  // 树中找到data节点,递归掉，初始tn为root
    vector<T> nearestAncestor(T a, T b);             // 最近先祖
    TreeNode<T> *getRoot() { return root; }

public:
    bool isRecursive;  // 递归还是非递归,游标迭代 iterative
    int size{0};
    TreeNode<T> *root{nullptr};
    vector<T> iterateResult;
};
template <class T>
void BinaryTree<T>::insert(T parent, T data, bool is_right) {  // 将data插入树中parent的左边或右边
    if (root == nullptr)
        root = new TreeNode<T>(data);
    else {
        TreeNode<T> *parent_ptr = findNode(parent, root);
        if (parent_ptr != nullptr) {
            if (!is_right && (parent_ptr->left == nullptr))
                parent_ptr->left = new TreeNode<T>(data);
            else if (is_right && (parent_ptr->right == nullptr))
                parent_ptr->right = new TreeNode<T>(data);
        }
    }
}

template <class T>
void BinaryTree<T>::in_order_recursive(TreeNode<T> *current_node) {
    if (current_node == nullptr) return;
    in_order_recursive(current_node->left);
    iterateResult.push_back(current_node->data);
    in_order_recursive(current_node->right);
}

template <class T>
void BinaryTree<T>::pre_order_recursive(TreeNode<T> *current_node) {
    if (current_node == nullptr) return;
    iterateResult.push_back(current_node->data);
    pre_order_recursive(current_node->left);
    pre_order_recursive(current_node->right);
}

template <class T>
void BinaryTree<T>::post_order_recursive(TreeNode<T> *current_node) {
    if (current_node == nullptr) return;
    post_order_recursive(current_node->left);
    post_order_recursive(current_node->right);
    iterateResult.push_back(current_node->data);
}

template <class T>
void BinaryTree<T>::in_order_iterative() {
    stack<TreeNode<T> *> s;
    TreeNode<T> *current_node = root;
    while (1) {
        while (current_node != nullptr) {
            s.push(current_node);
            current_node = current_node->left;
        }
        if (!s.empty()) {
            current_node = s.top();
            s.pop();
            iterateResult.push_back(current_node->data);
            current_node = current_node->right;
        } else
            break;
    }
}

template <class T>
void BinaryTree<T>::pre_order_iterative() {
    stack<TreeNode<T> *> s;
    TreeNode<T> *current_node = root;
    while (1) {
        while (current_node != nullptr) {
            iterateResult.push_back(current_node->data);

            s.push(current_node);
            current_node = current_node->left;
        }
        if (!s.empty()) {
            current_node = s.top();
            s.pop();
            current_node = current_node->right;
        } else
            break;
    }
}

template <class T>
void BinaryTree<T>::post_order_iterative() {
    stack<StackItem<T> > s;
    StackItem<T> si;
    TreeNode<T> *current_node = root;
    while (1) {
        while (current_node != nullptr) {
            si.p = current_node;
            si.RCVisited = false;  // 首次进栈
            s.push(si);
            current_node = current_node->left;
        }
        if (!s.empty()) {
            si = s.top();
            s.pop();
            current_node = si.p;
            if (!si.RCVisited) {      // 从左子女回溯
                si.RCVisited = true;  // 下次从有子女回溯，有子女已经遍历
                s.push(si);           // 二次进栈
                current_node = current_node->right;
            } else {  // 从右子女回溯
                iterateResult.push_back(current_node->data);
                current_node = nullptr;
            }
        } else
            break;
    }
}

template <class T>
void BinaryTree<T>::level_order() {
    iterateResult.clear();
    if (root == nullptr) return;
    queue<TreeNode<T> *> q;
    int cnt = 1, nextLevelCnt = 0;
    TreeNode<T> *current_node;
    q.push(root);
    while (cnt) {
        current_node = q.front();
        q.pop();

        iterateResult.push_back(current_node->data);

        if (current_node->left != nullptr) {
            q.push(current_node->left);
            nextLevelCnt++;
        }
        if (current_node->right != nullptr) {
            q.push(current_node->right);
            nextLevelCnt++;
        }
        cnt--;
        if (cnt == 0) {
            // cout << endl; // if print level layer, then use this to break line
            cnt = nextLevelCnt;
            nextLevelCnt = 0;
        }
    }
}

template <class T>
vector<T> BinaryTree<T>::find_path(T data) {
    stack<StackItem<T> > s, s1;
    StackItem<T> si;
    TreeNode<T> *current_node = root;
    while (1) {
        while (current_node != nullptr) {
            si.p = current_node;
            si.RCVisited = false;  // 首次进栈
            s.push(si);
            current_node = current_node->left;
        }
        if (!s.empty()) {
            si = s.top();
            s.pop();
            current_node = si.p;
            if (!si.RCVisited) {      // 从左子女回溯
                si.RCVisited = true;  // 下次从有子女回溯，有子女已经遍历
                s.push(si);           // 二次进栈
                current_node = current_node->right;
            } else {  // 从右子女回溯
                if (data == current_node->data) {
                    break;
                }
                current_node = nullptr;
            }
        } else
            break;
    }
    vector<T> path(0);
    if (!s.empty()) {
        while (!s.empty()) {
            s1.push(s.top());
            s.pop();
        }
        path.resize(s1.size() + 1);
        int pos = 0;
        while (!s1.empty()) {
            path[pos++] = s1.top().p->data;
            s1.pop();
        }
        path[pos++] = data;
    }
    return path;
}

template <class T>
TreeNode<T> *BinaryTree<T>::findNode(T data, TreeNode<T> *tn) {
    TreeNode<T> *result = nullptr;
    if (tn == nullptr)
        return nullptr;
    else if (tn->data == data)
        return tn;
    else if ((result = findNode(data, tn->left)) != nullptr)
        return result;  // 左树找到
    else if ((result = findNode(data, tn->right)) != nullptr)
        return result;  // 右数找到
    else
        return result;
}

template <class T>
vector<T> BinaryTree<T>::nearestAncestor(T a, T b) {
    vector<T> path1 = find_path(a);
    vector<T> path2 = find_path(b);
    vector<T> path3;
    size_t pos = 0;
    if (path1.size() > 0 && path2.size() > 0) {
        while (1) {  // find first not equal element
            if (pos >= path1.size() || pos >= path2.size()) break;
            if (path1[pos] != path2[pos])
                break;
            else {
                pos++;
            }
        }
        pos--;  // 前一个位置就是最近先祖
        for (size_t i = path1.size() - 1; i > pos; i--) {
            path3.push_back(path1[i]);
        }
        path3.push_back(path1[pos]);
        for (size_t i = pos + 1; i < path2.size(); i++) {
            path3.push_back(path2[i]);
        }
    }
    return path3;
}

#endif
