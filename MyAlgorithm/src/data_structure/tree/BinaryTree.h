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
class MaxSubBstResult {
public:
    int totalCount;
    TreeNode<T> *max;
    TreeNode<T> *min;

public:
    MaxSubBstResult(int c, TreeNode<T> *max_, TreeNode<T> *min_) : totalCount(c), max(max_), min(min_) {}
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

    void in_order_recursive(TreeNode<T> *currentNode);
    void in_order_iterative();

    void pre_order() {  // 前序遍历
        iterateResult.clear();
        isRecursive ? pre_order_recursive(root) : pre_order_iterative();
    };
    void pre_order_recursive(TreeNode<T> *currentNode);
    void pre_order_iterative();

    void post_order() {  // 后续遍历
        iterateResult.clear();
        isRecursive ? post_order_recursive(root) : post_order_iterative();
    };
    void post_order_recursive(TreeNode<T> *currentNode);
    void post_order_iterative();

    void level_order();  // 按层次遍历

    /**
     * DFS need visited flag
     */
    void dfs_without_visited_flag();  // 压栈先压右子树，然后左子树，这样就左树优先访问
    void dfs();                       // 能左先左，然后考虑右子女，两边都走不通了退栈
    void dfs_pre_order();             // 每次入栈前访问，退栈的时候不访问
    void dfs_post_order();            // 每次退栈的时候访问，入栈时不访问
    void dfs_in_order();              // 右子女压栈前访问，若右子女为空，则该节点退栈时访问

    vector<T> find_path(T data);                     // 找到从根到data的path
    TreeNode<T> *findNode(T data, TreeNode<T> *tn);  // 树中找到data节点,递归掉，初始tn为root
    vector<T> nearestAncestor(T a, T b);             // 最近先祖
    TreeNode<T> *getRoot() { return root; }

    TreeNode<T> *max_sub_bst();
    MaxSubBstResult<T> max_sub_bst_internal(TreeNode<T> *node, MaxSubBstResult<T> &currentBest);

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
void BinaryTree<T>::in_order_recursive(TreeNode<T> *currentNode) {
    if (currentNode == nullptr) return;
    in_order_recursive(currentNode->left);
    iterateResult.push_back(currentNode->data);
    in_order_recursive(currentNode->right);
}

template <class T>
void BinaryTree<T>::pre_order_recursive(TreeNode<T> *currentNode) {
    if (currentNode == nullptr) return;
    iterateResult.push_back(currentNode->data);
    pre_order_recursive(currentNode->left);
    pre_order_recursive(currentNode->right);
}

template <class T>
void BinaryTree<T>::post_order_recursive(TreeNode<T> *currentNode) {
    if (currentNode == nullptr) return;
    post_order_recursive(currentNode->left);
    post_order_recursive(currentNode->right);
    iterateResult.push_back(currentNode->data);
}

template <class T>
void BinaryTree<T>::in_order_iterative() {
    stack<TreeNode<T> *> s;
    TreeNode<T> *currentNode = root;
    while (1) {
        while (currentNode != nullptr) {
            s.push(currentNode);
            currentNode = currentNode->left;
        }
        if (!s.empty()) {
            currentNode = s.top();
            s.pop();
            iterateResult.push_back(currentNode->data);
            currentNode = currentNode->right;
        } else
            break;
    }
}

template <class T>
void BinaryTree<T>::pre_order_iterative() {
    stack<TreeNode<T> *> s;
    TreeNode<T> *currentNode = root;
    while (1) {
        while (currentNode != nullptr) {
            iterateResult.push_back(currentNode->data);

            s.push(currentNode);
            currentNode = currentNode->left;
        }
        if (!s.empty()) {
            currentNode = s.top();
            s.pop();
            currentNode = currentNode->right;
        } else
            break;
    }
}

template <class T>
void BinaryTree<T>::post_order_iterative() {
    stack<std::pair<TreeNode<T> *, bool>> s;
    TreeNode<T> *currentNode = root;
    while (1) {
        while (currentNode != nullptr) {
            s.push({currentNode, false});  // 首次进栈
            currentNode = currentNode->left;
        }
        if (!s.empty()) {
            auto node = s.top();
            s.pop();
            currentNode = node.first;
            if (!node.second) {                    // 从左子女回溯
                s.push({currentNode, true});       // 二次进栈
                currentNode = currentNode->right;  // 遍历右子女，下次从右子女回溯，右子女已经遍历
            } else {                               // 从右子女回溯
                iterateResult.push_back(currentNode->data);
                currentNode = nullptr;
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
    TreeNode<T> *currentNode;
    q.push(root);
    while (cnt) {
        currentNode = q.front();
        q.pop();

        iterateResult.push_back(currentNode->data);

        if (currentNode->left != nullptr) {
            q.push(currentNode->left);
            nextLevelCnt++;
        }
        if (currentNode->right != nullptr) {
            q.push(currentNode->right);
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
    stack<std::pair<TreeNode<T> *, bool>> s, s1;
    std::pair<TreeNode<T> *, bool> nodeState;
    TreeNode<T> *currentNode = root;
    while (1) {
        while (currentNode != nullptr) {
            nodeState.first = currentNode;
            nodeState.second = false;  // 首次进栈
            s.push(nodeState);
            currentNode = currentNode->left;
        }
        if (!s.empty()) {
            nodeState = s.top();
            s.pop();
            currentNode = nodeState.first;
            if (!nodeState.second) {      // 从左子女回溯
                nodeState.second = true;  // 下次从有子女回溯，有子女已经遍历
                s.push(nodeState);        // 二次进栈
                currentNode = currentNode->right;
            } else {  // 从右子女回溯
                if (data == currentNode->data) {
                    break;
                }
                currentNode = nullptr;
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
            path[pos++] = s1.top().first->data;
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

template <class T>
void BinaryTree<T>::dfs() {
    iterateResult.clear();
    unordered_map<TreeNode<T> *, bool> visited;
    stack<TreeNode<T> *> s;
    if (root) {
        visited[root] = true;
        iterateResult.push_back(root->data);
        s.push(root);
    }

    while (!s.empty()) {
        TreeNode<T> *current = s.top();
        if (current->left && !visited[current->left]) {
            visited[current->left] = true;
            iterateResult.push_back(current->left->data);
            s.push(current->left);
        } else if (current->right && !visited[current->right]) {
            visited[current->right] = true;
            iterateResult.push_back(current->right->data);
            s.push(current->right);
        } else {
            s.pop();
        }
    }
}

template <class T>
void BinaryTree<T>::dfs_pre_order() {
    iterateResult.clear();
    unordered_map<TreeNode<T> *, bool> visited;

    stack<TreeNode<T> *> s;
    if (root) {
        visited[root] = true;
        iterateResult.push_back(root->data);
        s.push(root);
    }

    while (!s.empty()) {
        TreeNode<T> *current = s.top();
        if (current->left && !visited[current->left]) {
            visited[current->left] = true;
            iterateResult.push_back(current->left->data);
            s.push(current->left);
        } else if (current->right && !visited[current->right]) {
            visited[current->right] = true;
            iterateResult.push_back(current->right->data);
            s.push(current->right);
        } else {
            s.pop();
        }
    }
}

template <class T>
void BinaryTree<T>::dfs_post_order() {
    iterateResult.clear();
    unordered_map<TreeNode<T> *, bool> visited;

    stack<TreeNode<T> *> s;
    if (root) {
        visited[root] = true;
        s.push(root);
    }

    while (!s.empty()) {
        TreeNode<T> *current = s.top();
        if (current->left && !visited[current->left]) {
            visited[current->left] = true;
            s.push(current->left);
        } else if (current->right && !visited[current->right]) {
            visited[current->right] = true;
            s.push(current->right);
        } else {
            s.pop();
            iterateResult.push_back(current->data);
        }
    }
}

template <class T>
void BinaryTree<T>::dfs_in_order() {
    iterateResult.clear();
    unordered_map<TreeNode<T> *, bool> visited;

    stack<TreeNode<T> *> s;
    if (root) {
        visited[root] = true;
        s.push(root);
    }

    while (!s.empty()) {
        TreeNode<T> *current = s.top();
        if (current->left && !visited[current->left]) {
            visited[current->left] = true;
            s.push(current->left);
        } else if (current->right && !visited[current->right]) {
            iterateResult.push_back(current->data);
            visited[current->right] = true;
            s.push(current->right);
        } else {
            if (!current->right) iterateResult.push_back(current->data);

            s.pop();
        }
    }
}

template <class T>
void BinaryTree<T>::dfs_without_visited_flag() {
    iterateResult.clear();

    stack<TreeNode<T> *> s;
    if (root) {
        s.push(root);
    }

    while (!s.empty()) {
        TreeNode<T> *current = s.top();
        s.pop();
        iterateResult.push_back(current->data);
        if (current->right) s.push(current->right);
        if (current->left) s.push(current->left);
    }
}

template <class T>
TreeNode<T> *BinaryTree<T>::max_sub_bst() {
    MaxSubBstResult<T> currentBest{0, nullptr, nullptr};
    max_sub_bst_internal(root, currentBest);
    return currentBest.max;
}

template <class T>
MaxSubBstResult<T> BinaryTree<T>::max_sub_bst_internal(TreeNode<T> *node, MaxSubBstResult<T> &currentBest) {
    if (node == nullptr)
        return {0, nullptr, nullptr};
    else if (node->left == nullptr && node->right == nullptr) {
        if (currentBest.totalCount == 0) {
            currentBest = {1, node, nullptr};
        }
        return {1, node, node};
    } else {
        MaxSubBstResult<T> leftResult = max_sub_bst_internal(node->left, currentBest);
        MaxSubBstResult<T> rightResult = max_sub_bst_internal(node->right, currentBest);

        if (node->left && leftResult.totalCount == 0) return leftResult;
        if (node->right && rightResult.totalCount == 0) return rightResult;
        if (node->left && leftResult.max->data >= node->data) return {0, nullptr, nullptr};
        if (node->right && rightResult.min->data <= node->data) return {0, nullptr, nullptr};

        MaxSubBstResult<T> result{0, nullptr, nullptr};
        result.totalCount = leftResult.totalCount + rightResult.totalCount + 1;
        result.max = (node->right ? rightResult.max : node);
        result.min = (node->left ? leftResult.min : node);

        if (currentBest.totalCount < result.totalCount) {
            currentBest = {result.totalCount, node, nullptr};
        }
        return result;
    }
}

#endif
