#include <algorithm>
#include <vector>

/**
 * Fruits are available at some positions on an infinite x-axis. You are given a 2D integer array
 * fruits where fruits[i] = [positioni, amounti] depicts amounti fruits at the position positioni.
 * fruits is already sorted by positioni in ascending order, and each positioni is unique.
 *
 * You are also given an integer startPos and an integer k. Initially, you are at the position
 * startPos. From any position, you can either walk to the left or right. It takes one step to move
 * one unit on the x-axis, and you can walk at most k steps in total. For every position you reach,
 * you harvest all the fruits at that position, and the fruits will disappear from that position.
 *
 * Return the maximum total number of fruits you can harvest.
 *
 * ! 1 <= fruits.length <= 10^5
 * ! fruits[i].length == 2
 * ! 0 <= startPos, positioni <= 2 * 10^5
 * ! positioni-1 < positioni for any i > 0 (0-indexed)
 * ! 1 <= amounti <= 10^4
 * ! 0 <= k <= 2 * 10^5
 */

class Solution {
public:
    int maxTotalFruits(std::vector<std::vector<int>>& fruits, int startPos, int k)
    {
        // case 1: go left then right
        // steps = 2 * (startPos - fruits[left][0]) + (fruits[right][0] - startPos)
        // steps = startPos - 2 * fruits[left][0] + fruits[right][0]
        // case 2: go right then left
        // steps = 2 * (fruits[right][0] - startPos) + (startPos - fruits[left][0])
        // steps = 2 * fruits[right][0] - startPos - fruits[left][0]
        const int n = fruits.size();
        auto comp = [](const auto& v, int val) { return val > v[0]; };
        int left = std::lower_bound(fruits.begin(), fruits.end(), startPos - k, comp) - fruits.begin();
        int right = left;
        auto case1 = [&]() { return startPos - 2 * fruits[left][0] + fruits[right][0]; };
        auto case2 = [&]() { return 2 * fruits[right][0] - startPos - fruits[left][0]; };
        int sum = 0;
        for (; right < n && fruits[right][0] <= startPos; ++right) {
            sum += fruits[right][1];
        }
        int result = sum;
        for (; right < n && fruits[right][0] - startPos <= k; ++right) {
            sum += fruits[right][1];
            while (case1() > k && case2() > k) {
                sum -= fruits[left][1];
                left++;
            }
            result = std::max(result, sum);
        }
        return result;
    }
};