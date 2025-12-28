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
 * You are given two integers m and n, which represent the dimensions of a matrix.
 *
 * You are also given the head of a linked list of integers.
 *
 * Generate an m x n matrix that contains the integers in the linked list presented in spiral order
 * (clockwise), starting from the top-left of the matrix. If there are remaining empty spaces, fill
 * them with -1.
 *
 * Return the generated matrix.
 *
 * ! 1 <= m, n <= 10^5
 * ! 1 <= m * n <= 10^5
 * ! The number of nodes in the list is in the range [1, m * n].
 * ! 0 <= Node.val <= 1000
 */

class Solution {
public:
    std::vector<std::vector<int>> spiralMatrix(int m, int n, ListNode* head)
    {
        std::vector<std::vector<int>> result(m, std::vector<int>(n, -1));
        int left = 0;
        int right = n - 1;
        int top = 0;
        int bottom = m - 1;
        while (head) {
            for (int i = left; i <= right && top <= bottom && head; ++i) {
                result[top][i] = head->val;
                head = head->next;
            }
            top++;
            for (int i = top; i <= bottom && left <= right && head; ++i) {
                result[i][right] = head->val;
                head = head->next;
            }
            right--;
            for (int i = right; i >= left && top <= bottom && head; --i) {
                result[bottom][i] = head->val;
                head = head->next;
            }
            bottom--;
            for (int i = bottom; i >= top && left <= right && head; --i) {
                result[i][left] = head->val;
                head = head->next;
            }
            left++;
        }
        return result;
    }
};