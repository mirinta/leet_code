#include <vector>

/**
 * Find all valid combinations of "k" numbers that sum up to "n" such that the following conditions
 * are true:
 *
 * - Only numbers 1 through 9 are used.
 *
 * - Each number is used at most once.
 *
 * Return a list of all possible valid combinations. The list must not contain the same combination
 * twice, and the combinations may be returned in any order.
 *
 * ! 2 <= k <= 9
 * ! 1 <= n <= 60
 */

class Solution {
public:
    std::vector<std::vector<int>> combinationSum3(int k, int n)
    {
        std::vector<int> path;
        backtrack1(path, n, 1, k);
        // backtrack2(path, n, 1, k);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    // approach1:
    // enumerate each number of the final answer,
    // options of the current number are in the range [i, 9]
    void backtrack1(std::vector<int>& path, int targetSum, int i, int k)
    {
        if (targetSum == 0 && path.size() == k) {
            result.push_back(path);
            return;
        }
        for (int j = i; j <= 9; ++j) {
            path.push_back(j);
            backtrack1(path, targetSum - j, j + 1, k);
            path.pop_back();
        }
    }

    // approach2:
    // choose/ignore option i, i is in the range [1,9]
    void backtrack2(std::vector<int>& path, int targetSum, int i, int k)
    {
        if (targetSum == 0 && path.size() == k) {
            result.push_back(path);
            return;
        }
        if (i > 9)
            return;

        path.push_back(i);
        backtrack2(path, targetSum - i, i + 1, k);
        path.pop_back();
        backtrack2(path, targetSum, i + 1, k);
    }
};
