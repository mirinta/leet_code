#include <unordered_set>
#include <vector>

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
 * You are given an array of integers nums and the head of a linked list. Return the head of the
 * modified linked list after removing all nodes from the linked list that have a value that exists
 * in nums.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^5
 * ! All elements in nums are unique.
 * ! The number of nodes in the given list is in the range [1, 10^5].
 * ! 1 <= Node.val <= 10^5
 * ! The input is generated such that there is at least one node in the linked list that has a value
 * ! not present in nums.
 */

class Solution {
public:
    ListNode* modifiedList(std::vector<int>& nums, ListNode* head)
    {
        if (!head)
            return nullptr;

        std::unordered_set<int> set(nums.begin(), nums.end());
        ListNode vHead;
        auto* node = &vHead;
        while (head) {
            auto* next = head->next;
            head->next = nullptr;
            if (!set.count(head->val)) {
                node->next = head;
                node = node->next;
            }
            head = next;
        }
        return vHead.next;
    }
};