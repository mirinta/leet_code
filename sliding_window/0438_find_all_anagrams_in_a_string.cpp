#include <array>
#include <string>
#include <vector>

/**
 * Given two string "s" and "p", return an array of all the start indicies of "p"'s anagrams in "s".
 * You may return the answer in any order.
 *
 * An anagram is a word or phase formed by rearranging the letters of a different word or phase,
 * typically using all the original letters exactly once.
 *
 * ! 1 <= s.length, p.length <= 3 * 10^4
 * ! s and p consist of lowercase English letters.
 */

class Solution {
public:
    std::vector<int> findAnagrams(std::string s, std::string p)
    {
        const int n = p.size();
        const int m = s.size();
        std::array<int, 26> target{};
        for (const auto& c : p) {
            target[c - 'a']++;
        }
        std::array<int, 26> count{};
        std::vector<int> result;
        for (int left = 0, right = 0; right < m; ++right) {
            count[s[right] - 'a']++;
            if (right - left + 1 > n) {
                count[s[left] - 'a']--;
                left++;
            }
            if (right - left + 1 == n && count == target) {
                result.push_back(left);
            }
        }
        return result;
    }
};
