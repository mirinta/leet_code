#include <string>
#include <vector>

/**
 * An additive number is a string whose digits can form an additive sequence.
 *
 * A valid additive sequence should contain at least three numbers. Except for the first two
 * numbers, each subsequent number in the sequence must be the sum of the preceding two.
 *
 * Given a string containing only digits, return true if it is an additive number or false
 * otherwise.
 *
 * Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02,
 * 3 is invalid.
 *
 * ! 1 <= num.length <= 35
 * ! num consists only of digits.
 */

class Solution {
public:
    bool isAdditiveNumber(const std::string& num)
    {
        std::vector<std::string> substrings;
        return backtrack(substrings, 0, num);
    }

private:
    bool backtrack(std::vector<std::string>& substrings, int start, const std::string& s)
    {
        if (start == s.size())
            return substrings.size() >= 3;

        const int m = substrings.size();
        for (int end = start; end < s.size(); ++end) {
            if (end > start && s[start] == '0')
                return false;

            const auto substr = s.substr(start, end - start + 1);
            std::string sum(s.size() + 1, '9');
            if (m >= 2) {
                sum = add(substrings[m - 1], substrings[m - 2]);
            }
            if (isGreaterThan(substr, sum))
                return false;

            if (m < 2 || substr == sum) {
                substrings.push_back(substr);
                if (backtrack(substrings, end + 1, s))
                    return true;

                substrings.pop_back();
            }
        }
        return false;
    }

    bool isGreaterThan(const std::string& s1, const std::string& s2)
    {
        if (s1.size() != s2.size())
            return s1.size() > s2.size();

        for (int i = 0; i < s1.size(); ++i) {
            if (s1[i] > s2[i])
                return true;
        }
        return false;
    }

    std::string add(const std::string& s1, const std::string& s2)
    {
        std::string result;
        int carry = 0;
        int i = s1.size() - 1;
        int j = s2.size() - 1;
        while (i >= 0 || j >= 0) {
            const int val1 = i >= 0 ? s1[i] - '0' : 0;
            const int val2 = j >= 0 ? s2[j] - '0' : 0;
            const int sum = carry + val1 + val2;
            result.push_back('0' + sum % 10);
            carry = sum / 10;
            i--;
            j--;
        }
        if (carry > 0) {
            result.push_back(carry + '0');
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};
