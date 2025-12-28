#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed array of strings "nums", where each string is of equal length and
 * consists of only digits.
 *
 * You are also given a 0-indexed 2D integer array "queries" where queries[i] = [k_i, trim_i]. For
 * each queries[i], you need to :
 *
 * - Trim each number in nums to its rightmost trim_i digits.
 *
 * - Determine the index of the (k_i)th smallest trimmed number in nums. If two trimmed numbers are
 * equal, the number with the lower index is considered to be smaller.
 *
 * - Reset each number in nums to its original length.
 *
 * Return an array "answer" of the same length as queries, where answer[i] is the answer to the ith
 * query.
 *
 * Note:
 *
 * - To trim to the rightmost x digits means to keep removing the leftmost gits, until only x digits
 * remain.
 *
 * - Strings in nums may contain leading zeros.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i].length <= 100
 * ! nums[i] consists of only digits.
 * ! All nums[i].length are equal.
 * ! 1 <= queries.length <= 100
 * ! queries[i].length == 2
 * ! 1 <= k_i <= nums.length
 * ! 1 <= trim_i <= nums[i].length
 */

class Solution {
public:
    std::vector<int> smallestTrimmedNumbers(const std::vector<std::string>& nums,
                                            const std::vector<std::vector<int>>& queries)
    {
        if (nums.empty() || queries.empty())
            return {};

        std::vector<int> result;
        std::unordered_map<int, std::vector<std::pair<std::string, int>>> memo;
        for (const auto& query : queries) {
            const auto& k = query[0];
            const auto& trim = query[1];
            if (!memo.count(trim)) {
                for (size_t i = 0; i < nums.size(); ++i) {
                    memo[trim].emplace_back(nums[i].substr(nums[i].size() - trim, trim), i);
                }
                std::sort(memo[trim].begin(), memo[trim].end());
            }
            result.push_back(memo[trim][k - 1].second);
        }
        return result;
    }
};
