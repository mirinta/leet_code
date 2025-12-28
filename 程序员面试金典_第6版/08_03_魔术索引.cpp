#include <vector>

/**
 * 魔术索引。 在数组A[0...n-1]中，有所谓的魔术索引，满足条件A[i] =
 * i。给定一个有序整数数组，编写一种方法找出魔术索引，若有的话，在数组A中找出一个魔术索引，如果没有，则返回-1。若有多个魔术索引，返回索引值最小的一个。
 *
 * ! nums长度在[1, 1000000]之间
 * !此题为原书中的 Follow-up，即数组中可能包含重复元素的版本
 */

class Solution {
public:
    int findMagicIndex(std::vector<int>& nums)
    {
        const int n = nums.size();
        return find(0, n - 1, nums);
    }

private:
    int find(int lo, int hi, const std::vector<int>& nums)
    {
        if (lo > hi)
            return -1;

        const int mid = lo + (hi - lo) / 2;
        if (const int left = find(lo, mid - 1, nums); left != -1)
            return left;

        if (nums[mid] == mid)
            return mid;

        return find(mid + 1, hi, nums);
    }
};