#ifndef RBTREE_H_
#define RBTREE_H_

#include "RBtreeIterator.h"
#include "algorithm/algorithm.h"
#include "allocator/allocator.h"
#include "allocator/construct.h"
#include "util/pair.h"

namespace ktl {

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc = alloc>
class rb_tree {
protected:
    typedef void* void_pointer;
    typedef __rb_tree_node_base* base_ptr;
    typedef __rb_tree_node<Value> rb_tree_node;
    typedef simple_alloc<rb_tree_node, Alloc> rb_tree_node_allocator;

public:
    typedef Key key_type;
    typedef Value value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;

    typedef rb_tree_node* link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

protected:
    link_type get_node() { return rb_tree_node_allocator::allocate(); }
    void put_node(link_type p) { rb_tree_node_allocator::deallocate(p); }
    link_type create_node(const value_type& x) {
        link_type tmp = get_node();       // allocate space
        construct(&tmp->value_field, x);  // construct object
        return tmp;
    }

    link_type clone_node(link_type x) {
        link_type tmp = create_node(x->value_field);
        tmp->color = x->color;
        tmp->left = 0;
        tmp->right = 0;
        return tmp;
    }

    void destroy_node(link_type p) {
        destroy(&p->value_field);  // destruct object
        put_node(p);               // release space
    }

    void clear() { freeTree(root()); }

    void freeTree(link_type& node) {
        if (node == 0) return;
        if (left(node) != 0) freeTree(left(node));
        if (right(node) != 0) freeTree(right(node));
        put_node(node);
    }

protected:
    size_type node_count;     // total node count, not include header
    link_type header;         // trick, header leftmost, rightmost, parent is root
    Compare key_compare;      // functor
    KeyOfValue key_of_value;  // functor

    link_type& root() const { return (link_type&)header->parent; }
    link_type& leftmost() const { return (link_type&)header->left; }
    link_type& rightmost() const { return (link_type&)header->right; }

    // quick access
    static link_type& left(link_type x) { return (link_type&)(x->left); }
    static link_type& right(link_type x) { return (link_type&)(x->right); }
    static link_type& parent(link_type x) { return (link_type&)(x->parent); }
    static reference value(link_type x) { return x->value_field; }
    const Key& key(link_type x) { return key_of_value(value(x)); }
    static color_type& color(link_type x) { return (color_type&)(x->color); }

    // quick access
    static link_type& left(base_ptr x) { return (link_type&)(x->left); }
    static link_type& right(base_ptr x) { return (link_type&)(x->right); }
    static link_type& parent(base_ptr x) { return (link_type&)(x->parent); }
    static reference value(base_ptr x) { return ((link_type)x)->value_field; }
    const Key& key(base_ptr x) { return key_of_value(value(link_type(x))); }
    static color_type& color(base_ptr x) { return (color_type&)(link_type(x)->color); }
    static link_type minimum(link_type x) { return (link_type)__rb_tree_node_base::minimum(x); }
    static link_type maximum(link_type x) { return (link_type)__rb_tree_node_base::maximum(x); }

public:
    typedef __rb_tree_iterator<value_type, reference, pointer> iterator;
    typedef __rb_tree_iterator<value_type, const_reference, const_pointer> const_iterator;

private:
    // y is parent, x is y's child
    iterator __insert(base_ptr x_, base_ptr y_, const Value& v) {
        link_type x = (link_type)x_;
        link_type y = (link_type)y_;
        link_type z;
        if (y == header || x != 0 || key_compare(key_of_value(v), key(y))) {
            z = create_node(v);
            left(y) = z;
            if (y == header) {
                root() = z;
                rightmost() = z;
            } else if (y == leftmost()) {
                leftmost() = z;
            }
        } else {
            z = create_node(v);
            right(y) = z;
            if (y == rightmost()) rightmost() = z;
        }
        parent(z) = y;
        left(z) = 0;
        right(z) = 0;

        __rb_tree_rebalance(z, header->parent);
        ++node_count;
        return iterator(z);
    }

    link_type __copy(link_type x, link_type p);
    void __erase(link_type x);

    void init() {
        header = get_node();
        color(header) = __rb_tree_red;  // header is red, used to distingush header and root
        root() = 0;
        leftmost() = header;
        rightmost() = header;
    }

public:
    rb_tree(const Compare& comp = Compare()) : node_count(0), key_compare(comp) { init(); }

    ~rb_tree() {
        clear();
        put_node(header);
    }
    rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& operator=(
        const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x);

    void swap(rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x) {
        swap(node_count, x.node_count);
        swap(header, x.header);
    }

    template <class Iterator>
    void insert(Iterator first, Iterator last) {
        for (Iterator i = first; i < last; ++i) {
            insert_unique(*i);
        }
    }

public:
    Compare key_comp() const { return key_compare; }
    iterator begin() const { return leftmost(); }
    iterator end() const { return header; }  // nice trick for [)
    bool empty() const { return node_count == 0; }
    size_type size() const { return node_count; }
    size_type max_size() const { return size_type(-1); }

public:
    // all key should be different, if failed, return that node's iterator
    pair<iterator, bool> insert_unique(const value_type& v) {
        link_type y = header;
        link_type x = root();
        bool comp = true;
        while (x != 0) {
            y = x;
            comp = key_compare(key_of_value(v), key(x));
            x = comp ? left(x) : right(x);
        }
        // y is leaf, v will be y's child
        iterator j = iterator(y);
        if (comp) {            // v is left child of y
            if (j == begin())  // j is left most
                return pair<iterator, bool>(__insert(x, y, v), true);
            else {
                --j;
            }
        }

        if (key_compare(key(j.node), key_of_value(v))) return pair<iterator, bool>(__insert(x, y, v), true);
        // failed, must have dup key, return false
        return pair<iterator, bool>(j, false);
    }

    template <class iterator>
    void insert_unique(iterator first, iterator last) {
        for (auto it = first; it != last; it++) {
            insert_unique(*it);
        }
    }

    // allow same key
    iterator insert_equal(const value_type& v) {
        link_type y = header;
        link_type x = root();
        while (x != 0) {
            y = x;
            x = key_compare(key_of_value(v), key(x)) ? left(x) : right(x);
        }
        return __insert(x, y, v);  // x is insert position, y is x's parent
    }

    // x is new added node
    inline void __rb_tree_rebalance(__rb_tree_node_base* x, __rb_tree_node_base*& root) {
        x->color = __rb_tree_red;                                   // new node is red
        while (x != root && x->parent->color == __rb_tree_red) {    // parent is red
            if (x->parent == x->parent->parent->left) {             // parent is grandpa's left
                __rb_tree_node_base* y = x->parent->parent->right;  // y is uncle
                if (y && y->color == __rb_tree_red) {               // uncle exist and red
                    x->parent->color = __rb_tree_black;
                    y->color = __rb_tree_black;
                    x->parent->parent->color = __rb_tree_red;
                    x = x->parent->parent;
                } else {                          // no uncle or uncle is black
                    if (x == x->parent->right) {  // new node is right child of parent
                        x = x->parent;
                        __rb_tree_rotate_left(x, root);
                    }
                    x->parent->color = __rb_tree_black;
                    x->parent->parent->color = __rb_tree_red;
                    __rb_tree_rotate_right(x->parent->parent, root);
                }
            } else {                                               // parent is grandpa's right
                __rb_tree_node_base* y = x->parent->parent->left;  // y is uncle
                if (y && y->color == __rb_tree_red) {              // uncle exist and red
                    x->parent->color = __rb_tree_black;
                    y->color = __rb_tree_black;
                    x->parent->parent->color = __rb_tree_red;
                    x = x->parent->parent;
                } else {                         // no uncle or uncle is black
                    if (x == x->parent->left) {  // new node is left child of parent
                        x = x->parent;
                        __rb_tree_rotate_right(x, root);
                    }
                    x->parent->color = __rb_tree_black;
                    x->parent->parent->color = __rb_tree_red;
                    __rb_tree_rotate_left(x->parent->parent, root);
                }
            }
        }
        root->color = __rb_tree_black;  // root always black
    }

    // x is rotate point
    inline void __rb_tree_rotate_left(__rb_tree_node_base* x, __rb_tree_node_base*& root) {
        __rb_tree_node_base* y = x->right;
        x->right = y->left;
        if (y->left != 0) y->left->parent = x;
        y->parent = x->parent;

        if (x == root)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // x is rotate point
    inline void __rb_tree_rotate_right(__rb_tree_node_base* x, __rb_tree_node_base*& root) {
        __rb_tree_node_base* y = x->left;
        x->left = y->right;
        if (y->right != 0) y->right->parent = x;
        y->parent = x->parent;

        if (x == root)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    iterator find(const Key& k) {
        link_type y = header;  // last node which is not less than k
        link_type x = root();  // current node

        while (x != 0)
            if (!key_compare(key(x), k)) {
                y = x;
                x = left(x);
            } else
                x = right(x);

        iterator j = iterator(y);
        return (j == end() || key_compare(k, key(j.node))) ? end() : j;
    }
};
}
#endif
