#include <vector>

/**
 * Given an integer array nums containing n integers, find the beauty of each subarray of size k.
 *
 * The beauty of a subarray is the xth smallest integer in the subarray if it is negative, or 0 if
 * there are fewer than x negative integers.
 *
 * Return an integer array containing n - k + 1 integers, which denote the beauty of the subarrays
 * in order from the first index in the array.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! n == nums.length
 * ! 1 <= n <= 10^5
 * ! 1 <= k <= n
 * ! 1 <= x <= k
 * ! -50 <= nums[i] <= 50
 */

class Solution {
public:
    std::vector<int> getSubarrayBeauty(std::vector<int>& nums, int k, int x)
    {
        const int n = nums.size();
        // use counting sort because -50 <= nums[i] <= 50
        std::vector<int> count(M, 0); // index 0 represents -50
        std::vector<int> result;
        result.reserve(n - k + 1);
        for (int left = 0, right = 0; right < n; ++right) {
            if (nums[right] < 0) {
                count[M + nums[right]]++;
            }
            if (right - left + 1 > k) {
                if (nums[left] < 0) {
                    count[M + nums[left]]--;
                }
                left++;
            }
            if (right - left + 1 == k) {
                result.push_back(helper(count, x));
            }
        }
        return result;
    }

private:
    static constexpr int M = 50;

    // return the xth smallest if it is negative,
    // or 0 if the num of negative integers is less than x
    int helper(const std::vector<int>& count, int x)
    {
        int sum = 0;
        for (int i = 0; i < count.size(); ++i) {
            sum += count[i];
            if (sum >= x)
                return i - M;
        }
        return 0;
    }
};