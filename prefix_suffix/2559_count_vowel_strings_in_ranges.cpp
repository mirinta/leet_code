#include <string>
#include <vector>

/**
 * You are given a 0-indexed array of strings words and a 2D array of integers queries.
 *
 * Each query queries[i] = [li, ri] asks us to find the number of strings present in the range li to
 * ri (both inclusive) of words that start and end with a vowel.
 *
 * Return an array ans of size queries.length, where ans[i] is the answer to the ith query.
 *
 * Note that the vowel letters are 'a', 'e', 'i', 'o', and 'u'.
 *
 * ! 1 <= words.length <= 10^5
 * ! 1 <= words[i].length <= 40
 * ! words[i] consists only of lowercase English letters.
 * ! sum(words[i].length) <= 3 * 10^5
 * ! 1 <= queries.length <= 10^5
 * ! 0 <= li <= ri < words.length
 */

class Solution {
public:
    std::vector<int> vowelStrings(std::vector<std::string>& words, std::vector<std::vector<int>>& queries)
    {
        const int n = words.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + isValid(words[i - 1]);
        }
        std::vector<int> result;
        result.reserve(queries.size());
        for (const auto& q : queries) {
            result.push_back(presum[q[1] + 1] - presum[q[0]]);
        }
        return result;
    }

private:
    bool isVowel(char c)
    {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }

    bool isValid(const std::string& s)
    {
        return isVowel(s.front()) && isVowel(s.back());
    }
};
