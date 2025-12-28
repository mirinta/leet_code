#include <string>
#include <unordered_map>
#include <vector>

/**
 * We can shift a string by shifting each of its letters to its successive letter.
 *
 * - For example, "abc" can be shifted to be "bcd".
 *
 * We can keep shifting the string to form a sequence.
 *
 * - For example, we can keep shifting "abc" to form the sequence: "abc" -> "bcd" -> ... -> "xyz".
 *
 * Given an array of strings strings, group all strings[i] that belong to the same shifting
 * sequence. You may return the answer in any order.
 *
 * ! 1 <= strings.length <= 200
 * ! 1 <= strings[i].length <= 50
 * ! strings[i] consists of lowercase English letters.
 */

class Solution {
public:
    std::vector<std::vector<std::string>> groupStrings(std::vector<std::string>& strings)
    {
        std::unordered_map<std::string, std::vector<std::string>> map;
        for (const auto& s : strings) {
            std::string key(s);
            key[0] = 'a';
            const int shift = key[0] - s[0];
            for (int i = 1; i < key.size(); ++i) {
                key[i] = (shift + s[i] + 26) % 26 + 'a';
            }
            map[key].push_back(s);
        }
        std::vector<std::vector<std::string>> result;
        for (const auto& [key, group] : map) {
            result.push_back(group);
        }
        return result;
    }
};