#include <iostream>
#include <queue>
#include <string>

using namespace std;

/**
 * this is binary search tree with thread, but it is not balanced tree
 * thread used for fast in-order traverse
 */

struct ThreadNode {
    int key{-1};
    ThreadNode *left{nullptr};
    ThreadNode *right{nullptr};
    bool isLeftThread{true};
    bool isRightThread{true};

    ThreadNode() = default;
    explicit ThreadNode(int key_) : key(key_) {}

    void copy_value_from(const ThreadNode *node) { key = node->key; }
};

ostream &operator<<(ostream &s, const ThreadNode &node) {
    s << "(" << node.key << ", " << (node.left ? node.left->key : -1) << ", " << (node.right ? node.right->key : -1)
      << ", " << node.isLeftThread << ", " << node.isRightThread << ")";
    return s;
}

class ThreadTree {
public:
    ThreadTree();
    void insert(int key);
    ThreadNode *find(int key);
    void in_order();
    void level_order();
    void clear();
    /**
     * if node has only one child, then that child will be this node's parent's child
     * if node has two child, then max left tree node or min right tree node will be this node's parent's child
     */
    bool remove(int key);

    ThreadNode *inOrderSuccessor(ThreadNode *ptr);
    ThreadNode *inOrderPredecessor(ThreadNode *ptr);

    bool empty() {
        return root == nullptr;  // return sentinel.left == &sentinel;
    }

private:
    ThreadNode *find_parent(int key);
    ThreadNode *leftmost(ThreadNode *n);
    ThreadNode *no_child_case(ThreadNode *root_, ThreadNode *parent, ThreadNode *current);
    ThreadNode *one_child_case(ThreadNode *root_, ThreadNode *parent, ThreadNode *current);
    ThreadNode *two_children_case(ThreadNode *root_, ThreadNode *parent, ThreadNode *current);

    /**
     * sentinel.left = leftmost node
     * sentinel.right = rightmost node
     */
    ThreadNode sentinel;
    ThreadNode *root{nullptr};
};

// Constructor
ThreadTree::ThreadTree() {
    sentinel.left = &sentinel;
    sentinel.right = &sentinel;
}

void ThreadTree::clear() {
    ThreadNode *i = sentinel.left;
    while (i && i != &sentinel) {
        if (i->isRightThread) {
            ThreadNode *tmp = i;
            i = i->right;
            delete tmp;
        } else
            i = leftmost(i->right);
    }
    root = nullptr;
    sentinel.left = &sentinel;
    sentinel.right = &sentinel;
}

void ThreadTree::insert(int key) {
    if (root == nullptr) {
        root = new ThreadNode(key);
        sentinel.left = root;
        sentinel.right = root;
        root->left = &sentinel;
        root->right = &sentinel;
    } else {
        ThreadNode *parent = find_parent(key);
        if (parent == nullptr) {
            cerr << key << " is already in tree root" << endl;
        } else if (parent->key < key) {
            if (!parent->isRightThread && parent->right->key == key) {
                cerr << key << " is already in tree" << endl;
            } else {
                auto tmp = new ThreadNode(key);
                tmp->left = parent;
                tmp->right = parent->right;
                if (parent->right == &sentinel) {
                    sentinel.right = tmp;
                }
                parent->right = tmp;
                parent->isRightThread = false;
            }
        } else {
            if (!parent->isLeftThread && parent->left->key == key) {
                cerr << key << " is already in tree" << endl;
            } else {
                auto tmp = new ThreadNode(key);
                tmp->right = parent;
                tmp->left = parent->left;
                if (parent->left == &sentinel) {
                    sentinel.left = tmp;
                }
                parent->left = tmp;
                parent->isLeftThread = false;
            }
        }
    }
}

ThreadNode *ThreadTree::find(int key) {
    if (root == nullptr) {
        return nullptr;
    } else {
        ThreadNode *tmp = root;
        while (true) {
            if (tmp->key == key)
                return tmp;
            else if (tmp->key < key) {
                if (tmp->isRightThread)
                    return nullptr;
                else
                    tmp = tmp->right;
            } else {
                if (tmp->isLeftThread)
                    return nullptr;
                else
                    tmp = tmp->left;
            }
        }
    }
}

ThreadNode *ThreadTree::find_parent(int key) {
    if (root == nullptr) {
        return nullptr;
    } else {
        ThreadNode *tmp = root;
        ThreadNode *parent = nullptr;
        while (true) {
            if (tmp->key == key) {
                return parent;
            } else if (tmp->key < key) {
                if (tmp->isRightThread)
                    return tmp;
                else {
                    parent = tmp;
                    tmp = tmp->right;
                }
            } else {
                if (tmp->isLeftThread)
                    return tmp;
                else {
                    parent = tmp;
                    tmp = tmp->left;
                }
            }
        }
    }
}

void ThreadTree::in_order() {
    ThreadNode *i = sentinel.left;
    while (i && i != &sentinel) {
        cout << *i << " ";

        if (i->isRightThread)
            i = i->right;
        else
            i = leftmost(i->right);
    }
    cout << endl;
}

ThreadNode *ThreadTree::leftmost(ThreadNode *n) {
    if (n == nullptr || n == &sentinel) return nullptr;

    while (!n->isLeftThread) n = n->left;
    return n;
}

void ThreadTree::level_order() {
    cout << sentinel << "  ";
    if (root == nullptr) return;

    queue<ThreadNode *> q;
    q.push(root);
    while (!q.empty()) {
        ThreadNode *current = q.front();
        q.pop();
        cout << *current << "  ";
        if (!current->isLeftThread) {
            q.push(current->left);
        }
        if (!current->isRightThread) {
            q.push(current->right);
        }
    }
    cout << endl;
}

bool ThreadTree::remove(int key) {
    if (root == nullptr) return false;
    ThreadNode *parent = nullptr, *current = root;
    bool found = false;

    // find target node and its parent
    while (true) {
        if (key == current->key) {
            found = true;
            break;
        }
        parent = current;
        if (key < current->key) {
            if (!current->isLeftThread)
                current = current->left;
            else
                break;
        } else {
            if (!current->isRightThread)
                current = current->right;
            else
                break;
        }
    }

    if (!found)
        return false;
    else if (!current->isLeftThread && !current->isRightThread)  // two children
        root = two_children_case(root, parent, current);
    else if (!current->isLeftThread)  // only left child
        root = one_child_case(root, parent, current);
    else if (!current->isRightThread)  // only right child
        root = one_child_case(root, parent, current);
    else  // no child
        root = no_child_case(root, parent, current);
    return true;
}

ThreadNode *ThreadTree::no_child_case(ThreadNode *root_, ThreadNode *parent, ThreadNode *current) {
    if (parent == nullptr) {  // node to be deleted is root
        root_ = nullptr;
        sentinel.left = &sentinel;
        sentinel.right = &sentinel;
    } else if (current == parent->left) {
        parent->isLeftThread = true;
        parent->left = current->left;
        if (parent->left == &sentinel) {
            sentinel.left = parent;
        }
    } else {
        parent->isRightThread = true;
        parent->right = current->right;
        if (parent->right == &sentinel) {
            sentinel.right = parent;
        }
    }
    delete current;
    return root_;
}

/**
 * only one child case
 */
ThreadNode *ThreadTree::one_child_case(ThreadNode *root_, ThreadNode *parent, ThreadNode *current) {
    ThreadNode *predecessor = inOrderPredecessor(current);
    ThreadNode *successor = inOrderSuccessor(current);
    ThreadNode *child;

    if (!current->isLeftThread)
        child = current->left;
    else
        child = current->right;

    // node to be deleted is root
    if (parent == nullptr) {
        root_ = child;
    } else if (current == parent->left) {
        parent->left = child;
    } else {
        parent->right = child;
    }

    if (!current->isLeftThread) {
        predecessor->right = successor;
        if (successor == &sentinel) {
            sentinel.right = predecessor;
        }
    } else if (!current->isRightThread) {
        successor->left = predecessor;
        if (predecessor == &sentinel) {
            sentinel.left = successor;
        }
    }
    delete current;
    return root_;
}

/**
 * copy right tree max node, then delete that node
 */
ThreadNode *ThreadTree::two_children_case(ThreadNode *root_, ThreadNode *parent, ThreadNode *current) {
    // find current's successor and also track its parent
    ThreadNode *parentSuccessor = current;
    ThreadNode *successor = current->right;
    while (successor->left != current) {
        parentSuccessor = successor;
        successor = successor->left;
    }

    current->copy_value_from(successor);

    if (successor->isLeftThread && successor->isRightThread)
        root_ = no_child_case(root_, parentSuccessor, successor);
    else
        root_ = one_child_case(root_, parentSuccessor, successor);
    return root_;
}

// in-order successor
ThreadNode *ThreadTree::inOrderSuccessor(ThreadNode *ptr) {
    if (ptr->isRightThread) return ptr->right;

    ThreadNode *current = ptr->right;
    while (current->left != ptr) current = current->left;
    return current;
}

ThreadNode *ThreadTree::inOrderPredecessor(ThreadNode *ptr) {
    if (ptr->isLeftThread) return ptr->right;

    ThreadNode *current = ptr->left;
    while (current->right != ptr) current = current->right;
    return current;
}

int main() {
    ThreadTree tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(3);
    tree.insert(6);
    tree.insert(5);
    tree.insert(1);

    cout << "level order traverse :";
    tree.level_order();
    cout << "in-order traverse :";
    tree.in_order();
    cout << "search 2: " << tree.find(2)->key << endl;
    cout << "search 4: " << tree.find(4)->key << endl;

    cout << "search predecessor of 4: " << *tree.inOrderPredecessor(tree.find(4)) << endl;
    cout << "search successor of 4: " << *tree.inOrderSuccessor(tree.find(4)) << endl;

    tree.remove(3);
    tree.level_order();

    tree.clear();
    cout << "tree empty: " << tree.empty() << endl;
    return 0;
}
