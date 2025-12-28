#include <string>
#include <vector>

/**
 * You have n boxes. You are given a binary string boxes of length n, where boxes[i] is '0' if the
 * ith box is empty, and '1' if it contains one ball.
 *
 * In one operation, you can move one ball from a box to an adjacent box. Box i is adjacent to box j
 * if abs(i - j) == 1. Note that after doing so, there may be more than one ball in some boxes.
 *
 * Return an array answer of size n, where answer[i] is the minimum number of operations needed to
 * move all the balls to the ith box.
 *
 * Each answer[i] is calculated considering the initial state of the boxes.
 *
 * ! n == boxes.length
 * ! 1 <= n <= 2000
 * ! boxes[i] is either '0' or '1'.
 */

class Solution {
public:
    std::vector<int> minOperations(std::string boxes)
    {
        const int n = boxes.size();
        // prefix[i] = num of operations to move boxes of boxes[0:i-1] to i
        std::vector<int> prefix(n);
        for (int i = 1, count = 0; i < n; ++i) {
            count += boxes[i - 1] == '1';
            prefix[i] = prefix[i - 1] + count;
        }
        // suffix[i] = num of operations to move boxes of boxes[i+1:n-1] to i
        std::vector<int> suffix(n);
        for (int i = n - 2, count = 0; i >= 0; --i) {
            count += boxes[i + 1] == '1';
            suffix[i] = suffix[i + 1] + count;
        }
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = prefix[i] + suffix[i];
        }
        return result;
    }
};
