#include <string>
#include <vector>

/**
 * You are given two strings word1 and word2.
 *
 * A string x is called almost equal to y if you can change at most one character in x to make it identical to y.
 *
 * A sequence of indices seq is called valid if:
 *
 * - The indices are sorted in ascending order.
 *
 * - Concatenating the characters at these indices in word1 in the same order results in a string that is almost equal
 * to word2.
 *
 * Return an array of size word2.length representing the lexicographically smallest valid sequence of indices. If no
 * such sequence of indices exists, return an empty array.
 *
 * Note that the answer must represent the lexicographically smallest array, not the corresponding string formed by
 * those indices.
 *
 * ! 1 <= word2.length < word1.length <= 3 * 10^5
 * ! word1 and word2 consist only of lowercase English letters.
 */

class Solution {
public:
    std::vector<int> validSequence(std::string& word1, std::string& word2)
    {
        const int m = word1.size();
        const int n = word2.size();
        std::vector<int> last(n, -1);
        for (int i = m - 1, j = n - 1; i >= 0; --i) {
            if (j < 0)
                break;

            if (word1[i] == word2[j]) {
                last[j--] = i;
            }
        }
        std::vector<int> result;
        result.reserve(n);
        for (int i = 0, j = 0, skip = 0; i < m; ++i) {
            if (j == n)
                break;

            if (word1[i] == word2[j] || (skip == 0 && (j == n - 1 || i < last[j + 1]))) {
                skip += word1[i] != word2[j];
                result.emplace_back(i);
                j++;
            }
        }
        return result.size() == n ? result : std::vector<int>{};
    }
};