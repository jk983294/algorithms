#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "BinaryTree.h"

template <class T>
class BinarySearchTree : public BinaryTree<T>{
public:
    void insert(T key);     //有序插入
    TreeNode<T> * search(T key);
    bool deleteKey(T key);     //删叶节点或只有一个子女的节点很容易，如果删带两个子女的节点，采取将左树最大节点或者右树最小节点代替被删节点
    //合并两棵有序树，左树key全部小于右树，左树最大节点为根，返回树根节点指针
    TreeNode<T> * TwoWayJoin(TreeNode<T> *left, TreeNode<T> *right);
};
template <class T>
TreeNode<T> * BinarySearchTree<T>::TwoWayJoin(TreeNode<T> *left, TreeNode<T> *right){
    if(left == NULL)    return right;
    if(right == NULL)   return left;
    TreeNode<T> *t = left;
    TreeNode<T> *p = t;     //p是t的双亲
    while(t->right != NULL){    //找左子树最大节点
        p=t;  t = p->right;
    }
    if(t->data == left->data)   {   //左子树没有右子树，直接将right拼接到他的右数
        left->right = right;
        return left;
    }
    else{
        p->right = NULL;    //最大节点从left树上取下来
        t->left = left;
        t->right = right;
        return t;
    }
}
template <class T>
bool BinarySearchTree<T>::deleteKey(T key){  //如果删带两个子女的节点，采取将左树最大节点代替被删节点
    TreeNode<T> *t = BinaryTree<T>::root;
    TreeNode<T> *p = t;     //p是t的双亲
    if((t != NULL)  && t->data == key)  {   //删除的是根节点
        BinaryTree<T>::root = TwoWayJoin(t->left,t->right);
        delete t;
        return true;
    }

    while(t != NULL){
        if( key == t->data)  {
            cout<<"find key : "<<key<<endl;
            break;
        }
        if( key < t->data) {  p=t;  t = p->left;}
        else {  p=t;  t = p->right;}
    }
    if(t == NULL)
        return false;
    else if((t->left == NULL)  && (t->right == NULL)){  //要删除的是叶子节点
        if(key < p->data) { //p的左儿子
            p->left = NULL;
            delete t;
        } else {
            p->right = NULL;
            delete t;
        }
    }
    else if((t->left != NULL) && (t->right == NULL)){   //要删除的只有左儿子
        if(key < p->data) { //p的左儿子
            p->left = t->left;
            delete t;
        } else {
            p->right = t->left;
            delete t;
        }
    }
    else if((t->left == NULL) && (t->right != NULL)){   //要删除的只有右儿子
        if(key < p->data) {  //p的左儿子
            p->left = t->right;
            delete t;
        } else {
            p->right = t->right;
            delete t;
        }
    } else {   //要删除的有左右儿子，找到左树上的最大值
        if(key < p->data) {   //p的左儿子
            p->left =TwoWayJoin(t->left,t->right);
            delete t;
        } else {
            p->right =TwoWayJoin(t->left,t->right);
            delete t;
        }
    }
    return true;
}
template <class T>
TreeNode<T> * BinarySearchTree<T>::search(T key){
    TreeNode<T> *t = BinaryTree<T>::root;
    while(t != NULL){
        if( key == t->data)  {
            cout<<"find key : "<<key<<endl;
            return t;
        }
        if( key < t->data)
            t = t->left;
        else
            t = t->right;
    }
    return NULL;
}
template <class T>
void BinarySearchTree<T>::insert(T x){
    bool isSuccess = true;
    if(BinaryTree<T>::root == NULL){   BinaryTree<T>::root = new TreeNode<T>(x);}
    else{
        TreeNode<T> *current = BinaryTree<T>::root;
        TreeNode<T> *next = BinaryTree<T>::root;
        do{
            current = next;
            if(current->data< x){    next = current->right;}
            else if(current->data> x){   next = current->left;}
            else {isSuccess = false;}
        } while(next!= NULL); //find leaf
        if(current->data< x){
            current->right = new TreeNode<T>(x);
        } else if(current->data> x){
            current->left = new TreeNode<T>(x);
        }
    }
    if(isSuccess){  BinaryTree<T>::size++;}
}
void test_BinarySearchTree(){
    BinarySearchTree<int> bst;
    bst.insert(3);
    bst.insert(5);
    bst.insert(4);
    bst.insert(1);
    bst.insert(-1);
    bst.insert(2);

    bst.levelorder();
    bst.search(1);
    bst.deleteKey(1);
    bst.levelorder();
//    bt.nearestAncestor(-1,2);
}

#endif
