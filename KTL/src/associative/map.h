#ifndef MAP_H_
#define MAP_H_

#include "allocator/allocator.h"
#include "functional/functional.h"
#include "rbtree.h"
#include "util/pair.h"

namespace ktl {

template <class Key, class T, class Compare = less<Key>, class Alloc = alloc>
class map {
public:
    typedef Key key_type;
    typedef T data_type;
    typedef T mapped_type;
    typedef pair<const Key, T> value_type;
    typedef Compare key_compare;

    // internal key comparator
    class value_compare : public binary_function<value_type, value_type, bool> {
        friend class map<Key, T, Compare, Alloc>;

    protected:
        Compare comp;
        value_compare(Compare c) : comp(c) {}

    public:
        bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
    };

private:
    typedef rb_tree<key_type, value_type, select1st<value_type>, key_compare, Alloc> rep_type;
    rep_type t;

public:
    typedef typename rep_type::pointer pointer;
    typedef typename rep_type::const_pointer const_pointer;
    typedef typename rep_type::reference reference;
    typedef typename rep_type::const_reference const_reference;
    typedef typename rep_type::iterator iterator;  // allow modify value
    typedef typename rep_type::const_iterator const_iterator;
    typedef typename rep_type::size_type size_type;
    typedef typename rep_type::difference_type difference_type;

    map() : t(Compare()) {}
    explicit map(const Compare& comp) : t(comp) {}

    template <class InputIterator>
    map(InputIterator first, InputIterator last) : t(Compare()) {
        t.insert_unique(first, last);
    }

    template <class InputIterator>
    map(InputIterator first, InputIterator last, const Compare& comp) : t(comp) {
        t.insert_unique(first, last);
    }

    map(const map<Key, T, Compare, Alloc>& x) : t(x.t) {}
    map<Key, T, Compare, Alloc>& operator=(const map<Key, T, Compare, Alloc>& x) {
        t = x.t;
        return *this;
    }

    key_compare key_comp() const { return t.key_comp(); }
    value_compare value_comp() const { return value_compare(t.key_comp()); }
    iterator begin() { return t.begin(); }
    const_iterator begin() const { return t.begin(); }
    iterator end() { return t.end(); }
    const_iterator end() const { return t.end(); }
    bool empty() const { return t.empty(); }
    size_type size() const { return t.size(); }
    size_type max_size() const { return t.max_size(); }

    T& operator[](const key_type& k) {
        // insert return pair<iterator, bool>
        auto result = insert(value_type(k, T()));
        return (*(result.first)).second;
    }
    void swap(map<Key, T, Compare, Alloc>& x) { t.swap(x.t); }

    pair<iterator, bool> insert(const value_type& x) { return t.insert_unique(x); }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        t.insert_unique(first, last);
    }

    void erase(iterator position) { t.erase(position); }
    size_type erase(const key_type& x) { return t.erase(x); }
    void erase(iterator first, iterator last) { t.erase(first, last); }
    void clear() { t.clear(); }

    iterator find(const key_type& x) { return t.find(x); }
    size_type count(const key_type& x) const { return t.count(x); }
};
}

#endif
