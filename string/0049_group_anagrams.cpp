#include <algorithm>
#include <array>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * Given an array of strings "strs", group the anagrams together. You can return the answer in any
 * order.
 *
 * An anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
 * typically using all the original letters exactly once.
 *
 * ! 1 <= strs.length <= 10^4
 * ! 0 <= strs[i].length <= 100
 * ! strs[i] consists of lowercase English letters.
 */

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs)
    {
        std::unordered_map<std::string, std::vector<std::string>> map;
        for (const auto& s : strs) {
            std::string key(s);
            std::sort(key.begin(), key.end());
            map[key].push_back(s);
        }
        std::vector<std::vector<std::string>> result;
        for (const auto& [key, group] : map) {
            result.push_back(group);
        }
        return result;
    }
};
