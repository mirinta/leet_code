#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * Given an array of strings strs, return the length of the longest uncommon subsequence between
 * them. If the longest uncommon subsequence does not exist, return -1.
 *
 * An uncommon subsequence between an array of strings is a string that is a subsequence of one
 * string but not the others.
 *
 * A subsequence of a string s is a string that can be obtained after deleting any number of
 * characters from s.
 *
 * - For example, "abc" is a subsequence of "aebdc" because you can delete the underlined characters
 * in "aebdc" to get "abc". Other subsequences of "aebdc" include "aebdc", "aeb", and "" (empty
 * string).
 *
 * ! 2 <= strs.length <= 50
 * ! 1 <= strs[i].length <= 10
 * ! strs[i] consists of lowercase English letters.
 */

class Solution {
public:
    int findLUSlength(std::vector<std::string>& strs)
    {
        std::unordered_map<std::string, int> map;
        for (const auto& s : strs) {
            map[s]++;
        }
        std::vector<std::string> unique;
        unique.reserve(map.size());
        for (const auto& [s, freq] : map) {
            unique.push_back(s);
        }
        std::sort(unique.begin(), unique.end(), [](const auto& s1, const auto& s2) { return s1.size() > s2.size(); });
        const int n = unique.size();
        for (int i = 0; i < n; ++i) {
            if (map[unique[i]] > 1)
                continue;

            const bool check = std::none_of(unique.begin(), unique.begin() + i,
                                            [&](const auto& s) { return isSubsequence(s, unique[i]); });
            if (check)
                return unique[i].size();
        }
        return -1;
    }

private:
    bool isSubsequence(const std::string& s, const std::string& sub)
    {
        int j = 0;
        for (int i = 0; i < s.size() && j < sub.size(); ++i) {
            if (s[i] == sub[j]) {
                j++;
            }
            if (j == sub.size())
                return true;
        }
        return false;
    }
};