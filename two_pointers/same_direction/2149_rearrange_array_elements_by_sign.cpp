#include <vector>

/**
 * You are given a 0-indexed integer array nums of even length consisting of an equal number of
 * positive and negative integers.
 *
 * You should rearrange the elements of nums such that the modified array follows the given
 * conditions:
 *
 * 1. Every consecutive pair of integers have opposite signs.
 *
 * 2. For all integers with the same sign, the order in which they were present in nums is
 * preserved.
 *
 * 3. The rearranged array begins with a positive integer.
 *
 * Return the modified array after rearranging the elements to satisfy the aforementioned
 * conditions.
 *
 * ! 2 <= nums.length <= 2 * 10^5
 * ! nums.length is even
 * ! 1 <= |nums[i]| <= 10^5
 * ! nums consists of equal number of positive and negative integers.
 */

class Solution {
public:
    std::vector<int> rearrangeArray(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    // Two-pointers, TC = O(N), SC = O(N)
    std::vector<int> approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int positive = 0;
        int negative = 1;
        std::vector<int> result(n);
        for (const auto& val : nums) {
            if (val > 0) {
                result[positive] = val;
                positive += 2;
            } else {
                result[negative] = val;
                negative += 2;
            }
        }
        return result;
    }

    // Simulation, TC = O(N), SC = O(N)
    std::vector<int> approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> positives;
        positives.reserve(n / 2);
        std::vector<int> negatives;
        negatives.reserve(n / 2);
        for (const auto& val : nums) {
            if (val > 0) {
                positives.push_back(val);
            } else {
                negatives.push_back(val);
            }
        }
        std::vector<int> result(n);
        for (int i = 0, j = 0, k = 0; i < n; ++i) {
            if (i % 2 == 0) {
                result[i] = positives[j++];
            } else {
                result[i] = negatives[k++];
            }
        }
        return result;
    }
};