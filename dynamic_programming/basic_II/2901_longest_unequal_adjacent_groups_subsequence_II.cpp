#include <algorithm>
#include <string>
#include <vector>

/**
 * You are given an integer n, a 0-indexed string array words, and a 0-indexed array groups, both
 * arrays having length n.
 *
 * The hamming distance between two strings of equal length is the number of positions at which the
 * corresponding characters are different.
 *
 * You need to select the longest subsequence from an array of indices [0, 1, ..., n - 1], such that
 * for the subsequence denoted as [i0, i1, ..., ik - 1] having length k, the following holds:
 *
 * - For adjacent indices in the subsequence, their corresponding groups are unequal, i.e.,
 * groups[ij] != groups[ij + 1], for each j where 0 < j + 1 < k.
 *
 * - words[ij] and words[ij + 1] are equal in length, and the hamming distance between them is 1,
 * where 0 < j + 1 < k, for all indices in the subsequence.
 *
 * Return a string array containing the words corresponding to the indices (in
 * order) in the selected subsequence. If there are multiple answers, return any of them.
 *
 * A subsequence of an array is a new array that is formed from the original array by deleting some
 * (possibly none) of the elements without disturbing the relative positions of the remaining
 * elements.
 *
 * Note: strings in words may be unequal in length.
 *
 * ! 1 <= n == words.length == groups.length <= 1000
 * ! 1 <= words[i].length <= 10
 * ! 1 <= groups[i] <= n
 * ! words consists of distinct strings.
 * ! words[i] consists of lowercase English letters.
 */

class Solution
{
public:
    std::vector<std::string> getWordsInLongestSubsequence(std::vector<std::string>& words,
                                                          std::vector<int>& groups)
    {
        // dp[i] = length of the longest valid subsequence of words[0:i] ending at words[i]
        const int n = words.size();
        std::vector<int> dp(n, 1);
        auto isValid = [&](int i, int j) {
            if (groups[i] == groups[j] || words[i].size() != words[j].size())
                return false;

            int count = 0;
            for (int k = 0; k < words[i].size(); ++k) {
                count += words[i][k] != words[j][k];
                if (count > 1)
                    return false;
            }
            return count == 1;
        };
        int maxLength = 0;
        int maxIndex = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (isValid(i, j)) {
                    dp[i] = std::max(dp[i], 1 + dp[j]);
                }
            }
            if (dp[i] > maxLength) {
                maxLength = dp[i];
                maxIndex = i;
            }
        }
        std::vector<std::string> result;
        while (maxIndex >= 0) {
            result.push_back(words[maxIndex]);
            int j = maxIndex - 1;
            while (j >= 0 && (!isValid(j, maxIndex) || dp[j] + 1 != dp[maxIndex])) {
                j--;
            }
            if (j < 0)
                break;

            maxIndex = j;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};
