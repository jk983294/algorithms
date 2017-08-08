#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * 斐波那契堆 最小堆实现
 * 支持O(1)时间合并两个堆
 */
template <typename Key, typename Data>
class FibonacciHeapNode {
public:
    Key key() const { return myKey; }
    Data data() const { return myData; }
    template <typename K, typename D>
    friend class FibonacciHeap;

private:
    Key myKey;
    Data myData;
    size_t degree;  // number of children. used in the removeMinimum algorithm.
    bool mark;      // mark used in the decreaseKey algorithm.

    FibonacciHeapNode<Key, Data>* previous;  // pointers in a circular doubly linked list
    FibonacciHeapNode<Key, Data>* next;
    FibonacciHeapNode<Key, Data>* child;  // pointer to the first child in the list of children
    FibonacciHeapNode<Key, Data>* parent;

    FibonacciHeapNode() {}
    FibonacciHeapNode(Key k, Data d) : myKey(k), myData(d), degree(0), mark(false), child(nullptr), parent(nullptr) {
        previous = next = this;  // doubly linked circular list
    }
    bool isSingle() const { return (this == this->next); }

    // inserts a new node after this node ,other 是一个双循环链表，断开后嵌入this
    void insert(FibonacciHeapNode<Key, Data>* other) {
        if (!other) return;
        // For example: given 1->2->3->4->1, insert a->b->c->d->a after node 3:
        // result: 1->2->3->a->b->c->d->4->1
        this->next->previous = other->previous;
        other->previous->next = this->next;
        this->next = other;
        other->previous = this;
    }

    void remove() {
        this->previous->next = this->next;
        this->next->previous = this->previous;
        this->next = this->previous = this;
    }

    void addChild(FibonacciHeapNode<Key, Data>* other) {  // Fibonacci-Heap-Link(other,current)
        if (!child)
            child = other;
        else
            child->insert(other);
        other->parent = this;
        other->mark = false;
        degree++;
    }

    void removeChild(FibonacciHeapNode<Key, Data>* other) {
        if (other->parent != this) throw string("Trying to remove a child from a non-parent");
        if (other->isSingle()) {
            if (child != other) throw string("Trying to remove a non-child");
            child = nullptr;
        } else {
            if (child == other) child = other->next;
            other->remove();  // from list of children
        }
        other->parent = nullptr;
        other->mark = false;
        degree--;
    }
    friend ostream& operator<<(ostream& out, const FibonacciHeapNode& n) { return (out << n.myData << ":" << n.myKey); }

    void printTree(ostream& out) const {
        out << myData << ":" << myKey << ":" << degree << ":" << mark;
        if (child) {
            out << "(";
            const FibonacciHeapNode<Key, Data>* n = child;
            do {
                if (n == this) throw string("Illegal pointer - node is child of itself");
                n->printTree(out);
                out << " ";
                n = n->next;
            } while (n != child);
            out << ")";
        }
    }

    void printAll(ostream& out) const {
        const FibonacciHeapNode<Key, Data>* n = this;
        do {
            n->printTree(out);
            out << " ";
            n = n->next;
        } while (n != this);
        out << endl;
    }
};  // FibonacciHeapNode

template <typename Key, typename Data>
class FibonacciHeap {
    typedef FibonacciHeapNode<Key, Data>* PNode;
    PNode rootWithMinKey;  // a circular d-list of nodes
    size_t count;          // total number of elements in heap
    size_t maxDegree;      // maximum degree (=child count) of a root in the  circular d-list

protected:
    PNode insertNode(PNode newNode) {
        // if (debug) cout << "insert " << (*newNode) << endl;
        if (!rootWithMinKey) {  // insert the first myKey to the heap:
            rootWithMinKey = newNode;
        } else {
            rootWithMinKey->insert(newNode);  // insert the root of new tree to the list of roots
            if (newNode->key() < rootWithMinKey->key()) rootWithMinKey = newNode;
        }
        return newNode;
    }

public:
    FibonacciHeap() : rootWithMinKey(nullptr), count(0), maxDegree(0) {}

    ~FibonacciHeap() {
        while (!empty()) {
            removeMinimum();
        }
    }

    bool empty() const { return count == 0; }

    PNode minimum() const {
        if (!rootWithMinKey) return nullptr;
        return rootWithMinKey;
    }

    void printRoots(ostream& out) const {
        out << "maxDegree=" << maxDegree << "  count=" << count << "  roots=";
        if (rootWithMinKey)
            rootWithMinKey->printAll(out);
        else
            out << endl;
    }

    void merge(const FibonacciHeap& other) {  // Fibonacci-Heap-Union
        rootWithMinKey->insert(other.rootWithMinKey);
        if (!rootWithMinKey || (other.rootWithMinKey && other.rootWithMinKey->key() < rootWithMinKey->key()))
            this->rootWithMinKey = other.rootWithMinKey;
        count += other.count;
    }

    PNode insert(Key k, Data d) {
        count++;
        // create a new tree with a single myKey:
        return insertNode(new FibonacciHeapNode<Key, Data>(k, d));
    }

    void removeMinimum() {  // Fibonacci-Heap-Extract-Min, CONSOLIDATE
        if (!rootWithMinKey) throw string("trying to remove from an empty heap");

        count--;

        /// Phase 1: Make all the removed root's children new roots:
        // Make all children of root new roots:
        if (rootWithMinKey->child) {
            PNode c = rootWithMinKey->child;
            do {
                c->parent = nullptr;
                c = c->next;
            } while (c != rootWithMinKey->child);
            rootWithMinKey->child = nullptr;  // removed all children
            rootWithMinKey->insert(c);
        }

        /// Phase 2-a: handle the case where we delete the last myKey:
        if (rootWithMinKey->next == rootWithMinKey) {
            if (count != 0) throw string("Internal error: should have 0 keys");
            rootWithMinKey = nullptr;
            return;
        }

        /// Phase 2: merge roots with the same degree:
        vector<PNode> degreeRoots(maxDegree + 1);  // make room for a new degree
        fill(degreeRoots.begin(), degreeRoots.end(), (PNode) nullptr);
        maxDegree = 0;
        PNode currentPointer = rootWithMinKey->next;
        size_t currentDegree;
        do {
            currentDegree = currentPointer->degree;

            PNode current = currentPointer;
            currentPointer = currentPointer->next;
            while (degreeRoots[currentDegree]) {           // merge the two roots with the same degree:
                PNode other = degreeRoots[currentDegree];  // another root with the same degree
                if (current->key() > other->key()) swap(other, current);
                // now current->key() <= other->key() - make other a child of current:
                other->remove();  // remove from list of roots
                current->addChild(other);
                degreeRoots[currentDegree] = nullptr;
                currentDegree++;
                if (currentDegree >= degreeRoots.size()) degreeRoots.push_back((PNode) nullptr);
            }
            // keep the current root as the first of its degree in the degrees array:
            degreeRoots[currentDegree] = current;
        } while (currentPointer != rootWithMinKey);

        /// Phase 3: remove the current root, and calcualte the new rootWithMinKey:
        delete rootWithMinKey;
        rootWithMinKey = nullptr;

        size_t newMaxDegree = 0;
        for (size_t d = 0; d < degreeRoots.size(); ++d) {
            if (degreeRoots[d]) {
                degreeRoots[d]->next = degreeRoots[d]->previous = degreeRoots[d];
                insertNode(degreeRoots[d]);
                if (d > newMaxDegree) newMaxDegree = d;
            } else {
            }
        }
        maxDegree = newMaxDegree;
    }

    void decreaseKey(PNode node, Key newKey) {
        if (newKey >= node->myKey) throw string("Trying to decrease key to a greater key");
        // Update the key and possibly the min key:
        node->myKey = newKey;

        // Check if the new key violates the heap invariant:
        PNode parent = node->parent;
        if (!parent) {  // root node - just make sure the minimum is correct
            if (newKey < rootWithMinKey->key()) rootWithMinKey = node;
            return;  // heap invariant not violated - nothing more to do
        } else if (parent->key() <= newKey) {
            return;  // heap invariant not violated - nothing more to do
        }

        for (;;) {
            parent->removeChild(node);
            insertNode(node);

            if (!parent->parent) {  // parent is a root - nothing more to do
                break;
            } else if (!parent->mark) {  // parent is not a root and is not marked - just mark it
                parent->mark = true;
                break;
            } else {
                node = parent;
                parent = parent->parent;
                continue;
            }
        };
    }

    void remove(PNode node, Key minusInfinity) {
        if (minusInfinity >= minimum()->key())
            throw string("2nd argument to remove must be a key that is smaller than all other keys");
        decreaseKey(node, minusInfinity);
        removeMinimum();
    }
};  // FibonacciHeap

#endif
