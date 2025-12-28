#include <string>

/**
 * Given string num representing a non-negative integer num, and an integer k, return the smallest
 * possible integer after removing k digits from num.
 *
 * ! 1 <= k <= num.length <= 10^5
 * ! num consists of only digits.
 * ! num does not have any leading zeros except for the zero itself.
 */

class Solution {
public:
    std::string removeKdigits(std::string num, int k)
    {
        if (num.size() <= k)
            return "0";

        std::string result;
        for (const auto& c : num) {
            while (k > 0 && !result.empty() && c < result.back()) {
                result.pop_back();
                k--;
            }
            result.push_back(c);
        }
        while (k > 0 && !result.empty()) {
            result.pop_back();
            k--;
        }
        if (result.empty())
            return "0";

        int start = 0;
        while (start < result.size() && result[start] == '0') {
            start++;
        }
        if (start == result.size())
            return "0";

        return {result.begin() + start, result.end()};
    }
};