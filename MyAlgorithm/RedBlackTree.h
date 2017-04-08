#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <queue>
using namespace std;


const bool RED=true;
const bool BLACK=false;
//tree node
template <typename Type>
class TNode{
    friend ostream& operator<<(ostream& os, const TNode & a){   os<<a.key<<"_"<<a.color;   return os;}
public:
    TNode* p;//parent
    TNode* left;// left son
    TNode* right;//right son
    Type key;
    bool color;
public:
    TNode(){    p=left=right=NULL; key = 0;};
    //~TNode();
    TNode(const Type& key){ this->key=key;  p=left=right=NULL;};
    int compare(const Type& t);
};
template <typename Type>
int TNode<Type>::compare(const Type& t){
    //return key>t?1:(key=t?0:-1);
    if(key>t)   return 1;
    else if(key<t)  return -1;
    else    return 0;
}

// tree
template <typename Type>
class RBTree{
public:
    TNode<Type>* root;          //根 黑色
    TNode<Type>* nil;           //叶子，黑色
public:
    RBTree();
    ~RBTree();
    TNode<Type>* rb_search(const Type& key);
    bool rb_insert(TNode<Type>* tnode);         //像二叉查找树那样插入，并进一步调rb_insert_fixup来调整以维持红黑树性质
    TNode<Type>* rb_delete(TNode<Type>* tnode);
    void inorder(TNode<Type>* node,Type a[]);
    void levelorder();          //按层次遍历
    bool Insert(Type a);
    bool Delete(Type a);
private:
    TNode<Type>* min(TNode<Type>* x);           //从当前结点找最小，向左
    TNode<Type>* max(TNode<Type>* x);           //从当前结点找最大，向右
    TNode<Type>* successor(TNode<Type>* x);     //返回后继结点
    void left_rotate(TNode<Type>* x);
    void right_rotate(TNode<Type>* x);
    void rb_insert_fixup(TNode<Type>* z);
    void rb_delete_fixup(TNode<Type>* z);
    void freeTree(TNode<Type>* node);
};
template <typename Type>
bool RBTree<Type>::Delete(Type a){
    TNode<Type> *tmp = rb_search(a);
    if(tmp == nil)  return false;
    else{
        tmp = rb_delete(tmp);
        delete tmp;
        return true;
    }
}
template <typename Type>
bool RBTree<Type>::Insert(Type a){
    TNode<Type> *tmp = new TNode<Type>(a);
    if(rb_insert(tmp)){ return true;}
    else{   delete tmp; return false;}
}
template <typename Type>
RBTree<Type>::RBTree(){ //root=nil;
    root=nil=new TNode<Type>();     //root -> nil
    nil->color=BLACK;
}
template <typename Type>
RBTree<Type>::~RBTree(){
    freeTree(root);
    if(nil!=NULL){
        delete nil;
        nil=NULL;
    }
}
template <typename Type>
TNode<Type>* RBTree<Type>::min(TNode<Type>* x){     //一路向左,if x == nil then return nil
    if(x == nil)    return x;
    while(x->left!=nil){    x=x->left;}
    return x;
}
template <typename Type>
TNode<Type>* RBTree<Type>::max(TNode<Type>* x){
    if(x == nil)    return x;
    while(x->right!=nil){   x=x->right; }
    return x;
}
template <typename Type>
TNode<Type>* RBTree<Type>::successor(TNode<Type>* x){
    //如果右树存在，返回右树中的最小值结点
    if(x->right !=nil){
        return min(x->right);
    }
    //否则向上追溯祖先，必须是从左边回溯祖先，从右边回溯说明自己比祖先大
    TNode<Type>* y=x->p;
    while(y!=nil && x==y->right){
        x=y;
        y=y->p;
    }
    return y;
}
template <typename Type>
TNode<Type>* RBTree<Type>::rb_search(const Type& key){
    TNode<Type>* p=root;
    while(p!=nil){
        int result=p->compare(key);
        if(result==0){
            return p;
        }else if(result==1){
            p=p->left;
        }else{
            p=p->right;
        }
    }
    return p;
}
template <typename Type>
bool RBTree<Type>::rb_insert(TNode<Type>* tnode){
    TNode<Type>* x=root;
    TNode<Type>* y=nil;
    while(x!=nil){
        y=x;
        if(x->compare(tnode->key)==1){      //x->key > tnode->key
            x=x->left;
        }else if(x->compare(tnode->key)==-1){//x->key < tnode->key
            x=x->right;
        }
        else {  //key already in tree ,done nothing
            return false;
        }
    }
    tnode->p=y;
    if(y==nil){
        root=tnode;
    }else if(y->compare(tnode->key)==1){
        y->left=tnode;
    }else{
        y->right=tnode;
    }
    tnode->left=nil;
    tnode->right=nil;
    tnode->color=RED;           //初始设置为红色
    rb_insert_fixup(tnode);         //通过重着色和旋转保持红黑树性质
    return true;
}
template <typename Type>
void RBTree<Type>::left_rotate(TNode<Type>* x){
    TNode<Type>* y=x->right;
    x->right=y->left;
    if(y->left!=nil){
        y->left->p=x;
    }
    y->p=x->p;
    if(x->p==nil){
        root=y;
    }else{
        if(x->p->left==x){
            x->p->left=y;
        }else{
            x->p->right=y;
        }
    }
    y->left=x;
    x->p=y;
}
template <typename Type>
void RBTree<Type>::right_rotate(TNode<Type>* y){
    TNode<Type>* x=y->left;
//    cout<<*x<<" "<<*y<<" "<<*(x->left)<<endl;
    y->left=x->right;
    if(x->right!=nil){
        x->right->p=y;
    }
    x->p=y->p;
    if(x->p==nil){
        root=x;
    }else{
        if(y->p->left==y){
            y->p->left=x;
        }else{
            y->p->right=x;
        }
    }
    x->right=y;
    y->p=x;
//    cout<<"debug right_rotate:  "<<*x<<" "<<*y<<" "<<*(x->left)<<endl;
}
template <typename Type>
void RBTree<Type>::rb_insert_fixup(TNode<Type>* z){
    while(z->p->color==RED){    //z自己是红的，如果父亲也是红的，违反性质4
        if(z->p==z->p->p->left){    //left case
            TNode<Type>* y=z->p->p->right;  //祖父的右儿子，z's uncle
            if(y->color==RED){
                //case 1 : z's uncle is red, so toper layer is red, recolor and put violation upward
                z->p->color=BLACK;
                z->p->p->color=RED;
                y->color=BLACK;
                z=z->p->p;
            }else{//z's uncle is black
                if(z==z->p->right){
                    //case 2 : z's uncle is black, and z is right child, so left_rotate,
                    //in order to make zigzag form to left line form
                    z=z->p;
                    left_rotate(z);
                }
                //case 3 : z's uncle is black, and z is left child,left line form, so right_rotate
                //here no else, because no matter what path, it should pass case 3
                //like from case 1 to case 3 or from case 2 to case 3
                z->p->color=BLACK;
                z->p->p->color=RED;
                right_rotate(z->p->p);
            }
        }else{      //right case
            TNode<Type>* y=z->p->p->left;   //z's uncle
            if(y->color==RED){
                //case 4 : z's uncle is red, so toper layer is red, recolor and put violation upward
                z->p->color=BLACK;
                z->p->p->color=RED;
                y->color=BLACK;
                z=z->p->p;
            }else {//z's uncle is black
                if(z==z->p->left){
                    //case 5 : z's uncle is black, and z is left child, so right_rotate,
                    //in order to make zigzag form to right line form
                    z=z->p;
                    right_rotate(z);
                }
                //case 6 : z's uncle is black, and z is right child,right line form, so left_rotate
                //here no else, because no matter what path, it should pass case 6
                //like from case 4 to case 6 or from case 5 to case 6
                z->p->color=BLACK;
                z->p->p->color=RED;
                left_rotate(z->p->p);
            }

        }
    }
    root->color=BLACK;      //root always black
}

template <typename Type>
TNode<Type>* RBTree<Type>::rb_delete(TNode<Type>* tnode){
    TNode<Type>* y; //pointer to be deleted node
    if(tnode->left==nil || tnode->right==nil){
        y=tnode;
    }else{
        y=successor(tnode);
    }
    TNode<Type>* x;
    if(y->left!=nil){   //x 指向待删结点的单支儿子
        x=y->left;
    }else{
        x=y->right;
    }
    x->p=y->p;

    if(y->p==nil){
        root=x;
    }else{
        if(y->p->left==y){
            y->p->left=x;
        }else{
            y->p->right=x;
        }
    }
    if(y!=tnode){       //y为待删结点
        tnode->key=y->key;
    }
    //如果y是红的，不影响树高
    //如果是黑的，则需要调整
    if(y->color==BLACK){
        rb_delete_fixup(x);
    }

    return y;
}

template <typename Type>
void RBTree<Type>::rb_delete_fixup(TNode<Type>* x){
    TNode<Type>* w; //x's brother
    while(x!=root && x->color==BLACK){
        if(x==x->p->left){  // left case
            w=x->p->right;  // x's right brother
            if(w->color==RED){
                //case 1: x's right brother w is red, turn into case 2,3,4
                w->color=BLACK;
                x->p->color=RED;
                left_rotate(x->p);
                w=x->p->right;
            }
            //here no else, because case1 turn into case 2,3,4 to handle
            if(w->left->color==BLACK && w->right->color==BLACK){
                //case 2: x的兄弟w是黑色，w的两个孩子都是黑色
                w->color=RED;
                x=x->p;
            }else {
                if(w->right->color==BLACK){
                    //case 3: x的兄弟w是黑色，w的左孩子是红色，右孩子是黑色,turn into case 4
                    w->left->color=BLACK;
                    w->color=RED;
                    right_rotate(w);
                    w=x->p->right;
                }
                //here no else, because case3 turn into case 4 to handle
                //case 4 : x的兄弟w是黑色，w的右孩子是红色
                w->color=x->p->color;
                x->p->color=BLACK;
                w->right->color=BLACK;
                left_rotate(x->p);
                x=root;
            }

        }
        else{  // right case
            w=x->p->left;  // x's left brother
            if(w->color==RED){
                //case 5: x's left brother w is red, turn into case 6,7,8
                w->color=BLACK;
                x->p->color=RED;
                right_rotate(x->p);
                w=x->p->left;
            }
            //here no else, because case5 turn into case 6,7,8 to handle
            if(w->left->color==BLACK && w->right->color==BLACK){
                //case 6: x的兄弟w是黑色，w的两个孩子都是黑色
                w->color=RED;
                x=x->p;
            }else { //w的两个孩子至少有一个红的
                if(w->left->color==BLACK){
                    //case 7: x的兄弟w是黑色，w的右孩子是红色，左孩子是黑色,turn into case 8
                    w->right->color=BLACK;
                    w->color=RED;
                    left_rotate(w);
                    w=x->p->left;
                }
                //here no else, because case7 turn into case 8 to handle
                //case 8 : x的兄弟w是黑色，w的左右孩子是红色
                w->color=x->p->color;
                x->p->color=BLACK;
                w->left->color=BLACK;
                right_rotate(x->p);
                x=root;
            }
        }
    }
    x->color=BLACK;
}

template <typename Type>
void RBTree<Type>::freeTree(TNode<Type>* node){
    if(node==nil){
        return;
    }
    if(node->left!=nil){
        freeTree(node->left);
    }
    if(node->right!=nil){
        freeTree(node->right);
    }
    delete node;
    node=NULL;
}
template <typename Type>
void RBTree<Type>::inorder(TNode<Type>* node,Type a[]){
    static int count=0;
    if(node==nil){
        return;
    }
    inorder(node->left,a);
    a[count++]=node->key;
    inorder(node->right,a);
}
template <class T>
void RBTree<T>::levelorder(){
    if(root == nil)    return;
    queue<TNode<T>*> q;
    TNode<T> *currentnode = root;
    q.push(currentnode);
    while(!q.empty()){
        currentnode = q.front();
        q.pop();
        if(currentnode == nil ) continue;
        cout<<*currentnode<<" ";
        if(currentnode->left != nil)   q.push(currentnode->left);
        if(currentnode->right != nil)   q.push(currentnode->right);
    }
    cout<<endl;
}




void  test_RBTree(){
    //例子来源  ： http://blog.csdn.net/v_JULY_v/article/details/6284050
    RBTree<int> tree;
    //insert 12 1 9 2 0 11 7 19 4 15 18 5 14 13 10 16 6 3 8 17
    tree.Insert(12);
    tree.Insert(1);
    tree.Insert(9);
    tree.Insert(2);
    tree.Insert(0);
    tree.Insert(11);
    tree.Insert(7);
    tree.Insert(19);
    tree.Insert(4);
    tree.Insert(15);
    tree.Insert(18);
    tree.Insert(5);
    tree.Insert(14);
    tree.Insert(13);
    tree.Insert(10);
    tree.Insert(16);
    tree.Insert(6);
    tree.Insert(3);
    tree.Insert(8);
    tree.Insert(17);
    tree.levelorder();
    //insert 12 1 9 2 0 11 7 19 4 15 18 5 14 13 10 16 6 3 8 17
    tree.Delete(12);
    tree.Delete(1);
    tree.Delete(9);
    tree.Delete(2);
    tree.levelorder();
    tree.Delete(0);
    tree.Delete(11);
    tree.Delete(7);
    tree.Delete(19);
    tree.levelorder();
    tree.Delete(4);
    tree.Delete(15);
    tree.Delete(18);
    tree.Delete(5);
    tree.levelorder();
    tree.Delete(14);
    tree.Delete(13);
    tree.Delete(10);
    tree.Delete(16);
    tree.levelorder();
    tree.Delete(6);
    tree.Delete(3);
    tree.Delete(8);
    tree.Delete(17);
    tree.levelorder();

    getchar();

}



#endif
