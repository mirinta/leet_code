#include <string>
#include <vector>

/**
 * You are given a binary string s. You are allowed to perform two types of operations on the string in any sequence:
 *
 * - Type-1: Remove the character at the start of the string s and append it to the end of the string.
 *
 * - Type-2: Pick any character in s and flip its value, i.e., if its value is '0' it becomes '1' and vice-versa.
 *
 * Return the minimum number of type-2 operations you need to perform such that s becomes alternating.
 *
 * The string is called alternating if no two adjacent characters are equal.
 *
 * For example, the strings "010" and "1010" are alternating, while the string "0100" is not.
 *
 * ! 1 <= s.length <= 10^5
 * ! s[i] is either '0' or '1'.
 */

class Solution {
public:
    int minFlips(std::string& s)
    {
        return approach2(s);
    }

private:
    int approach2(const std::string& s)
    {
        const int n = s.size();
        int result = INT_MAX;
        // count = num of type-2 operations to make s become 010101...
        for (int i = 0, count = 0; i < 2 * n - 1; ++i) {
            if (i >= n) {
                count = n - count;
                count -= s[i - n] != '1';
                count += s[i % n] != (1 - n % 2 + '0');
            } else {
                count += s[i] != (i % 2 + '0');
            }
            if (i >= n - 1) {
                result = std::min({result, count, n - count});
            }
        }
        return result;
    }

    int approach1(const std::string& s)
    {
        // let x = num of type-2 operations to make s become 010101...
        // and y = num of type-2 operations to make s become 101010...
        // then x + y = n
        //
        // prefix[i] = num of type-2 operations to make s[0:i] become 010101...
        // suffix[i] = num of type-2 operations to make s[i:n-1] become 010101...
        const int n = s.size();
        std::vector<int> prefix(n, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i] = s[i] != (i % 2 + '0');
            if (i > 0) {
                prefix[i] += prefix[i - 1];
            }
        }
        std::vector<int> suffix(n, 0);
        for (int i = n - 1; i >= 0; --i) {
            suffix[i] = s[i] != '0';
            if (i + 1 < n) {
                suffix[i] += n - i - 1 - suffix[i + 1];
            }
        }
        int result = std::min(prefix.back(), n - prefix.back());
        for (int i = 0; i + 1 < n; ++i) {
            // count = num of type-2 operations to make s[i+1:n-1] + s[0:i] become 010101...
            int count = suffix[i + 1];
            if ((n - i - 1) % 2) {
                // the last character of s[i+1:n-1] is '0'
                // we need to make s[0:i] become 101010...
                count += i + 1 - prefix[i];
            } else {
                // the last character of s[i+1:n-1] is '1'
                // we need to make s[0:i] become 010101...
                count += prefix[i];
            }
            result = std::min({result, count, n - count});
        }
        return result;
    }
};