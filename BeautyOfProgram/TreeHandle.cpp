#include "MyUtility.h"

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    int leftMaxValue;   //左子树最长距离
    int rightMaxValue;  //右子树最长距离
};

void build_by_preorder_inorder();  //根据先序和中序遍历结果构建树
//根据先序和中序遍历结果构建树
TreeNode* build_by_preorder_inorder(vector<int>& preorder, vector<int>& inorder, int pStart, int pEnd, int iStart,
                                    int iEnd);
void level_order(TreeNode* root);              //按层次遍历
void findMaxLen(TreeNode* root, int* maxLen);  //树中节点间的最大距离  No.3.8

int main() {
    build_by_preorder_inorder();  //重建二叉树 No. 3.9  层次遍历 No. 3.10
    return 0;
}

void level_order(TreeNode* root) {
    if (root == nullptr) return;
    queue<TreeNode*> q;
    TreeNode* currentNode = root;
    q.push(currentNode);
    int levelCnt = 1, nextLevelCnt = 0;
    while (levelCnt > 0) {
        currentNode = q.front();
        cout << currentNode->data << " ";
        q.pop();
        --levelCnt;
        if (currentNode->left != nullptr) {
            q.push(currentNode->left);
            ++nextLevelCnt;
        }
        if (currentNode->right != nullptr) {
            q.push(currentNode->right);
            ++nextLevelCnt;
        }
        if (levelCnt == 0) {
            cout << endl;
            levelCnt = nextLevelCnt;
            nextLevelCnt = 0;
        }
    }
    cout << endl;
}
//根据先序和中序遍历结果构建树
void build_by_preorder_inorder() {
    vector<int> preorder{1, 2, 4, 3, 5, 6};
    vector<int> inorder{4, 2, 1, 5, 3, 6};
    int len = preorder.size();
    TreeNode* root = build_by_preorder_inorder(preorder, inorder, 0, len - 1, 0, len - 1);
    cout << root->data << endl;
    level_order(root);
}
//根据先序和中序遍历结果构建树
TreeNode* build_by_preorder_inorder(vector<int>& preorder, vector<int>& inorder, int pStart, int pEnd, int iStart,
                                    int iEnd) {
    TreeNode* root = new TreeNode;
    root->data = preorder[pStart];
    int inorderIndex = find(inorder.begin(), inorder.end(), root->data) - inorder.begin();  // 找到rootValue在中序的位置
    int len1 = inorderIndex - iStart;                                                       // 左子树大小
    if (len1 > 0)
        root->left = build_by_preorder_inorder(preorder, inorder, pStart + 1, pStart + len1, iStart, inorderIndex - 1);
    else
        root->left = nullptr;
    int len2 = iEnd - inorderIndex;  //右子树大小
    if (len2 > 0)
        root->right = build_by_preorder_inorder(preorder, inorder, pStart + 1 + len1, pEnd, inorderIndex + 1, iEnd);
    else
        root->right = nullptr;
    return root;
}
void findMaxLen(TreeNode* root, int* maxLen) {
    //遍历到叶子结点，返回
    if (root == nullptr) return;

    //如果左子树为空，那么该节点左边最长距离为0
    if (root->left == nullptr) root->leftMaxValue = 0;

    //如果右子树为空，那么该节点右边最长距离为0
    if (root->right == nullptr) root->rightMaxValue = 0;

    //如果左子树不为空，递归寻找左子树最长距离
    if (root->left != nullptr) findMaxLen(root->left, maxLen);

    //如果右子树不为空，递归寻找右子树最长距离
    if (root->right != nullptr) findMaxLen(root->right, maxLen);

    //计算左子树中距离根节点的最长距离
    if (root->left != nullptr) {
        if (root->left->leftMaxValue > root->left->rightMaxValue)
            root->leftMaxValue = root->left->leftMaxValue + 1;
        else
            root->leftMaxValue = root->left->rightMaxValue + 1;
    }

    //计算右子树中距离根节点的最长距离
    if (root->right != nullptr) {
        if (root->right->leftMaxValue > root->right->rightMaxValue)
            root->rightMaxValue = root->right->leftMaxValue + 1;
        else
            root->rightMaxValue = root->right->rightMaxValue + 1;
    }

    //更新最长距离
    if (root->leftMaxValue + root->rightMaxValue > *maxLen) *maxLen = root->leftMaxValue + root->rightMaxValue;
}
