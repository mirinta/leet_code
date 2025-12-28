/**
 * Definition for a node.
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
 * 请实现 copyRandomList 函数，复制一个复杂链表。在复杂链表中，每个节点除了有一个 next
 * 指针指向下一个节点，还有一个 random 指针指向链表中的任意节点或者 null。
 *
 * ! -10000 <= Node.val <= 10000
 * ! Node.random 为空（null）或指向链表中的节点。
 * ! 节点数目不超过 1000 。
 *
 * ! 本题与LC 138相同。
 */

class Solution {
public:
    Node* copyRandomList(Node* head)
    {
        if (!head)
            return nullptr;

        // insert copy node right after each original node
        auto* node = head;
        while (node) {
            auto* copy = new Node(node->val);
            copy->next = node->next;
            node->next = copy;
            node = node->next->next;
        }
        // process random pointers
        node = head;
        while (node) {
            if (node->random) {
                node->next->random = node->random->next;
            } else {
                node->next->random = nullptr;
            }
            node = node->next->next;
        }
        // extract all copied nodes and restore the original list
        Node vHead(-1);
        auto* i = &vHead;
        node = head;
        while (node) {
            i->next = node->next;
            node->next = node->next->next;
            node = node->next;
            i = i->next;
        }
        return vHead.next;
    }
};