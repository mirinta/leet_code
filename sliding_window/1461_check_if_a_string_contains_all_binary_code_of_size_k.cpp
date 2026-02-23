#include <string>
#include <unordered_set>

/**
 * Given a binary string s and an integer k, return true if every binary code of length k is a substring of s.
 * Otherwise, return false.
 *
 * ! 1 <= s.length <= 5 * 10^5
 * ! s[i] is either '0' or '1'.
 * ! 1 <= k <= 20
 */

class Solution {
public:
    bool hasAllCodes(std::string& s, int k)
    {
        const int n = s.size();
        const int target = 1 << k;
        if (n - k + 1 < target)
            return false;

        std::unordered_set<int> set;
        for (int i = 0, code = 0; i < n; ++i) {
            code = 2 * code + (s[i] - '0');
            if (i >= k) {
                code -= (s[i - k] - '0') * (1 << k);
            }
            if (i >= k - 1) {
                set.insert(code);
            }
            if (set.size() == target)
                return true;
        }
        return false;
    }
};