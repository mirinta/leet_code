#include <array>
#include <string>
#include <vector>

/**
 * Given a string array words, return an array of all characters that show up in all strings within
 * the words (including duplicates). You may return the answer in any order.
 *
 * ! 1 <= words.length <= 100
 * ! 1 <= words[i].length <= 100
 * ! words[i] consists of lowercase English letters.
 */

class Solution {
public:
    std::vector<std::string> commonChars(std::vector<std::string>& words)
    {
        std::array<int, 26> count{};
        std::fill(count.begin(), count.end(), INT_MAX);
        for (const auto& word : words) {
            std::array<int, 26> arr{};
            for (const auto& c : word) {
                arr[c - 'a']++;
            }
            for (int i = 0; i < 26; ++i) {
                count[i] = std::min(count[i], arr[i]);
            }
        }
        std::vector<std::string> result;
        for (int i = 0; i < 26; ++i) {
            std::string s;
            s.push_back(i + 'a');
            result.insert(result.end(), count[i], s);
        }
        return result;
    }
};