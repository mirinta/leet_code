#include <array>
#include <string>
#include <vector>

/**
 * You are given two string arrays words1 and words2.
 *
 * A string b is a subset of string a if every letter in b occurs in a including multiplicity.
 *
 * - For example, "wrr" is a subset of "warrior" but is not a subset of "world".
 * A string a from words1 is universal if for every string b in words2, b is a subset of a.
 *
 * Return an array of all the universal strings in words1. You may return the answer in any order.
 *
 * ! 1 <= words1.length, words2.length <= 104
 * ! 1 <= words1[i].length, words2[i].length <= 10
 * ! words1[i] and words2[i] consist only of lowercase English letters.
 * ! All the strings of words1 are unique.
 */

class Solution {
public:
    std::vector<std::string> wordSubsets(std::vector<std::string>& words1, std::vector<std::string>& words2)
    {
        std::array<int, 26> target{};
        for (const auto& s : words2) {
            const auto freq = getFreq(s);
            for (int i = 0; i < 26; ++i) {
                target[i] = std::max(target[i], freq[i]);
            }
        }
        std::vector<std::string> result;
        for (const auto& s : words1) {
            if (isValid(s, target)) {
                result.push_back(s);
            }
        }
        return result;
    }

private:
    std::array<int, 26> getFreq(const std::string& s)
    {
        std::array<int, 26> result{};
        for (const auto& c : s) {
            result[c - 'a']++;
        }
        return result;
    }

    bool isValid(const std::string& s, const std::array<int, 26>& target)
    {
        const auto freq = getFreq(s);
        for (int i = 0; i < 26; ++i) {
            if (freq[i] < target[i])
                return false;
        }
        return true;
    }
};
