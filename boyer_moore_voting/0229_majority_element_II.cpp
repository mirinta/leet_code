#include <unordered_map>
#include <vector>

/**
 * Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
 *
 *
 * ! 1 <= nums.length <= 5 * 10^4
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution {
public:
    std::vector<int> majorityElement(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    std::vector<int> approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int count1 = 0;
        int value1 = 0;
        int count2 = 0;
        int value2 = 0;
        for (const auto& val : nums) {
            if (value1 == val) {
                count1++;
            } else if (value2 == val) {
                count2++;
            } else if (count1 == 0) {
                value1 = val;
                count1 = 1;
            } else if (count2 == 0) {
                value2 = val;
                count2 = 1;
            } else {
                count1--;
                count2--;
            }
        }
        count1 = 0;
        count2 = 0;
        for (const auto& val : nums) {
            if (val == value1) {
                count1++;
            } else if (val == value2) {
                count2++;
            }
        }
        std::vector<int> result;
        if (count1 > n / 3) {
            result.push_back(value1);
        }
        if (count2 > n / 3) {
            result.push_back(value2);
        }
        return result;
    }

    std::vector<int> approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            map[val]++;
        }
        std::vector<int> result;
        for (const auto& [val, freq] : map) {
            if (freq > n / 3) {
                result.push_back(val);
            }
        }
        return result;
    }
};