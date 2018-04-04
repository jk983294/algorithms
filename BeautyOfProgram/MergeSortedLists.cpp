#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

/**
 * Merge k sorted linked lists and return it as one sorted list.
 */

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct comparator {
    bool operator()(ListNode* a, ListNode* b) { return a->val > b->val; }
};

bool my_cmp(ListNode* a, ListNode* b) { return a->val > b->val; }

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) { return mergeKListsPriorityQueue(lists); }

    ListNode* mergeKListsHeap(vector<ListNode*>& lists) {
        /**
         * head node technical get rid of first node null check
         */
        ListNode head(0);
        ListNode* pNode = &head;
        vector<ListNode*> heap;
        for (auto itr : lists) {
            if (itr) heap.push_back(itr);
        }

        if (heap.empty()) return nullptr;

        int size = heap.size();
        make_heap(heap.begin(), heap.end(), my_cmp);

        while (size) {
            pop_heap(heap.begin(), heap.begin() + size, my_cmp);
            ListNode* node = heap[size - 1];

            pNode->next = node;
            pNode = node;

            if (node->next) {
                heap[size - 1] = node->next;
                push_heap(heap.begin(), heap.begin() + size, my_cmp);
            } else {
                --size;
            }
        }
        return head.next;
    }

    ListNode* mergeKListsPriorityQueue(vector<ListNode*>& lists) {
        ListNode head(0);
        ListNode* pNode = &head;
        std::priority_queue<ListNode*, vector<ListNode*>, comparator> pq;
        for (auto itr : lists) {
            if (itr) pq.push(itr);
        }

        while (!pq.empty()) {
            ListNode* node = pq.top();
            pq.pop();

            pNode->next = node;
            pNode = node;

            if (node->next) {
                pq.push(node->next);
            }
        }
        return head.next;
    }
};

int main() {
    vector<ListNode*> lists;
    lists.push_back(new ListNode(0));
    lists.push_back(new ListNode(1));
    Solution s;
    ListNode* result = s.mergeKLists(lists);
    while (result) {
        cout << result->val << endl;
        result = result->next;
    }
    return 0;
}
