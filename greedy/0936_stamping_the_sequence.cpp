#include <string>
#include <vector>

/**
 * You are given two strings stamp and target. Initially, there is a string s of length
 * target.length with all s[i] == '?'.
 *
 * In one turn, you can place stamp over s and replace every letter in the s with the corresponding
 * letter from stamp.
 *
 * For example, if stamp = "abc" and target = "abcba", then s is "?????" initially. In one turn you
 * can:
 *
 * - place stamp at index 0 of s to obtain "abc??",
 *
 * - place stamp at index 1 of s to obtain "?abc?", or
 *
 * - place stamp at index 2 of s to obtain "??abc".
 *
 * Note that stamp must be fully contained in the boundaries of s in order to stamp (i.e., you
 * cannot place stamp at index 3 of s).
 *
 * We want to convert s to target using at most 10 * target.length turns.
 *
 * Return an array of the index of the left-most letter being stamped at each turn. If we cannot
 * obtain target from s within 10 * target.length turns, return an empty array.
 *
 * ! 1 <= stamp.length <= target.length <= 1000
 * ! stamp and target consist of lowercase English letters.
 */

class Solution {
public:
    std::vector<int> movesToStamp(std::string stamp, std::string target)
    {
        // try to restore target to "??...?"
        // if it is possible to do so,
        // consider the last operation,
        // there must be a substring of target equal to stamp
        const int n = stamp.size();
        const int m = target.size();
        int total = m; // num of characters of target need to be restored to '?'
        std::vector<int> result;
        while (total > 0) {
            int count = -1;
            for (int i = 0; i + n - 1 < m; ++i) {
                count = check(target, i, i + n - 1, stamp);
                if (count > 0) {
                    result.push_back(i);
                    target.replace(i, n, n, '?');
                    total -= count;
                    break;
                }
            }
            if (count <= 0)
                return {};
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

private:
    // check if s1[start:end] == s2, return the num of characters of s1 which are not '*'
    int check(const std::string& s1, int start, int end, const std::string& s2)
    {
        int count = 0;
        for (int i = start; i <= end; ++i) {
            if (s1[i] != '?' && s1[i] != s2[i - start])
                return 0;

            count += s1[i] != '?';
        }
        return count;
    }
};