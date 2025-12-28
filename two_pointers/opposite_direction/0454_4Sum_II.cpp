#include <unordered_map>
#include <vector>

/**
 * Given four integer arrays "nums1", "nums2", "nums3" and "nums4" all of length "n", return the
 * number of tuples (i, j, k, l) such that:
 *
 * - 0 <= i, j, k, l < n
 *
 * - nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0
 *
 * ! n == nums1.length
 * ! n == nums2.length
 * ! n == nums3.length
 * ! n == nums4.length
 * ! 1 <= n <= 200
 * ! -2^28 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 2^28
 */

class Solution {
public:
    int fourSumCount(std::vector<int>& nums1, std::vector<int>& nums2, std::vector<int>& nums3, std::vector<int>& nums4)
    {
        std::unordered_map<long long, int> map; // key = nums1[i]+nums2[j], value = frequency
        for (int i = 0; i < nums1.size(); ++i) {
            for (int j = 0; j < nums2.size(); ++j) {
                map[(long long)nums1[i] + nums2[j]]++;
            }
        }
        int result = 0;
        for (int k = 0; k < nums3.size(); ++k) {
            for (int l = 0; l < nums4.size(); ++l) {
                const long long sum = (long long)nums3[k] + nums4[l];
                result += map[-sum];
            }
        }
        return result;
    }
};
