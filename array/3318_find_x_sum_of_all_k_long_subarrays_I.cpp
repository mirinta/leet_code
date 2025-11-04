#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given an array nums of n integers and two integers k and x.
 *
 * The x-sum of an array is calculated by the following procedure:
 *
 * - Count the occurrences of all elements in the array.
 *
 * - Keep only the occurrences of the top x most frequent elements. If two elements have the same
 * number of occurrences, the element with the bigger value is considered more frequent.
 *
 * - Calculate the sum of the resulting array.
 *
 * Note that if an array has less than x distinct elements, its x-sum is the sum of the array.
 *
 * Return an integer array answer of length n - k + 1 where answer[i] is the x-sum of the subarray
 * nums[i..i + k - 1].
 *
 * ! 1 <= n == nums.length <= 50
 * ! 1 <= nums[i] <= 50
 * ! 1 <= x <= k <= nums.length
 */

class Solution
{
public:
    std::vector<int> findXSum(std::vector<int>& nums, int k, int x)
    {
        const int n = nums.size();
        std::unordered_map<int, int> map;
        std::vector<int> result;
        for (int left = 0, right = 0; right < n; ++right) {
            map[nums[right]]++;
            if (right >= k) {
                map[nums[left]]--;
                left++;
            }
            if (right < k - 1)
                continue;

            std::vector<std::pair<int, int>> v{map.begin(), map.end()};
            std::sort(v.begin(), v.end(), [](const auto& p1, const auto& p2) {
                if (p1.second != p2.second)
                    return p1.second > p2.second;

                return p1.first > p2.first;
            });
            int sum = 0;
            for (int i = 0; i < std::min<int>(x, v.size()); ++i) {
                sum += v[i].first * v[i].second;
            }
            result.emplace_back(sum);
        }
        return result;
    }
};