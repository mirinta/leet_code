#include <string>

/**
 * There are n balls on a table, each ball has a color black or white.
 *
 * You are given a 0-indexed binary string s of length n, where 1 and 0 represent black and white
 * balls, respectively.
 *
 * In each step, you can choose two adjacent balls and swap them.
 *
 * Return the minimum number of steps to group all the black balls to the right and all the white
 * balls to the left.
 *
 * ! 1 <= n == s.length <= 10^5
 * ! s[i] is either '0' or '1'.
 */

class Solution {
public:
    long long minimumSteps(std::string s)
    {
        return approach2(s);
    }

private:
    long long approach2(const std::string& s)
    {
        int ones = 0;
        long long result = 0;
        for (const auto& c : s) {
            if (c == '1') {
                ones++;
            } else {
                result += ones;
            }
        }
        return result;
    }

    long long approach1(const std::string& s)
    {
        const int n = s.size();
        int i = 0;
        int j = n - 1;
        long long result = 0;
        while (i < j) {
            while (i < j && s[i] == '0') {
                i++;
            }
            while (i < j && s[j] == '1') {
                j--;
            }
            result += j - i;
            i++;
            j--;
        }
        return result;
    }
};