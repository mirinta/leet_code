#include <string>

/**
 * Given a binary string s ​​​​​without leading zeros, return true​​​ if s contains at most one
 * contiguous segment of ones. Otherwise, return false.
 *
 * ! 1 <= s.length <= 100
 * ! s[i]​​​​ is either '0' or '1'.
 * ! s[0] is '1'.
 */

class Solution {
public:
    bool checkOnesSegment(std::string& s)
    {
        // s has no leading zeros
        // if s is valid,
        // then '1' must not be found
        const int n = s.size();
        for (int i = 0; i + 1 < n; ++i) {
            if (s[i] == '0' && s[i + 1] == '1')
                return false;
        }
        return true;
    }
};
