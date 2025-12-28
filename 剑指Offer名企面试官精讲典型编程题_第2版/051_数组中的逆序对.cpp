#include <vector>

/**
 * 在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。
 *
 * ! 0 <= 数组长度 <= 50000
 */

class Solution {
public:
    int reversePairs(std::vector<int>& nums)
    {
        // based on merge sort
        std::vector<int> aux(nums);
        mergeSort(nums, aux, 0, nums.size() - 1);
        return result;
    }

private:
    int result = 0;

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
        // [lo...i...mid] [mid+1...j...hi]
        for (int k = lo, i = lo, j = mid + 1; k <= hi; ++k) {
            if (i > mid) {
                nums[k] = aux[j++];
                continue;
            }
            if (j > hi) {
                nums[k] = aux[i++];
                continue;
            }
            if (aux[i] > aux[j]) {
                nums[k] = aux[j++];
                // aux[i] > aux[j] means:
                // - we can make a reverse pair with aux[p] and aux[j], where p=i,i+1,...,mid
                // - thus, the number of pairs = mid - i + 1
                result += mid - i + 1;
            } else {
                nums[k] = aux[i++];
            }
        }
    }
};