/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

/**
 * Given the head of a singly linked list, group all the nodes with odd indices together followed by
 * the nodes with even indices, and return the reordered list.
 *
 * The first node is considered odd, and the second node is even, and so on.
 *
 * Note that the relative order inside both the even and odd groups should remain as it was in the
 * input.
 *
 * You must solve this problem in O(1) extra space complexity and O(n) time complexity.
 *
 * ! The number of nodes in the linked list is in the range [0, 10^4].
 * ! -10^6 <= Node.val <= 10^6
 */

class Solution {
public:
    ListNode* oddEvenList(ListNode* head)
    {
        if (!head)
            return nullptr;

        auto* even = head;
        auto* odd = head->next;
        auto* oddHead = head->next;
        // 0->[1]->2->3...
        while (odd && odd->next) {
            even->next = odd->next;
            even = even->next;
            odd->next = even->next;
            odd = odd->next;
        }
        even->next = oddHead;
        return head;
    }

private:
    ListNode* approach1(ListNode* head)
    {
        if (!head)
            return nullptr;

        ListNode vOdd(-1);
        ListNode vEven(-1);
        auto* odd = &vOdd;
        auto* even = &vEven;
        auto* i = head;
        int index = 0;
        while (i) {
            auto* next = i->next;
            i->next = nullptr; // break original link
            if (index % 2 == 0) {
                even->next = i;
                even = even->next;
            } else {
                odd->next = i;
                odd = odd->next;
            }
            index++;
            i = next;
        }
        even->next = vOdd.next;
        return vEven.next;
    }
};
