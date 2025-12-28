#include <algorithm>
#include <vector>

/**
 * You are given an array nums consisting of positive integers.
 *
 * You are also given an integer array queries of size m. For the ith query, you want to make all of
 * the elements of nums equal to queries[i]. You can perform the following operation on the array
 * any number of times:
 *
 * Increase or decrease an element of the array by 1.
 * Return an array answer of size m where answer[i] is the minimum number of operations to make all
 * elements of nums equal to queries[i].
 *
 * Note that after each query the array is reset to its original state.
 *
 * ! n == nums.length
 * ! m == queries.length
 * ! 1 <= n, m <= 10^5
 * ! 1 <= nums[i], queries[i] <= 10^9
 */

class Solution {
public:
    std::vector<long long> minOperations(std::vector<int>& nums, std::vector<int>& queries)
    {
        const int n = nums.size();
        const int m = queries.size();
        std::sort(nums.begin(), nums.end());
        std::vector<long long> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        std::vector<long long> result(m);
        for (int i = 0; i < m; ++i) {
            result[i] = calcOperations(queries[i], nums, presum);
        }
        return result;
    }

private:
    // change {x0, x1, x2, x3, x4} to q
    // #operations = ((x2-x0)*q - sum[x0:x1]) - (sum[x2:x4] - (x4+1-x2)*q)
    //                                             +------+
    //                                             |      |
    //                                             |      |
    //                                             |      |
    //                                     +-------+      |
    //                                     |       |      |
    //                                     |       |      |
    //                             +-------+       |      |
    //                             |       |       |      |
    //      q ---------------------+-------+-------+------+-------
    //                             |       |       |      |
    //                     +-------+       |       |      |
    //                     |       |       |       |      |
    //             +-------+       |       |       |      |
    //             |       |       |       |       |      |
    //             |       |       |       |       |      |
    //             |       |       |       |       |      |
    //             |       |       |       |       |      |
    //       ------+-------+-------+-------+-------+------+-------
    //             x0      x1      x2      x3      x4
    long long calcOperations(long long q, const std::vector<int>& nums, const std::vector<long long>& presum)
    {
        const int begin = 0;
        const int end = nums.size() - 1;
        const int index = std::lower_bound(nums.begin(), nums.end(), q) - nums.begin();
        const long long area1 = (index - begin) * q - (presum[index] - presum[begin]);
        const long long area2 = (presum[end + 1] - presum[index]) - (end - index + 1) * q;
        return area1 + area2;
    }
};