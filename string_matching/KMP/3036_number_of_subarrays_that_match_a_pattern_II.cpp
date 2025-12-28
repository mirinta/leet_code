#include <vector>

/**
 * You are given a 0-indexed integer array nums of size n, and a 0-indexed integer array pattern of
 * size m consisting of integers -1, 0, and 1.
 *
 * A subarray nums[i..j] of size m + 1 is said to match the pattern if the following conditions hold
 * for each element pattern[k]:
 *
 * - nums[i + k + 1] > nums[i + k] if pattern[k] == 1.
 *
 * - nums[i + k + 1] == nums[i + k] if pattern[k] == 0.
 *
 * - nums[i + k + 1] < nums[i + k] if pattern[k] == -1.
 *
 * Return the count of subarrays in nums that match the pattern.
 *
 * ! 2 <= n == nums.length <= 10^6
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= m == pattern.length < n
 * ! -1 <= pattern[i] <= 1
 */

class Solution {
public:
    int countMatchingSubarrays(std::vector<int>& nums, std::vector<int>& pattern)
    {
        std::vector<int> v;
        v.reserve(nums.size() - 1);
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > nums[i - 1]) {
                v.emplace_back(1);
            } else if (nums[i] < nums[i - 1]) {
                v.emplace_back(-1);
            } else {
                v.emplace_back(0);
            }
        }
        return kmp(v, pattern);
    }

private:
    int kmp(const std::vector<int>& v, const std::vector<int>& p)
    {
        const int n = v.size();
        const int m = p.size();
        const auto next = preprocess(p);
        int i = 0;
        int j = 0;
        int result = 0;
        while (i < n) {
            if (v[i] == p[j]) {
                i++;
                j++;
            } else if (j > 0) {
                j = next[j - 1];
            } else {
                i++;
            }
            if (j == m) {
                result++;
                j = next[m - 1];
            }
        }
        return result;
    }

    std::vector<int> preprocess(const std::vector<int>& p)
    {
        const int n = p.size();
        std::vector<int> next(n, 0);
        for (int i = 1; i < n; ++i) {
            int L = next[i - 1];
            while (L > 0 && p[L] != p[i]) {
                L = next[L - 1];
            }
            next[i] = L + (p[L] == p[i]);
        }
        return next;
    }
};