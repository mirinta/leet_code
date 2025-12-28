/**
 * Definition for a Node.
 */
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val)
    {
        val = _val;
        next = nullptr;
    }

    Node(int _val, Node* _next)
    {
        val = _val;
        next = _next;
    }
};

/**
 * Given a Circular Linked List node, which is sorted in non-descending order, write a function to
 * insert a value insertVal into the list such that it remains a sorted circular list. The given
 * node can be a reference to any single node in the list and may not necessarily be the smallest
 * value in the circular list.
 *
 * If there are multiple suitable places for insertion, you may choose any place to insert the new
 * value. After the insertion, the circular list should remain sorted.
 *
 * If the list is empty (i.e., the given node is null), you should create a new single circular list
 * and return the reference to that single node. Otherwise, you should return the originally given
 * node.
 *
 * ! The number of nodes in the list is in the range [0, 5 * 10^4].
 * ! -10^6 <= Node.val, insertVal <= 10^6
 */

class Solution {
public:
    Node* insert(Node* head, int insertVal)
    {
        if (!head) {
            auto* node = new Node(insertVal);
            node->next = node; // to make sure it is a circular linked list
            return node;
        }
        // find the min and max node
        // - [1]->2->[3], [3]->3->[3], [1]->1->[3]
        // - if there're duplicate max values, we want the last one
        // - if there're duplicate min values, we want the first one
        Node* min = head;
        Node* max = head;
        for (auto* i = head->next; i != head; i = i->next) {
            if (i->val < min->val) {
                min = i;
            } else if (i->val >= max->val) {
                max = i;
            }
        }
        // check if "insertVal" is out of range
        // 1->2->3  insert 4: 1->2->3->4   insert 0: 1->2->3->0
        // |<----|            |<-------|             |<-------|
        if (insertVal < min->val || insertVal > max->val) {
            auto* node = new Node(insertVal);
            node->next = min;
            max->next = node;
            return head;
        }
        // insert new node at the last valid position
        for (auto* i = min; i; i = i->next) {
            if (i->val <= insertVal && insertVal <= i->next->val) {
                auto* node = new Node(insertVal);
                node->next = i->next;
                i->next = node;
                break;
            }
        }
        return head;
    }
};
