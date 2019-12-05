#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <string>

using namespace std;

/**
 * basic idea:
 * node hash to [0, 1]
 * item hash to [0, 1]
 * item assign to closest right of node
 * [0, 1] is not a interval but a circle, means if closest right doesn't have a node, then circle back to first node
 * actually [0, 1] scaled to [0, UINT64_MAX]
 */

template <typename T, typename Hash, typename Alloc = std::allocator<std::pair<const typename Hash::result_type, T> > >
class consistent_hash_map {
public:
    typedef typename Hash::result_type size_type;
    typedef std::map<size_type, T, std::less<>, Alloc> map_type;  // small to big order
    typedef typename map_type::value_type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename map_type::iterator iterator;
    typedef typename map_type::reverse_iterator reverse_iterator;
    typedef Alloc allocator_type;

public:
    consistent_hash_map() = default;
    ~consistent_hash_map() = default;

public:
    std::size_t size() const { return nodes_.size(); }

    bool empty() const { return nodes_.empty(); }

    std::pair<iterator, bool> insert(const T& node) {
        size_type hash = hasher_(node);
        return nodes_.insert(value_type(hash, node));
    }

    void erase(iterator it) { nodes_.erase(it); }

    std::size_t erase(const T& node) {
        size_type hash = hasher_(node);
        return nodes_.erase(hash);
    }

    iterator find(size_type hash) {
        if (nodes_.empty()) {
            return nodes_.end();
        }

        auto it = nodes_.lower_bound(hash);

        if (it == nodes_.end()) {  // if cannot find, then circle back to first machine
            it = nodes_.begin();
        }
        return it;
    }

    iterator begin() { return nodes_.begin(); }
    iterator end() { return nodes_.end(); }
    reverse_iterator rbegin() { return nodes_.rbegin(); }
    reverse_iterator rend() { return nodes_.rend(); }

private:
    Hash hasher_;
    map_type nodes_;
};

const char* nodes[] = {"192.168.1.100", "192.168.1.101", "192.168.1.102", "192.168.1.103", "192.168.1.104"};

struct vnode_t {
    vnode_t() {}
    vnode_t(std::size_t n, std::size_t v) : node_id(n), vnode_id(v) {}

    std::string to_str() const { return string(nodes[node_id]) + ":" + std::to_string(vnode_id); }

    std::size_t node_id;
    std::size_t vnode_id;
};

struct vnode_hasher {
    std::hash<std::string> hasher;

    size_t operator()(const vnode_t& node) { return hasher(node.to_str()); }
    typedef size_t result_type;
};

int main() {
    typedef consistent_hash_map<vnode_t, vnode_hasher> consistent_hash_t;
    consistent_hash_t hash_;

    // total 5 physic machine and each one have 100 virtual nodes, this can prevent hash not evenly distributed
    for (std::size_t i = 0; i < 5; ++i) {
        for (std::size_t j = 0; j < 100; j++) {
            hash_.insert(vnode_t(i, j));
        }
    }

    {
        std::cout << "=======================stats of each physical machine and virtual node====================="
                  << std::endl;
        std::size_t sums[] = {0, 0, 0, 0, 0};
        auto itr1 = hash_.begin();
        auto itr2 = hash_.rbegin();
        std::size_t n = (UINT64_MAX - itr2->first) + itr1->first;
        cout << "vnode: " << itr1->second.to_str() << ", hash: " << itr1->first << ", contains: [0, " << itr1->first
             << "], (" << itr2->first << ", UINT64_MAX] total: " << n << endl;
        sums[itr1->second.node_id] += n;

        size_t prev = itr1->first;
        size_t cur;
        while (++itr1 != hash_.end()) {
            cur = itr1->first;
            n = cur - prev;
            cout << "vnode: " << itr1->second.to_str() << ", hash: " << itr1->first << ", contains: (" << prev << ", "
                 << cur << "] total:" << n << endl;
            sums[itr1->second.node_id] += n;
            prev = cur;
        }

        for (std::size_t i = 0; i < 5; ++i) {
            cout << "node: " << nodes[i] << ", total: " << sums[i] << endl;
        }
    }

    {
        auto it = hash_.find(290235110);
        cout << "located in node: " << nodes[it->second.node_id] << ", vnode: " << it->second.vnode_id
             << ", hash: " << it->first << endl;
    }
    return 0;
}
