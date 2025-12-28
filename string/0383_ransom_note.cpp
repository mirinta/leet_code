#include <string>
#include <unordered_map>

/**
 * Given two strings "ransomNote" and "magazine", return "true" if "ransomNote" can be constructed
 * by using the letters from "magazine" and "false" otherwise.
 *
 * Each letter in "magazine" can only be used once in "ransomNote".
 *
 * ! 1 <= ransomNote.length, magazine.length <= 10^5
 * ! ransomNote and magazine consist of lowercase English letters.
 */

class Solution {
public:
    bool canConstruct(std::string ransomNote, std::string magazine)
    {
        std::unordered_map<char, int> freq;
        for (const auto& c : magazine) {
            freq[c]++;
        }
        for (const auto& c : ransomNote) {
            if (!freq.count(c) || --freq[c] < 0)
                return false;
        }
        return true;
    }
};
