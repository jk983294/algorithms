#ifndef KTL_FLAT_MAP_H
#define KTL_FLAT_MAP_H

#include <vector>
#include <cstdlib>
#include <algorithm>

namespace ktl {
template <typename key_type, typename val_type>
class FlatMap {
public:
    typedef std::pair<key_type, val_type> pair_type;
    typedef typename std::vector<pair_type>::iterator iterator;
    typedef std::pair<iterator, iterator> iterator_pair;

    FlatMap() : bSorted(true){};
    FlatMap(const FlatMap &rhs) = default;
    FlatMap(FlatMap &&rhs) { swap(rhs); };
    FlatMap &operator=(const FlatMap &rhs) = default;

    void clear();
    void reserve(size_t size);
    void insert(const pair_type &p);
    void insert(const key_type &k, const val_type &v);
    iterator find(const key_type &k);
    iterator lower_bound(const key_type &k);
    iterator upper_bound(const key_type &k);
    iterator_pair equal_range(const key_type &k);
    size_t count(const key_type &k);
    bool empty();
    size_t size();
    iterator erase(const key_type &k);
    iterator erase(iterator i0);
    iterator erase(iterator i0, iterator i1);
    void swap(FlatMap &other);

    iterator begin();
    iterator end();

    void sort(bool bPriorityFirstUnique = false);

private:
    template <class T>
    struct flat_map_less_key {
        bool operator()(const T &lhs, const T &rhs) const { return lhs.first < rhs.first; }
    };

    template <class T>
    struct flat_map_equal_key {
        bool operator()(const T &lhs, const T &rhs) const { return lhs.first == rhs.first; }
    };

    template <class T>
    struct flat_map_equal_key1 {
        flat_map_equal_key1(const typename T::first_type &k) : m_key(k){};

        bool operator()(const T &p) const { return p.first == m_key; }
        const typename T::first_type &m_key;
    };

    std::vector<pair_type> container;
    bool bSorted;
};

template <typename key_type, typename val_type>
void FlatMap<key_type, val_type>::clear() {
    container.clear();
    bSorted = true;
}

template <typename key_type, typename val_type>
void FlatMap<key_type, val_type>::reserve(size_t size) {
    container.reserve(size);
}

template <typename key_type, typename val_type>
void FlatMap<key_type, val_type>::insert(const pair_type &p) {
    container.push_back(p);
    bSorted = false;
}

template <typename key_type, typename val_type>
void FlatMap<key_type, val_type>::insert(const key_type &k, const val_type &v) {
    container.push_back(std::make_pair(k, v));
    bSorted = false;
}

template <typename key_type, typename val_type>
typename FlatMap<key_type, val_type>::iterator FlatMap<key_type, val_type>::find(const key_type &k) {
    if (!bSorted) sort();
    pair_type p;
    p.first = k;
    iterator_pair pit = std::equal_range(container.begin(), container.end(), p, flat_map_less_key<pair_type>());
    if (pit.first == pit.second) return container.end();
    return pit.first;
}

template <typename key_type, typename val_type>
typename FlatMap<key_type, val_type>::iterator FlatMap<key_type, val_type>::lower_bound(const key_type &k) {
    if (!bSorted) sort();
    pair_type p;
    p.first = k;
    iterator it = std::lower_bound(container.begin(), container.end(), p, flat_map_less_key<pair_type>());
    return it;
}

template <typename key_type, typename val_type>
typename FlatMap<key_type, val_type>::iterator FlatMap<key_type, val_type>::upper_bound(const key_type &k) {
    if (!bSorted) sort();
    pair_type p;
    p.first = k;
    iterator it = std::upper_bound(container.begin(), container.end(), p, flat_map_less_key<pair_type>());
    return it;
}

template <typename key_type, typename val_type>
typename FlatMap<key_type, val_type>::iterator_pair FlatMap<key_type, val_type>::equal_range(const key_type &k) {
    if (!bSorted) sort();
    pair_type p;
    p.first = k;
    iterator_pair pit = std::equal_range(container.begin(), container.end(), p, flat_map_less_key<pair_type>());
    return pit;
}

template <typename key_type, typename val_type>
size_t FlatMap<key_type, val_type>::count(const key_type &k) {
    pair_type p;
    p.first = k;
    bool b = std::binary_search(container.begin(), container.end(), p, flat_map_less_key<pair_type>());
    if (!b) return 0;
    return 1;
}

template <typename key_type, typename val_type>
size_t FlatMap<key_type, val_type>::size() {
    if (!bSorted) sort();
    return container.size();
}

template <typename key_type, typename val_type>
bool FlatMap<key_type, val_type>::empty() {
    return container.size() == 0;
}

template <typename key_type, typename val_type>
typename FlatMap<key_type, val_type>::iterator FlatMap<key_type, val_type>::erase(const key_type &k) {
    flat_map_equal_key1<pair_type> pred(k);
    iterator it = container.erase(std::remove_if(container.begin(), container.end(), pred));
    return it;
}

template <typename key_type, typename val_type>
typename FlatMap<key_type, val_type>::iterator FlatMap<key_type, val_type>::erase(iterator i0) {
    iterator it = container.erase(i0);
    return it;
}

template <typename key_type, typename val_type>
typename FlatMap<key_type, val_type>::iterator FlatMap<key_type, val_type>::erase(iterator i0, iterator i1) {
    iterator it = container.erase(i0, i1);
    return it;
}

template <typename key_type, typename val_type>
void FlatMap<key_type, val_type>::swap(FlatMap<key_type, val_type> &other) {
    std::swap(bSorted, other.bSorted);
    std::swap(container, other.container);
}

template <typename key_type, typename val_type>
typename FlatMap<key_type, val_type>::iterator FlatMap<key_type, val_type>::begin() {
    if (!bSorted) sort();
    return container.begin();
}

template <typename key_type, typename val_type>
typename FlatMap<key_type, val_type>::iterator FlatMap<key_type, val_type>::end() {
    if (!bSorted) sort();
    return container.end();
}

template <typename key_type, typename val_type>
void FlatMap<key_type, val_type>::sort(bool bPriorityFirstUnique /*= false*/) {
    if (container.size() < 2) {
        bSorted = true;
        return;
    }
    iterator i0 = container.begin();
    iterator i1 = container.end();
    std::stable_sort(i0, i1, flat_map_less_key<pair_type>());

    // reversing first and last unique values
    if (!bPriorityFirstUnique) {
        int nLast = static_cast<int>(container.size()) - 1;
        int nFirstUnique = nLast;
        int nLastUnique = nLast;
        for (int i = nLast - 1; i >= 0; i--) {
            if (container[i].first == container[nLastUnique].first) {
                nLastUnique--;
                if (i == 0) std::swap(container[nFirstUnique], container[nLastUnique]);
                continue;
            }
            if (nFirstUnique != nLastUnique) std::swap(container[nFirstUnique], container[nLastUnique]);
            nFirstUnique = i;
            nLastUnique = i;
        }
    }
    container.erase(std::unique(i0, i1, flat_map_equal_key<pair_type>()), i1);

    bSorted = true;
}
}

#endif
