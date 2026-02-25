#include <string>

/**
 * You are given two binary strings s and t​​​​​​​, each of length n.
 *
 * You may rearrange the characters of t in any order, but s must remain unchanged.
 *
 * Return a binary string of length n representing the maximum integer value obtainable by taking the bitwise XOR of s
 * and rearranged t.
 *
 * ! 1 <= n == s.length == t.length <= 2 * 10^5
 * ! s[i] and t[i] are either '0' or '1'.
 */

class Solution {
public:
    std::string maximumXor(std::string& s, std::string& t)
    {
        const int n = s.size();
        int count0 = 0;
        int count1 = 0;
        for (const auto& c : t) {
            if (c == '0') {
                count0++;
            } else {
                count1++;
            }
        }
        std::string result;
        result.reserve(n);
        for (const auto& c : s) {
            const bool case1 = c == '0' && --count1 >= 0;
            const bool case2 = c == '1' && --count0 >= 0;
            if (case1 || case2) {
                result.push_back('1');
            } else {
                result.push_back('0');
            }
        }
        return result;
    }
};