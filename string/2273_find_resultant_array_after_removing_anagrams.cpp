#include <array>
#include <numeric>
#include <string>
#include <vector>

/**
 * You are given a 0-indexed string array words, where words[i] consists of lowercase English
 * letters.
 *
 * In one operation, select any index i such that 0 < i < words.length and words[i - 1] and words[i]
 * are anagrams, and delete words[i] from words. Keep performing this operation as long as you can
 * select an index that satisfies the conditions.
 *
 * Return words after performing all operations. It can be shown that selecting the indices for each
 * operation in any arbitrary order will lead to the same result.
 *
 * An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase
 * using all the original letters exactly once. For example, "dacb" is an anagram of "abdc".
 *
 * ! 1 <= words.length <= 100
 * ! 1 <= words[i].length <= 10
 * ! words[i] consists of lowercase English letters.
 */

class Solution
{
public:
    std::vector<std::string> removeAnagrams(std::vector<std::string>& words)
    {
        const int n = words.size();
        std::vector<std::string> result;
        int i = 0;
        while (i < n) {
            int j = i + 1;
            while (j < n && isAnagram(words[i], words[j])) {
                j++;
            }
            result.push_back(words[i]);
            i = j;
        }
        return result;
    }

private:
    bool isAnagram(const std::string& s1, const std::string& s2)
    {
        if (s1.size() != s2.size())
            return false;

        std::array<int, 26> count{};
        for (const auto& c : s1) {
            count[c - 'a']++;
        }
        for (const auto& c : s2) {
            if (--count[c - 'a'] < 0)
                return false;
        }
        return std::accumulate(count.begin(), count.end(), 0) == 0;
    }
};
