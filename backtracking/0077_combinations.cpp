#include <vector>

/**
 * Given two integers "n" and "k", return all possible combinations of "k" numbers chosen from the
 * range "[1, n]";
 *
 * You may return the answer in any order.
 *
 * ! 1 <= n <= 20
 * ! 1 <= k <= n
 */

class Solution
{
public:
    std::vector<std::vector<int>> combine(int n, int k)
    {
        std::vector<std::vector<int>> result;
        std::vector<int> combination;
        backtrack(result, combination, 1, n, k);
        return result;
    }

private:
    void backtrack(std::vector<std::vector<int>>& result, std::vector<int>& combination, int start,
                   int n, int k)
    {
        if (combination.size() == k) {
            result.push_back(combination);
            return;
        }
        for (int i = start; i <= n; ++i) {
            combination.push_back(i);
            backtrack(result, combination, i + 1, n, k);
            combination.pop_back();
        }
    }
};