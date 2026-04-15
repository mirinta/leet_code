#include <string>
#include <vector>

/**
 * You are given a 0-indexed circular string array words and a string target. A circular array means that the array's
 * end connects to the array's beginning.
 *
 * Formally, the next element of words[i] is words[(i + 1) % n] and the previous element of words[i] is words[(i - 1 +
 * n) % n], where n is the length of words.
 *
 * Starting from startIndex, you can move to either the next word or the previous word with 1 step at a time.
 *
 * Return the shortest distance needed to reach the string target. If the string target does not exist in words, return
 * -1.
 *
 * ! 1 <= words.length <= 100
 * ! 1 <= words[i].length <= 100
 * ! words[i] and target consist of only lowercase English letters.
 * ! 0 <= startIndex < words.length
 */

class Solution {
public:
    int closestTarget(std::vector<std::string>& words, std::string& target, int startIndex)
    {
        const int n = words.size();
        int result = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (words[i] != target)
                continue;

            const int dist = std::abs(i - startIndex);
            result = std::min({result, dist, n - dist});
        }
        return result == INT_MAX ? -1 : result;
    }
};