#ifndef TREEHANDLE_H
#define TREEHANDLE_H

#include "myutility.h"


typedef struct treenode{
    int data;
    treenode *left;
    treenode *right;
    int leftMaxValue;       //左子树最长距离
    int rightMaxValue;      //右子树最长距离
}treenode, *pNode;

void bulid_by_preorder_inorder();                       //根据先序和中序遍历结果构建树
treenode* bulid_by_preorder_inorder(vector<int> &preoder,vector<int> &inoder,int pstart,int pend,int istart,int iend);  //根据先序和中序遍历结果构建树
void levelorder(treenode* root);                        //按层次遍历
void findMaxLen(pNode root, int *maxLen);               //树中节点间的最大距离  No.3.8




#endif
