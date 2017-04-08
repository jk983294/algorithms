#include "TreeHandle.h"


void levelorder(treenode* root){
    if(root == NULL)    return;
    queue<treenode*> q;
    treenode* currentnode = root;
    q.push(currentnode);
    int levelcnt = 1 , nextlevelcnt = 0;
    while(levelcnt > 0){
        currentnode = q.front();
        cout<<currentnode->data<<" ";
        q.pop();
        --levelcnt;
        if(currentnode->left != NULL) {
            q.push(currentnode->left);
            ++nextlevelcnt;
        }
        if(currentnode->right != NULL) {
            q.push(currentnode->right);
            ++nextlevelcnt;
        }
        if (levelcnt == 0){
            cout<<endl;
            levelcnt = nextlevelcnt;
            nextlevelcnt = 0;
        }
    }
    cout<<endl;
}
//根据先序和中序遍历结果构建树
void bulid_by_preorder_inorder(){
    int apreoder[] = { 1, 2, 4, 3, 5, 6};
    int ainoder[] = { 4, 2, 1, 5, 3, 6};
    int len = sizeof(apreoder)/sizeof(int);
    vector<int> preoder = to_vector(apreoder,len);
    vector<int> inoder = to_vector(ainoder,len);
    treenode* root = bulid_by_preorder_inorder(preoder,inoder,0,len-1,0,len-1);
    cout<<root->data<<endl;
    levelorder(root);
}
//根据先序和中序遍历结果构建树
treenode* bulid_by_preorder_inorder(vector<int> &preoder,vector<int> &inoder,int pstart,int pend,int istart,int iend){
    treenode *root = new treenode;
    root->data = preoder[pstart];
    int inorder_index = find(inoder.begin(),inoder.end(),root->data) - inoder.begin();  //找到rootvalue在中序的位置
    int len1 = inorder_index - istart;  //左子树大小
    if(len1 > 0)    root->left = bulid_by_preorder_inorder(preoder,inoder,pstart+1,pstart+len1,istart,inorder_index-1);
    else root->left = NULL;
    int len2 = iend - inorder_index;    //右子树大小
    if(len2 > 0)    root->right = bulid_by_preorder_inorder(preoder,inoder,pstart+1+len1,pend,inorder_index+1,iend);
    else root->right = NULL;
    return root;
}
void findMaxLen(pNode root, int *maxLen) {
    //遍历到叶子结点，返回
    if(root == NULL)
        return;

    //如果左子树为空，那么该节点左边最长距离为0
    if(root->left == NULL)
        root->leftMaxValue = 0;

    //如果右子树为空，那么该节点右边最长距离为0
    if(root->right == NULL)
        root->rightMaxValue = 0;

    //如果左子树不为空，递归寻找左子树最长距离
    if(root->left != NULL)
        findMaxLen(root->left, maxLen);

    //如果右子树不为空，递归寻找右子树最长距离
    if(root->right != NULL)
        findMaxLen(root->right, maxLen);

    //计算左子树中距离根节点的最长距离
    if(root->left != NULL) {
        if(root->left->leftMaxValue > root->left->rightMaxValue)
            root->leftMaxValue = root->left->leftMaxValue + 1;
        else
            root->leftMaxValue = root->left->rightMaxValue + 1;
    }

    //计算右子树中距离根节点的最长距离
    if(root->right != NULL) {
        if(root->right->leftMaxValue > root->right->rightMaxValue)
            root->rightMaxValue = root->right->leftMaxValue + 1;
        else
            root->rightMaxValue = root->right->rightMaxValue + 1;
    }

    //更新最长距离
    if(root->leftMaxValue + root->rightMaxValue > *maxLen)
        *maxLen = root->leftMaxValue + root->rightMaxValue;
}
