#include <algorithm>
#include <queue>
#include <vector>

/**
 * You are given two integer arrays "nums1" and "nums2" both of the same length. The advantage of
 * "nums1" with respect to "nums2" is the number of indicies "i" for which "nums1[i] > nums2[i]".
 *
 * Return any permutation of "nums1" that maximizes its advantage with respect to "nums2".
 *
 * Example:
 * Input: nums1 = [12, 24, 8, 32], nums2 = [13, 25, 32, 11]
 * Output: [24, 32, 8, 12]
 */

class Solution {
public:
    std::vector<int> advantageCount(std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        if (nums1.size() != nums2.size() || nums1.empty())
            return {};

        std::vector<int> result(nums1.size(), 0);
        // sort nums1 in ascending order
        std::sort(nums1.begin(), nums1.end());
        // sort indices of nums2 in descending order based on values
        auto compIndex = [&nums2](int left, int right) { return nums2[left] < nums2[right]; };
        std::priority_queue<size_t, std::vector<size_t>, decltype(compIndex)> maxPq{compIndex};
        for (size_t i = 0; i < nums2.size(); ++i) {
            maxPq.push(i);
        }
        // compare with nums2's max value in each round:
        // - suppose MAX2 is the max value of nums2, and its index is I;
        // - suppose MIN1 and MAX1 are the min and max values of nums1 (int this round);
        // - our goal is to put an appropriate value at location I of nums1;
        // - if MAX1 > MAX2, nums1[I] = MAX1; otherwise, nums1[i] = MIN1
        for (size_t left = 0, right = nums1.size() - 1; !maxPq.empty(); maxPq.pop()) {
            const auto i = maxPq.top();
            if (nums1[right] > nums2[i]) {
                result[i] = nums1[right--];
            } else {
                result[i] = nums1[left++];
            }
        }
        return result;
    }
};