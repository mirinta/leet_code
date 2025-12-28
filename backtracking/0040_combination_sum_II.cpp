#include <algorithm>
#include <functional>
#include <vector>

/**
 * Given a collection of candidate numbers "candidates" and a target number "target", find all
 * unique combinations in "candidates" where the candidate numbers sum to "target".
 *
 * Each number in "candidates" may only be used once in the combinations.
 *
 * Note: The solution set must not contain duplicate combinations.
 *
 * ! 1 <= candidates.length <= 100
 * ! 1 <= candidates[i] <= 50
 * ! 1 <= target <= 30
 */

#include <algorithm>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target)
    {
        std::sort(candidates.begin(), candidates.end());
        std::vector<int> path;
        std::vector<std::vector<int>> result;
        std::function<void(int, int)> backtrack = [&](int i, int sum) {
            if (sum == target) {
                result.push_back(path);
                return;
            }
            for (int j = i; j < candidates.size(); ++j) {
                if (j > i && candidates[j] == candidates[j - 1])
                    continue;

                if (sum + candidates[j] > target)
                    break;

                path.push_back(candidates[j]);
                backtrack(j + 1, sum + candidates[j]);
                path.pop_back();
            }
        };
        backtrack(0, 0);
        return result;
    }
};
