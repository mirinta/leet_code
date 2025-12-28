#include <queue>
#include <unordered_map>
#include <vector>

/**
 * If the depth of a tree is smaller than 5, then this tree can be represented by an array of
 * three-digit integers. For each integer in this array:
 *
 * - The hundreds digit represents the depth d of this node where 1 <= d <= 4.
 *
 * - The tens digit represents the position p of this node in the level it belongs to where 1 <= p
 * <= 8. The position is the same as that in a full binary tree.
 *
 * - The units digit represents the value v of this node where 0 <= v <= 9.
 *
 * Given an array of ascending three-digit integers nums representing a binary tree with a depth
 * smaller than 5, return the sum of all paths from the root towards the leaves.
 *
 * It is guaranteed that the given array represents a valid connected binary tree.
 *
 * ! 1 <= nums.length <= 15
 * ! 110 <= nums[i] <= 489
 * ! nums represents a valid binary tree with depth less than 5.
 */

class Solution {
public:
    int pathSum(std::vector<int>& nums)
    {
        /**
         *   depth i:   1      2   ...
         *             / \    / \
         * depth i+1: 1   2  3   4 ...
         *
         * node(i, j) = node at index j in depth i
         *
         * left child of node(i, j) = node(i + 1, 2 * j - 1)
         * right child of node(i, j) = node(i + 1, 2 * j)
         */
        std::unordered_map<int, int> map;
        for (const auto& digit : nums) {
            map[digit / 10] = digit % 10;
        }
        std::queue<std::pair<int, int>> queue; // <coord, sum to this node>
        queue.emplace(nums[0] / 10, nums[0] % 10);
        int result = 0;
        while (!queue.empty()) {
            const auto [coord, sum] = queue.front();
            queue.pop();
            const int depth = coord / 10;
            const int index = coord % 10;
            const int lChild = (depth + 1) * 10 + 2 * index - 1;
            const int rChild = lChild + 1;
            if (!map.count(lChild) && !map.count(rChild)) {
                result += sum;
            }
            if (map.count(lChild)) {
                queue.emplace(lChild, sum + map[lChild]);
            }
            if (map.count(rChild)) {
                queue.emplace(rChild, sum + map[rChild]);
            }
        }
        return result;
    }
};
