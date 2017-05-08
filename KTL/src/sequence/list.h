#ifndef _LIST_H_
#define _LIST_H_

#include <initializer_list>
#include "../algorithm/algorithm.h"
#include "../allocator/allocator.h"
#include "../allocator/construct.h"

namespace ktl {

template <class T>
struct _list_node {
    typedef _list_node<T>* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};

template <class T, class Ref, class Ptr>
struct _list_iterator {
    typedef _list_iterator<T, T&, T*> iterator;
    typedef _list_iterator<T, Ref, Ptr> self;

    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef _list_node<T>* link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    link_type node;
    _list_iterator(link_type x) : node(x) {}
    _list_iterator() {}
    _list_iterator(const iterator& x) : node(x.node) {}
    bool operator==(const self& x) const { return node == x.node; }
    bool operator!=(const self& x) const { return node != x.node; }

    reference operator*() const { return (*node).data; }
    /**
     * member access operator, &((*node).data)
     * iterator is an object, so when client call itr->func(), it will delegate to actual node->data.func()
     */
    pointer operator->() const { return &(operator*()); }

    //! ++i
    self& operator++() {
        node = node->next;
        return *this;
    }

    //! i++
    self operator++(int) {
        self tmp = *this;
        ++*this;
        return tmp;
    }

    //! --i
    self& operator--() {
        node = node->prev;
        return *this;
    }

    //! i--
    self operator--(int) {
        self tmp = *this;
        --*this;
        return tmp;
    }

    self operator+(int dis) {
        self tmp = *this;
        while (dis-- > 0) {
            tmp = tmp.node->next;
        }
        return tmp;
    }

    self operator-(int dis) {
        self tmp = *this;
        while (dis-- > 0) {
            tmp = tmp.node->prev;
        }
        return tmp;
    }
};

template <class T, class Alloc = alloc>
class list {
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef _list_node<T> list_node;
    typedef list_node* link_type;
    typedef simple_alloc<list_node, Alloc> list_node_allocator;
    typedef _list_iterator<T, T&, T*> iterator;

    link_type get_node() { return list_node_allocator::allocate(); }

    void put_node(link_type x) { list_node_allocator::deallocate(x); }

    link_type create_node(const T& x) {
        link_type newListNode = get_node();
        construct(&newListNode->data, x);
        return newListNode;
    }

    void destroy_node(link_type d) {
        destroy(&d->data);
        put_node(d);
    }

public:
    iterator begin() const { return node->next; }
    iterator end() const { return node; }
    bool empty() const { return node->next == node; }
    size_type size() const { return distance(begin(), end()); }

    reference front() { return *begin(); }
    reference back() { return *(--end()); }

    list() { empty_initialize(); }
    list(const std::initializer_list<T> v) {
        empty_initialize();
        for (auto i = v.begin(); i < v.end(); ++i) {
            this->push_back(*i);
        }
    }
    ~list() {
        clear();
        erase(end());
    }

    // change four pointers
    iterator insert(iterator position, const T& x) {
        link_type tmp = create_node(x);
        tmp->next = position.node;
        tmp->prev = position.node->prev;
        position.node->prev->next = tmp;
        position.node->prev = tmp;
        return tmp;
    }

    void push_back(const T& x) { insert(end(), x); }

    void push_front(const T& x) { insert(begin(), x); }

    void pop_front() { erase(begin()); }

    void pop_back() { erase(--end()); }

    void clear() {
        iterator s = begin();
        while (s != end()) {
            s = erase(s);
        }
        node->next = node;
        node->prev = node;
    }

    // no need to release position object, this is an stack object
    iterator erase(iterator position) {
        link_type next_node = position.node->next;
        link_type prev_node = position.node->prev;
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destroy_node(position.node);
        return iterator(next_node);
    }

    // remove all match
    void remove(const T& x) {
        iterator s = begin();
        iterator last = end();
        while (s != last) {
            if (*s == x)
                s = erase(s);
            else
                s++;
        }
    }

    // remove consective equal element
    void unique() {
        iterator first = begin();
        iterator last = end();
        if (first == end) return;  // empty list
        iterator next = first;
        while (++next != last) {
            if (*first == *next)
                erase(next);
            else
                first = next;
            next = first;
        }
    }

    // move [first,last) before position
    // it can be within same list, it also support different lists
    void transfer(iterator position, iterator first, iterator last) {
        if (last == position) return;

        link_type last_node = last.node->prev;
        link_type prev_node = position.node->prev;

        // take out [first last)
        first.node->prev->next = last.node;
        last.node->prev = first.node->prev;

        // link [first last) back
        prev_node->next = first.node;
        first.node->prev = prev_node;
        last_node->next = position.node;
        position.node->prev = last_node;
    }

    // move l before position
    void splice(iterator position, list& l) {
        if (l.empty()) return;
        transfer(position, l.begin(), l.end());
    }

    void splice(iterator position, iterator i) {
        iterator j = i;
        j++;
        if (position == i || position == j) return;  // already in position
        transfer(position, i, j);
    }

    // position cannot within [first, last)
    void splice(iterator position, iterator first, iterator last) {
        if (position == last) return;
        transfer(position, first, last);
    }

    // merge, two list alrady sorted increasely
    void merge(list& x) {
        iterator first1 = begin();
        iterator first2 = x.begin();
        iterator last1 = end();
        iterator last2 = x.end();

        while (first1 != last1 && first2 != last2) {
            if (*first2 < *first1) {
                iterator next = first2;
                transfer(first1, first2, ++next);
                first2 = next;
            } else
                ++first1;
        }

        // add rest of x to the end
        if (first2 != last2) splice(last1, first2, last2);
    }

    void reverse() {
        if (size() == 0 || size() == 1) return;
        iterator start = begin();
        iterator stop = end();
        start++;
        while (start != stop) {
            iterator next = start + 1;
            splice(begin(), start);
            start = next;
        }
    }

    // just swap the sentinel node
    void swap(list& x) {
        link_type tmp = x.node;
        x.node = this->node;
        this->node = tmp;
    }

    // sort list cannot use STL sort since it is not ramdon access
    // use insert sort here
    void sort() {
        if (size() == 0 || size() == 1) return;
        list<T, Alloc> tmp;
        iterator q = begin();
        while (!empty()) {
            iterator p = tmp.begin();
            while (p != tmp.end() && *p < *q) p++;
            tmp.splice(p, q);
            q = begin();
        }
        swap(tmp);
    }

protected:
    /**
     * bidirectional cyclical list, node point to tail empty head node
     * node works as sentinel node
     * list.end() == node
     * list.begin() == node->next
     */
    link_type node;

    void empty_initialize() {
        node = get_node();
        node->next = node;
        node->prev = node;
    }
};
}

#endif
