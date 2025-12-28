#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed integer array mapping which represents the mapping rule of a shuffled
 * decimal system. mapping[i] = j means digit i should be mapped to digit j in this system.
 *
 * The mapped value of an integer is the new integer obtained by replacing each occurrence of digit
 * i in the integer with mapping[i] for all 0 <= i <= 9.
 *
 * You are also given another integer array nums. Return the array nums sorted in non-decreasing
 * order based on the mapped values of its elements.
 *
 * Notes:
 *
 * Elements with the same mapped values should appear in the same relative order as in the input.
 * The elements of nums should only be sorted based on their mapped values and not be replaced by
 * them.
 *
 * ! mapping.length == 10
 * ! 0 <= mapping[i] <= 9
 * ! All the values of mapping[i] are unique.
 * ! 1 <= nums.length <= 3 * 10^4
 * ! 0 <= nums[i] < 10^9
 */

class Solution {
public:
    std::vector<int> sortJumbled(std::vector<int>& mapping, std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<std::pair<int, int>> v;
        v.reserve(n);
        for (int i = 0; i < n; ++i) {
            v.emplace_back(helper(nums[i], mapping), i);
        }
        std::sort(v.begin(), v.end(), [](const auto& p1, const auto& p2) {
            if (p1.first != p2.first)
                return p1.first < p2.first;

            return p1.second < p2.second;
        });
        std::vector<int> result;
        result.reserve(n);
        for (const auto& [mapped, index] : v) {
            result.push_back(nums[index]);
        }
        return result;
    }

private:
    int helper(int val, const std::vector<int>& mapping)
    {
        if (val == 0)
            return mapping[0];

        int base = 1;
        int result = 0;
        while (val) {
            result += base * mapping[val % 10];
            val /= 10;
            base *= 10;
        }
        return result;
    }
};
