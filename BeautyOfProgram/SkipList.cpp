#include <cstddef>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>

using namespace std;

template <typename K, typename V>
struct SkipListNode {
    K key;
    V value;
    int level{0};
    SkipListNode<K, V> **nextNodes{nullptr};

    SkipListNode() = default;
    SkipListNode(const K &k, const V &v, int l)
        : key(k), value(v), level(l), nextNodes(new SkipListNode<K, V> *[l + 1]) {}
    ~SkipListNode() {
        if (nextNodes) delete[] nextNodes;
    }
};

/**
 * maxLevel should be log(2, maxElementCount)
 */
template <typename K, typename V>
class SkipList {
public:
    SkipList(int maxLevel_ = 10) {
        maxLevel = maxLevel_ > 0 ? maxLevel_ : 1;
        head = new SkipListNode<K, V>;
        tail = new SkipListNode<K, V>;

        head->nextNodes = new SkipListNode<K, V> *[maxLevel];
        for (int i = 0; i < maxLevel; ++i) head->nextNodes[i] = tail;
    }

    ~SkipList() {
        SkipListNode<K, V> *curr = nullptr;
        while (head->nextNodes[0] != tail) {
            curr = head->nextNodes[0];
            head->nextNodes[0] = curr->nextNodes[0];
            delete curr;
        }
        delete head;
        delete tail;
    }

    std::pair<SkipListNode<K, V> *, bool> insert(K key, V value) {
        SkipListNode<K, V> *update[maxLevel];  // store new node's precursors
        SkipListNode<K, V> *curr = head;

        // find new node's precursor in each level
        for (int i = maxLevel - 1; i >= 0; --i) {
            if (curr->nextNodes[i] == tail || curr->nextNodes[i]->key > key)
                update[i] = curr;
            else {
                while (curr->nextNodes[i] != tail && curr->nextNodes[i]->key < key) {
                    curr = curr->nextNodes[i];
                }

                // ensure the key is unique
                if (curr->nextNodes[i] != tail && curr->nextNodes[i]->key == key) {
                    curr->nextNodes[i]->value = value;
                    return {nullptr, false};
                }
                update[i] = curr;
            }
        }

        // create the new node to be inserted
        int level = min(distribution(generator), maxLevel - 1);  // get max random level
        SkipListNode<K, V> *temp = new SkipListNode<K, V>(key, value, level);

        // inserted the new node into lists indexing from 0 to level
        for (int i = 0; i <= level; ++i) {
            temp->nextNodes[i] = update[i]->nextNodes[i];
            update[i]->nextNodes[i] = temp;
        }
        ++count;
        return {temp, true};
    }

    std::pair<V, bool> erase(K key) {
        SkipListNode<K, V> *update[maxLevel];
        SkipListNode<K, V> *curr = head;

        // find the node's precursors in each level.
        for (int i = maxLevel - 1; i >= 0; --i) {
            if (curr->nextNodes[i] == tail || curr->nextNodes[i]->key > key)
                update[i] = nullptr;
            else {
                while (curr->nextNodes[i] != tail && curr->nextNodes[i]->key < key) curr = curr->nextNodes[i];
                if (curr->nextNodes[i] != tail && curr->nextNodes[i]->key == key)
                    update[i] = curr;
                else
                    update[i] = nullptr;
            }
        }

        SkipListNode<K, V> *temp = nullptr;
        // delete the node from all lists it appears in
        for (int i = 0; i < maxLevel; ++i) {
            if (update[i]) {
                temp = update[i]->nextNodes[i];
                update[i]->nextNodes[i] = temp->nextNodes[i];
            }
        }

        if (temp) {
            V v = temp->value;
            delete temp;
            --count;
            return {v, true};
        }
        return {V(), false};
    }

    std::pair<SkipListNode<K, V> *, bool> find(K key) {
        SkipListNode<K, V> *curr = head;
        for (int i = maxLevel - 1; i >= 0; --i) {
            if (curr->nextNodes[i] == tail || curr->nextNodes[i]->key > key)
                continue;
            else {
                while (curr->nextNodes[i] != tail && curr->nextNodes[i]->key < key) curr = curr->nextNodes[i];
                if (curr->nextNodes[i] != tail && curr->nextNodes[i]->key == key) return {curr->nextNodes[i], true};
            }
        }
        return {nullptr, false};
    }

    void display() {
        for (int i = maxLevel - 1; i >= 0; --i) {
            SkipListNode<K, V> *curr = head->nextNodes[i];
            SkipListNode<K, V> *base = head->nextNodes[0];
            cout << "layer " << i << ": ";
            while (base != tail) {
                if (curr == base) {  // base raised up as index
                    cout << setw(4) << curr->key;
                    curr = curr->nextNodes[i];
                } else {
                    cout << setw(4) << " ";
                }
                base = base->nextNodes[0];
            }
            cout << endl;
        }
    }

    V &operator[](const K &key) {
        auto result = find(key);
        if (result.second) {
            return result.first->value;
        } else {
            return insert(key, V()).first->value;
        }
    }

    V &at(const K &key) {
        auto result = find(key);
        if (result.second) {
            return result.first->value;
        } else {
            throw std::out_of_range("key not found");
        }
    }

    int size() const { return count; }

private:
    int maxLevel{1};
    int count{0};
    mt19937 generator{random_device()()};
    std::geometric_distribution<int> distribution{0.5};
    SkipListNode<K, V> *head;
    SkipListNode<K, V> *tail;
};

using namespace std;

int main() {
    SkipList<int, int> s(4);

    // test inserting
    cout << "Inserting 0 ~ 15." << endl;
    for (int i = 0; i < 16; ++i) cout << "insert " << i << ": " << s.insert(i, i).second << endl;
    cout << "insert " << 2 << ": " << s.insert(2, 2).second << endl;
    s.display();
    cout << endl;

    // test deleting
    cout << "delete 3: " << s.erase(3).second << endl;
    cout << "delete 7: " << s.erase(7).second << endl;
    cout << "delete 7: " << s.erase(7).second << endl;
    cout << "delete 25: " << s.erase(25).second << endl;
    s.display();
    cout << endl;

    // test Searching
    cout << "Searching 5 and 9." << endl;
    cout << "key = 5, val = " << s.find(5).first->value << endl;
    cout << "key = 9, val = " << s.find(9).first->value << endl;
    cout << "key = 42, val = " << s.find(42).second << endl;
    cout << "key = 4, val = " << s[4] << endl;
    cout << "key = 13, val = " << s.at(13) << endl;
    return 0;
}
