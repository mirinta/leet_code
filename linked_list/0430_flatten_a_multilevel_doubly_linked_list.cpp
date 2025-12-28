/**
 * Definition for a Node.
 */
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

class Solution {
public:
    Node* flatten(Node* head)
    {
        dfs(head);
        return head;
    }

private:
    // return tail node
    Node* dfs(Node* head)
    {
        if (!head)
            return nullptr;

        auto* next = head->next;
        auto* child = head->child;
        head->child = nullptr;
        if (next && child) {
            auto* nextTail = dfs(next);
            auto* childTail = dfs(child);
            head->next = child;
            child->prev = head;
            childTail->next = next;
            next->prev = childTail;
            return nextTail;
        }
        if (!next && child) {
            auto* childTail = dfs(child);
            head->next = child;
            child->prev = head;
            return childTail;
        }
        if (next && !child) {
            auto* nextTail = dfs(next);
            return nextTail;
        }
        return head;
    }
};
