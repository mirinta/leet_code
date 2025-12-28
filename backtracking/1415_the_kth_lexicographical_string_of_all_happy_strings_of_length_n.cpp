#include <functional>
#include <string>

/**
 * A happy string is a string that:
 *
 * - consists only of letters of the set ['a', 'b', 'c'].
 *
 * - s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is 1-indexed).
 *
 * For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy strings and strings "aa",
 * "baa" and "ababbc" are not happy strings.
 *
 * Given two integers n and k, consider a list of all happy strings of length n sorted in
 * lexicographical order.
 *
 * Return the kth string of this list or return an empty string if there are less than k happy
 * strings of length n.
 *
 * ! 1 <= n <= 10
 * ! 1 <= k <= 100
 */

class Solution {
public:
    std::string getHappyString(int n, int k)
    {
        int count = 0;
        std::string s;
        std::string result;
        std::function<bool(int)> backtrack = [&](int i) {
            if (i == n) {
                if (++count == k) {
                    result = s;
                    return true;
                }
                return false;
            }
            for (char c = 'a'; c <= 'c'; ++c) {
                if (!s.empty() && c == s.back())
                    continue;

                s.push_back(c);
                if (backtrack(i + 1))
                    return true;

                s.pop_back();
            }
            return false;
        };
        backtrack(0);
        return result;
    }
};
