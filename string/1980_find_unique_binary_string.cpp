#include <bitset>
#include <string>
#include <unordered_set>
#include <vector>

/**
 * Given an array of strings nums containing n unique binary strings each of length n, return a
 * binary string of length n that does not appear in nums. If there are multiple answers, you may
 * return any of them.
 *
 * ! n == nums.length
 * ! 1 <= n <= 16
 * ! nums[i].length == n
 * ! nums[i] is either '0' or '1'.
 * ! All the strings of nums are unique.
 */

class Solution {
public:
    std::string findDifferentBinaryString(std::vector<std::string>& nums)
    {
        return approach2(nums);
    }

private:
    // time O(N), space O(1)
    std::string approach2(const std::vector<std::string>& nums)
    {
        // final answer has at least one bit difference between each nums[i]
        std::string result;
        result.reserve(nums.size());
        for (int i = 0; i < nums.size(); ++i) {
            result.push_back(nums[i][i] == '0' ? '1' : '0');
        }
        return result;
    }

    // time O(N^2), space O(N)
    std::string approach1(const std::vector<std::string>& nums)
    {
        const int n = nums.size();
        std::unordered_set<int> visited;
        for (const auto& s : nums) {
            visited.insert(std::stoi(s, nullptr, 2)); // binary string to integer
        }
        for (int i = 0; i < (1 << n); ++i) {
            if (!visited.count(i))
                return std::bitset<16>(i).to_string().substr(16 - n); // at most 16 bits
        }
        return {};
    }
};
