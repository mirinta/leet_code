#include <unordered_map>
#include <vector>

/**
 * You are given two integer arrays nums1 and nums2. You are tasked to implement a data structure
 * that supports queries of two types:
 *
 * 1. Add a positive integer to an element of a given index in the array nums2.
 *
 * 2. Count the number of pairs (i, j) such that nums1[i] + nums2[j] equals a given value (0 <= i <
 * nums1.length and 0 <= j < nums2.length).
 *
 * Implement the FindSumPairs class:
 *
 * - FindSumPairs(int[] nums1, int[] nums2) Initializes the FindSumPairs object with two integer
 * arrays nums1 and nums2.
 *
 * - void add(int index, int val) Adds val to nums2[index], i.e., apply nums2[index] += val.
 *
 * - int count(int tot) Returns the number of pairs (i, j) such that nums1[i] + nums2[j] == tot.
 *
 * ! 1 <= nums1.length <= 1000
 * ! 1 <= nums2.length <= 10^5
 * ! 1 <= nums1[i] <= 10^9
 * ! 1 <= nums2[i] <= 10^5
 * ! 0 <= index < nums2.length
 * ! 1 <= val <= 10^5
 * ! 1 <= tot <= 10^9
 * ! At most 1000 calls are made to add and count each.
 */

class FindSumPairs {
public:
    FindSumPairs(std::vector<int>& nums1, std::vector<int>& nums2) : nums2(nums2)
    {
        for (const auto& val : nums1) {
            map1[val]++;
        }
        for (const auto& val : nums2) {
            map2[val]++;
        }
    }

    void add(int index, int val)
    {
        if (--map2[nums2[index]] == 0) {
            map2.erase(nums2[index]);
        }
        map2[nums2[index] + val]++;
        nums2[index] += val;
    }

    int count(int tot)
    {
        int result = 0;
        for (const auto& [val, freq] : map1) {
            const int target = tot - val;
            if (map2.count(target)) {
                result += freq * map2[target];
            }
        }
        return result;
    }

private:
    std::unordered_map<int, int> map1;
    std::unordered_map<int, int> map2;
    std::vector<int> nums2;
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */