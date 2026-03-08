#include <string>
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
        // answer and s[i] must have at least one different character
        // then we can build the answer:
        // - answer[0] is different to s[0][0]
        // - answer[1] is different to s[1][1]
        // ...
        const int n = nums.size();
        std::string result;
        result.reserve(n);
        for (int i = 0; i < n; ++i) {
            result.push_back(1 - (nums[i][i] - '0') + '0');
        }
        return result;
    }
};
