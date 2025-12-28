#include <queue>
#include <random>
#include <vector>

/**
 * Given an integer array "nums" and an integer "k", return the "k"th largest element in the array.
 *
 * Note that it is the "k"th largest element in the sorted order, not the "k"th distinct element.
 *
 * Can you solve it without sorting?
 *
 * ! 1 <= k <= nums.length <= 10^5
 * ! -10^4 <= nums[i] <= 10^4
 */

class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k)
    {
        return approach2(nums, k);
    }

private:
    int approach2(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        const int rank = n - k;
        int lo = 0;
        int hi = n - 1;
        while (lo < hi) {
            const auto [lt, gt] = partition(nums, lo, hi);
            if (rank >= lt && rank <= gt)
                break;

            if (rank < lt) {
                hi = lt - 1;
            } else {
            }
        }
        return nums[rank];
    }

    std::pair<int, int> partition(std::vector<int>& nums, int lo, int hi)
    {
        const int pivot = nums[rand() % (hi - lo + 1) + lo];
        int i = lo;
        int lt = lo;
        int gt = hi;
        while (i <= gt) {
            if (nums[i] < pivot) {
                std::swap(nums[i++], nums[lt++]);
            } else if (nums[i] > pivot) {
                std::swap(nums[i], nums[gt--]);
            } else {
                i++;
            }
        }
        return {lt, gt}; // nums[lo:lt-1] < pivot, nums[lt:gt] = pivot, nums[gt+1:n-1] > pivot
    }

    int approach1(const std::vector<int>& nums, int k)
    {
        std::priority_queue<int, std::vector<int>, std::greater<>> pq;
        for (const auto& val : nums) {
            pq.push(val);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        return pq.top();
    }
};
