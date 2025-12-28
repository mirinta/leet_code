#include <algorithm>
#include <array>
#include <string>
#include <unordered_map>

/**
 * You are given two strings order and s. All the characters of order are unique and were sorted in
 * some custom order previously.
 *
 * Permute the characters of s so that they match the order that order was sorted. More
 * specifically, if a character x occurs before a character y in order, then x should occur before y
 * in the permuted string.
 *
 * Return any permutation of s that satisfies this property.
 *
 * ! 1 <= order.length <= 26
 * ! 1 <= s.length <= 200
 * ! order and s consist of lowercase English letters.
 * ! All the characters of order are unique.
 */

class Solution {
public:
    std::string customSortString(std::string order, std::string s)
    {
        return approach2(order, s);
    }

private:
    std::string approach2(const std::string& order, const std::string& s)
    {
        std::array<int, 26> count{};
        for (const auto& c : s) {
            count[c - 'a']++;
        }
        std::string result;
        result.reserve(s.size());
        for (const auto& c : order) {
            if (count[c - 'a'] == 0)
                continue;

            result.append(count[c - 'a'], c);
            count[c - 'a'] = 0;
        }
        for (int i = 0; i < 26; ++i) {
            if (count[i] > 0) {
                result.append(count[i], 'a' + i);
            }
        }
        return result;
    }

    std::string approach1(const std::string& order, std::string& s)
    {
        std::unordered_map<char, int> map;
        for (int i = 0; i < order.size(); ++i) {
            map[order[i]] = i;
        }
        std::sort(s.begin(), s.end(), [&map](const auto& c1, const auto& c2) -> bool {
            if (map.count(c1) && map.count(c2))
                return map[c1] < map[c2];

            return map.count(c1);
        });
        return s;
    }
};