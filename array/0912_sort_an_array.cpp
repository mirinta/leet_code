#include <vector>

/**
 * Given an array of integers nums, sort the array in ascending order and return it.
 *
 * You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and
 * with the smallest space complexity possible.
 *
 * ! 1 <= nums.length <= 5 * 10^4
 * !-5 * 104 <= nums[i] <= 5 * 10^4
 */

class Solution {
public:
    std::vector<int> sortArray(std::vector<int>& nums)
    {
        mergeSort(nums);
        return nums;
    }

private:
    void mergeSort(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> aux(n);
        mergeSort(nums, aux, 0, n - 1);
    }

    void mergeSort(std::vector<int>& nums, std::vector<int>& aux, int lo, int hi)
    {
        if (lo >= hi)
            return;

        const int mid = lo + (hi - lo) / 2;
        mergeSort(nums, aux, lo, mid);
        mergeSort(nums, aux, mid + 1, hi);
        merge(nums, aux, lo, mid, hi);
    }

    void merge(std::vector<int>& nums, std::vector<int>& aux, int lo, int mid, int hi)
    {
        for (int k = lo; k <= hi; ++k) {
            aux[k] = nums[k];
        }
        for (int i = lo, j = mid + 1, k = lo; k <= hi; ++k) {
            if (i > mid || (j <= hi && aux[j] < aux[i])) {
                nums[k] = aux[j++];
            } else {
                nums[k] = aux[i++];
            }
        }
    }
};
