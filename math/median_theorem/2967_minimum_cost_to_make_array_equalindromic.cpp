#include <algorithm>
#include <string>
#include <vector>

/**
 * You are given a 0-indexed integer array nums having length n.
 *
 * You are allowed to perform a special move any number of times (including zero) on nums. In one
 * special move you perform the following steps in order:
 *
 * - Choose an index i in the range [0, n - 1], and a positive integer x.
 *
 * - Add |nums[i] - x| to the total cost.
 *
 * - Change the value of nums[i] to x.
 *
 * A palindromic number is a positive integer that remains the same when its digits are reversed.
 * For example, 121, 2552 and 65756 are palindromic numbers whereas 24, 46, 235 are not palindromic
 * numbers.
 *
 * An array is considered equalindromic if all the elements in the array are equal to an integer y,
 * where y is a palindromic number less than 109.
 *
 * Return an integer denoting the minimum possible total cost to make nums equalindromic by
 * performing any number of special moves.
 *
 * ! 1 <= n <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution {
public:
    long long minimumCost(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        const int median = nums[n / 2];
        const auto [lower, upper] = getPalindromeBounds(median);
        return std::min(calcCost(nums, lower), calcCost(nums, upper));
    }

private:
    int isPalindrome(int val)
    {
        const auto s = std::to_string(val);
        for (int i = 0, j = s.size() - 1; i < j; ++i, --j) {
            if (s[i] != s[j])
                return false;
        }
        return true;
    }

    std::pair<int, int> getPalindromeBounds(int val)
    {
        // a = max palindrome <= val
        // b = min palindrome >= val
        int a = val;
        while (!isPalindrome(a)) {
            a--;
        }
        int b = val;
        while (!isPalindrome(b)) {
            b++;
        }
        return std::make_pair(a, b);
    }

    long long calcCost(const std::vector<int>& nums, int y)
    {
        long long result = 0;
        for (const auto& val : nums) {
            result += std::abs(val - y);
        }
        return result;
    }
};