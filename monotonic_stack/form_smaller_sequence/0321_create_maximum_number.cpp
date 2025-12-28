#include <vector>

/**
 * You are given two integer arrays nums1 and nums2 of lengths m and n respectively. nums1 and nums2
 * represent the digits of two numbers. You are also given an integer k.
 *
 * Create the maximum number of length k <= m + n from digits of the two numbers. The relative order
 * of the digits from the same array must be preserved.
 *
 * Return an array of the k digits representing the answer.
 *
 * ! m == nums1.length
 * ! n == nums2.length
 * ! 1 <= m, n <= 500
 * ! 0 <= nums1[i], nums2[i] <= 9
 * ! 1 <= k <= m + n
 */

class Solution {
public:
    std::vector<int> maxNumber(std::vector<int>& nums1, std::vector<int>& nums2, int k)
    {
        const int m = nums1.size();
        const int n = nums2.size();
        std::vector<int> result;
        for (int k1 = 0; k1 <= std::min(k, m); ++k1) {
            const int k2 = k - k1;
            if (k2 > n)
                continue;

            auto seq1 = helper(nums1, m - k1);
            auto seq2 = helper(nums2, n - k2);
            result = std::max(result, merge(seq1, seq2));
        }
        return result;
    }

private:
    // return the largest subsequence of nums by removing exatcly x elements
    std::vector<int> helper(const std::vector<int>& nums, int x)
    {
        if (x >= nums.size())
            return {};

        std::vector<int> result;
        for (const auto& val : nums) {
            while (!result.empty() && val > result.back() && x > 0) {
                result.pop_back();
                x--;
            }
            result.push_back(val);
        }
        while (x > 0) {
            result.pop_back();
            x--;
        }
        return result;
    }

    std::vector<int> merge(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        std::vector<int> result(nums1.size() + nums2.size());
        for (int i = 0; i < result.size(); ++i) {
            if (nums1 > nums2) {
                result[i] = nums1.front();
                nums1.erase(nums1.begin());
            } else {
                result[i] = nums2.front();
                nums2.erase(nums2.begin());
            }
        }
        return result;
    }
};