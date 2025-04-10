#include <cmath>
#include <string>

/**
 * You are given three integers start, finish, and limit. You are also given a 0-indexed string s
 * representing a positive integer.
 *
 * A positive integer x is called powerful if it ends with s (in other words, s is a suffix of x)
 * and each digit in x is at most limit.
 *
 * Return the total number of powerful integers in the range [start..finish].
 *
 * A string x is a suffix of a string y if and only if x is a substring of y that starts from some
 * index (including 0) in y and extends to the index y.length - 1. For example, 25 is a suffix of
 * 5125 whereas 512 is not.
 *
 * ! 1 <= start <= finish <= 10^15
 * ! 1 <= limit <= 9
 * ! 1 <= s.length <= floor(log10(finish)) + 1
 * ! s only consists of numeric digits which are at most limit.
 * ! s does not have leading zeros.
 */

class Solution
{
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, std::string s)
    {
        return helper(std::to_string(finish), limit, s) -
               helper(std::to_string(start - 1), limit, s);
    }

private:
    // total num of valid integers in the range [1:finish] and the suffix of each integer is s
    long long helper(const std::string& finish, int limit, const std::string& suffix)
    {
        return dfs(0, true, finish, limit, suffix);
    }

    long long dfs(int i, bool isPrefixSame, const std::string& finish, int limit,
                  const std::string& suffix)
    {
        // s = 0 X X X X i-1 i X X X X j X X X X n-1
        //     |<--prefix->|           |<--suffix->|
        //
        // case 1: s.prefix != finish.prefix
        // each digit of s[i] and the remaining digits can be [0:limit],
        // i.e., num of valid integers = (limit+1)^(j-i)
        //
        // case 2: s.prefix == finish.prefix
        // s[i] can be [0:min(limit, finish[i])]
        // the remaining digits can not be determined
        const int n = finish.size();
        const int suffixLength = suffix.size();
        if (n < suffixLength)
            return 0;

        if (i == n - suffixLength) {
            if (isPrefixSame && std::stoll(finish.substr(i, suffixLength)) < std::stoll(suffix))
                return 0;

            return 1; // s[i:n-1] must be equal to suffix, only one choice
        }
        if (!isPrefixSame)
            return std::pow(limit + 1, n - i - suffixLength);

        long long result = 0;
        for (int d = 0; d <= std::min(limit, finish[i] - '0'); ++d) {
            result += dfs(i + 1, d == finish[i] - '0', finish, limit, suffix);
        }
        return result;
    }
};
