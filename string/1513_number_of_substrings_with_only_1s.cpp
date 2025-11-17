#include <string>

/**
 * Given a binary string s, return the number of substrings with all characters 1's. Since the
 * answer may be too large, return it modulo 10^9 + 7.
 *
 * ! 1 <= s.length <= 10^5
 * ! s[i] is either '0' or '1'.
 */

class Solution
{
public:
    int numSub(std::string s)
    {
        static constexpr int kMod = 1e9 + 7;
        const int n = s.size();
        int result = 0;
        for (int i = 0, count = 0; i < n; ++i) {
            if (s[i] == '0') {
                count = 0;
            } else {
                count += 1;
            }
            result = (result + count) % kMod;
        }
        return result;
    }
};
