#include <vector>

/**
 * You are given an integer array nums. You may rearrange the elements in any order.
 *
 * The alternating score of an array arr is defined as:
 *
 * - score = arr[0]2 - arr[1]2 + arr[2]2 - arr[3]2 + ...
 *
 * Return an integer denoting the maximum possible alternating score of nums after rearranging its elements.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -4 * 10^4 <= nums[i] <= 4 * 10^4
 */

class Solution {
public:
    long long maxAlternatingSum(std::vector<int>& nums)
    {
        // score = square sum of even index elements - square sum of odd index elements
        // score = A - B
        // max score <=> maximize A and minimize B
        const int n = nums.size();
        std::sort(nums.begin(), nums.end(),
                  [](const auto& e1, const auto& e2) { return 1LL * e1 * e1 < 1LL * e2 * e2; });
        long long B = 0;
        for (int i = 0; i < n / 2; ++i) {
            B += 1LL * nums[i] * nums[i];
        }
        long long A = 0;
        for (int i = n / 2; i < n; ++i) {
            A += 1LL * nums[i] * nums[i];
        }
        return A - B;
    }
};
