#ifndef BINARYTREE_H
#define BINARYTREE_H

/**
 * 二叉树(无序), 提供插入, 前中后序遍历,判断data是否在树中, 找路径从root到data, 两个节点之间最近祖先和路径
 */
#include "utilities.h"
using namespace std;

template <class T>
class TreeNode{
public:
    TreeNode(T x) : data{x}, left{NULL}, right{NULL} {}
public:
    TreeNode *left, *right;
    T data;
};
template <class T>
class StackItem{        //后序遍历时压栈用
public:
    TreeNode<T> *p;
    bool RCVisited;     //right child visited
};

template <class T>
class BinaryTree{
public:
    BinaryTree(){
        root = NULL;
        isRecursive = false;
    }
    ~BinaryTree(){  clear(); }
    void clear(){
        delete_all(root);
        root = NULL;
    }
    void delete_all(TreeNode<T> *tn){
        if(tn == NULL) return;
        if(tn->left != NULL) delete_all(tn->left);
        if(tn->right != NULL) delete_all(tn->right);
        delete tn;
    }

    void insert(T parent, T data, bool is_right);  //将data插入树中parent的左边或右边
    void set_root(T data){
        root = new TreeNode<T>(data);
    }

    void inorder(){              //中序遍历
        cout<<"inorder : ";
        isRecursive ? inorder_recursive(root) : inorder_iterative();
        cout<<endl;
    };
    void inorder_recursive(TreeNode<T> *current_node);
    void inorder_iterative();

    void preorder(){            //前序遍历
        cout<<"preorder : ";
        isRecursive ? preorder_recursive(root) : preorder_iterative();
        cout<<endl;
    };
    void preorder_recursive(TreeNode<T> *current_node);
    void preorder_iterative();

    void postorder(){          //后续遍历
        cout<<"postorder : ";
        isRecursive ? postorder_recursive(root) : postorder_iterative();
        cout<<endl;
    };
    void postorder_recursive(TreeNode<T> *current_node);
    void postorder_iterative();

    void level_order();          //按层次遍历

    vector<T> find_path(T data);      //找到从根到data的path
    TreeNode<T>* findNode(T data,TreeNode<T> *tn);      //树中找到data节点,递归掉，初始tn为root
    vector<T> nearestAncestor(T a,T b);     //最近先祖
    TreeNode<T>* getRoot(){ return root; }
public:
    bool isRecursive;   //递归还是非递归,游标迭代 iterative
    TreeNode<T> *root;
};
template <class T>
void BinaryTree<T>::insert(T parent, T data, bool is_right){        //将data插入树中parent的左边或右边
    if(root == NULL) root = new TreeNode<T>(data);
    else{
        TreeNode<T>* parent_ptr = findNode(parent, root);
        if(parent_ptr != NULL){
            if(!is_right && (parent_ptr->left == NULL) )
                parent_ptr->left = new TreeNode<T>(data);
            else if(is_right && (parent_ptr->right == NULL))
                parent_ptr->right = new TreeNode<T>(data);
        }
    }
}

template <class T>
void BinaryTree<T>::inorder_recursive(TreeNode<T> *current_node){
    if(current_node == NULL) return;
    inorder_recursive(current_node->left);
    cout<<current_node->data<<" ";
    inorder_recursive(current_node->right);
}

template <class T>
void BinaryTree<T>::preorder_recursive(TreeNode<T> *current_node){
    if(current_node == NULL) return;
    cout<<current_node->data<<" ";
    preorder_recursive(current_node->left);
    preorder_recursive(current_node->right);
}

template <class T>
void BinaryTree<T>::postorder_recursive(TreeNode<T> *current_node){
    if(current_node == NULL) return;
    postorder_recursive(current_node->left);
    postorder_recursive(current_node->right);
    cout<<current_node->data<<" ";
}

template <class T>
void BinaryTree<T>::inorder_iterative(){
    stack<TreeNode<T> *> s;
    TreeNode<T> *current_node = root;
    while(1){
        while(current_node != NULL){
            s.push(current_node);
            current_node = current_node->left;
        }
        if(!s.empty()){
            current_node = s.top();
            s.pop();
            cout<<current_node->data<<" ";
            current_node = current_node->right;
        }
        else break;
    }
}

template <class T>
void BinaryTree<T>::preorder_iterative(){
    stack<TreeNode<T> *> s;
    TreeNode<T> *current_node = root;
    while(1){
        while(current_node != NULL){
            cout<<current_node->data<<" ";
            s.push(current_node);
            current_node = current_node->left;
        }
        if(!s.empty()){
            current_node = s.top();
            s.pop();
            current_node = current_node->right;
        }
        else break;
    }
}

template <class T>
void BinaryTree<T>::postorder_iterative(){
    stack<StackItem<T> > s;
    StackItem<T> si;
    TreeNode<T> *current_node = root;
    while(1){
        while(current_node != NULL){
            si.p = current_node;
            si.RCVisited = false;                   //首次进栈
            s.push(si);
            current_node = current_node->left;
        }
        if(!s.empty()){
            si = s.top();
            s.pop();
            current_node = si.p;
            if(!si.RCVisited ){                     //从左子女回溯
                si.RCVisited = true;                //下次从有子女回溯，有子女已经遍历
                s.push(si);                         //二次进栈
                current_node = current_node->right;
            } else{                                   //从右子女回溯
                cout<<current_node->data<<" ";
                current_node = NULL;
            }
        }
        else break;
    }
}

template <class T>
void BinaryTree<T>::level_order(){
    cout<<"level_order : "<<endl;
    if(root == NULL) return;
    queue<TreeNode<T>*> q;
    int cnt = 1, nextLevelCnt = 0;
    TreeNode<T> *current_node;
    q.push(root);
    while(cnt){
        current_node = q.front();
        q.pop();
        cout<<current_node->data<<" ";
        if(current_node->left != NULL){
            q.push(current_node->left);
            nextLevelCnt++;
        }
        if(current_node->right != NULL){
            q.push(current_node->right);
            nextLevelCnt++;
        }
        cnt--;
        if(cnt == 0){
            cout<<endl;
            cnt = nextLevelCnt;
            nextLevelCnt = 0;
        }
    }
    cout<<"level_order end."<<endl;
}

template <class T>
vector<T> BinaryTree<T>::find_path(T data){
    stack<StackItem<T> > s,s1;
    StackItem<T> si;
    TreeNode<T> *current_node = root;
    while(1){
        while(current_node != NULL){
            si.p = current_node;
            si.RCVisited = false;               //首次进栈
            s.push(si);
            current_node = current_node->left;
        }
        if(!s.empty()){
            si = s.top();
            s.pop();
            current_node = si.p;
            if(!si.RCVisited ){                 //从左子女回溯
                si.RCVisited = true;            //下次从有子女回溯，有子女已经遍历
                s.push(si);                     //二次进栈
                current_node = current_node->right;
            }
            else{                               //从右子女回溯
                if(data == current_node->data){break;}
                current_node = NULL;
            }
        }
        else break;
    }
    vector<T> path(0);
    if(!s.empty()){
        while(!s.empty()){
            s1.push(s.top());
            s.pop();
        }
        path.resize(s1.size()+1);
        int pos = 0;
        while(!s1.empty()){
            path[pos++] = s1.top().p->data;
            s1.pop();
        }
        path[pos++] = data;
    }
    return path;
}

template <class T>
TreeNode<T> * BinaryTree<T>::findNode(T data,TreeNode<T> *tn){
    TreeNode<T>* result = NULL;
    if(tn == NULL)  return NULL;
    else if(tn->data == data)   return tn;
    else if((result = findNode(data,tn->left)) != NULL) return result;  //左树找到
    else if((result = findNode(data,tn->right)) != NULL) return result; //右数找到
    else return result;
}

template <class T>
vector<T> BinaryTree<T>::nearestAncestor(T a,T b){
    vector<T> path1 = find_path(a);
    vector<T> path2 = find_path(b);
    vector<T> path3;
    int pos = 0;
    if(path1.size() >0  && path2.size() > 0){
        while(1){   //find first not equal element
            if(pos >=path1.size() || pos >= path2.size()) break;
            if(path1[pos] != path2[pos])    break;
            else{ pos++;}
        }
        pos--;      //前一个位置就是最近先祖
        for(int i = path1.size()-1; i > pos; i--){  path3.push_back(path1[i]);}
        path3.push_back(path1[pos]);
        for(int i = pos+1; i <path2.size();i++){  path3.push_back(path2[i]);}
    }
    return path3;
}

void test_BinaryTree(){
    BinaryTree<int> bt;
    bt.set_root(3);
    bt.insert(3,5,true);
    bt.insert(5,4,false);
    bt.insert(3,1,false);
    bt.insert(1,-1,false);
    bt.insert(1,2,true);

    bt.inorder();
    bt.preorder();
    bt.postorder();
    bt.level_order();
    cout<<"find path for "<<1<<" : "<<bt.find_path(1)<<endl;
    cout<<"nearestAncestor for "<<-1<<" vs "<<2<<" : "<<bt.nearestAncestor(-1, 2)<<endl;
}


#endif
