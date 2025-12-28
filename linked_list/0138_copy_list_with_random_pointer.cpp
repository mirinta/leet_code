#include <unordered_map>

/**
 * Definition of a Node.
 */
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val)
    {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

/**
 * A linked list of length "n" is given such that each node contains an additional random pointer,
 * which could point to any node in the list, or null.
 *
 * Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes,
 * where each new node has its value set to the value of its corresponding original node. Both the
 * next and random pointer of the new nodes should point to new nodes in the copied list such that
 * the pointers in the original list and copied list represent the same list state. None of the
 * pointers in the new list should point to nodes in the original list.
 *
 * For example, if there are two nodes X and Y in the original list, where X.random --> Y, then for
 * the corresponding two nodes x and y in the copied list, x.random --> y.
 *
 * Return the head of the copied linked list.
 *
 * The linked list is represented in the input/output as a list of n nodes. Each node is represented
 * as a pair of [val, random_index] where:
 *
 * - val: an integer representing Node.val
 *
 * - random_index: the index of the node (range from 0 to n-1) that the random pointer points to, or
 * null if it does not point to any node.
 *
 * Your code will only be given the head of the original linked list.
 *
 * ! 0 <= n <= 1000
 * ! -10^4 <= Node.val <= 10^4
 * ! Node.random is null or is pointing to some node in the linked list.
 */

class Solution {
public:
    Node* copyRandomList(Node* head)
    {
        return approach2(head);
    }

    Node* approach2(Node* head)
    {
        if (!head)
            return nullptr;

        // step 1: put each copied node right after the original node
        // - for example, node1->copy1->node2->...
        for (auto* i = head; i; i = i->next->next) {
            auto* next = i->next;
            auto* copy = new Node(i->val);
            copy->next = next;
            i->next = copy;
        }
        // step 2: copy the random pointers
        for (auto* i = head; i; i = i->next->next) {
            if (i->random) {
                i->next->random = i->random->next;
            } else {
                i->next->random = nullptr;
            }
        }
        // step 3: extract the copied nodes and restore the original list
        Node vHead(-1);
        // 1->1'->2->2'->...
        for (auto i = head, j = &vHead; i; i = i->next, j = j->next) {
            j->next = i->next;
            i->next = i->next->next;
        }
        return vHead.next;
    }

    Node* approach1(Node* head)
    {
        if (!head)
            return nullptr;

        Node vHead(-1);
        std::unordered_map<Node*, Node*> map; // original node to copied node
        for (auto i = head, j = &vHead; i; i = i->next, j = j->next) {
            // initialization of i and j, we have to use auto, not auto*
            // because auto* i = head deduces auto as Node, and Node j = &vHead is a compile error
            auto* copy = new Node(i->val);
            j->next = copy;
            map[i] = copy;
        }
        for (auto* i = head; i; i = i->next) {
            map[i]->random = map[i->random];
        }
        return vHead.next;
    }
};
