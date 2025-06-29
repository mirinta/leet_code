#include <vector>

/**
 * Given two sorted 0-indexed integer arrays nums1 and nums2 as well as an integer k, return the kth
 * (1-based) smallest product of nums1[i] * nums2[j] where 0 <= i < nums1.length and 0 <= j <
 * nums2.length.
 *
 * ! 1 <= nums1.length, nums2.length <= 5 * 10^4
 * ! -10^5 <= nums1[i], nums2[j] <= 10^5
 * ! 1 <= k <= nums1.length * nums2.length
 * ! nums1 and nums2 are sorted.
 */

class Solution
{
public:
    long long kthSmallestProduct(std::vector<int>& nums1, std::vector<int>& nums2, long long k)
    {
        const int n1 = nums1.size();
        const int n2 = nums2.size();
        const int pos1 = find(nums1); // nums1[pos1:n1) >= 0
        const int pos2 = find(nums2); // nums2[pos2:n2) >= 0
        long long lo = -1e11;
        long long hi = 1e11;
        while (lo <= hi) {
            const long long mid = lo + (hi - lo) / 2;
            long long count = 0; // num of product <= mid
            // case 1: nums1[0:pos1) < 0 and nums2[0:pos2) < 0
            for (int i1 = 0, i2 = pos2 - 1; i1 < pos1 && i2 >= 0;) {
                if (1LL * nums1[i1] * nums2[i2] > mid) {
                    i1++;
                } else {
                    count += pos1 - i1; // fix nums2[i2], nums1[i1:pos1) are valid
                    i2--;
                }
            }
            // case 2: nums1[0:pos1) < 0 and nums2[pos2:n2) >= 0
            for (int i1 = 0, i2 = pos2; i1 < pos1 && i2 < n2;) {
                if (1LL * nums1[i1] * nums2[i2] > mid) {
                    i2++;
                } else {
                    count += n2 - i2; // fix nums1[i1], nums2[i2:n2) are valid
                    i1++;
                }
            }
            // case 3: nums1[pos1:n1) >= 0 and nums2[0:pos2) < 0
            for (int i1 = pos1, i2 = 0; i1 < n1 && i2 < pos2;) {
                if (1LL * nums1[i1] * nums2[i2] > mid) {
                    i1++;
                } else {
                    count += n1 - i1; // fix nums2[i2], nums1[i1:n1) are valid
                    i2++;
                }
            }
            // case 4: nums1[pos1:n1) >= 0 and nums2[pos2:n2) >= 0
            for (int i1 = pos1, i2 = n2 - 1; i1 < n1 && i2 >= pos2;) {
                if (1LL * nums1[i1] * nums2[i2] > mid) {
                    i2--;
                } else {
                    count += i2 - pos2 + 1; // fix nums1[i1], nums2[pos2:i2] are valid
                    i1++;
                }
            }
            if (count < k) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return lo;
    }

private:
    int find(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int pos = 0;
        while (pos < n && nums[pos] < 0) {
            pos++;
        }
        return pos;
    }
};
