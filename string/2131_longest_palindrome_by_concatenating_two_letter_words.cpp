#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given an array of strings words. Each element of words consists of two lowercase English
 * letters.
 *
 * Create the longest possible palindrome by selecting some elements from words and concatenating
 * them in any order. Each element can be selected at most once.
 *
 * Return the length of the longest palindrome that you can create. If it is impossible to create
 * any palindrome, return 0.
 *
 * A palindrome is a string that reads the same forward and backward.
 *
 * ! 1 <= words.length <= 10^5
 * ! words[i].length == 2
 * ! words[i] consists of lowercase English letters.
 */

class Solution {
public:
    int longestPalindrome(std::vector<std::string>& words)
    {
        std::unordered_map<int, int> map;
        int result = 0;
        for (const auto& s : words) {
            const int val = encode(s);
            const int target = getTarget(val);
            if (!map.count(target)) {
                map[val]++;
                continue;
            }
            result += 4;
            if (--map[target] == 0) {
                map.erase(target);
            }
        }
        for (const auto& [val, freq] : map) {
            const auto [first, second] = decode(val);
            if (first == second) {
                result += 2;
                break;
            }
        }
        return result;
    }

private:
    int encode(const std::string& s)
    {
        return (s[0] - 'a') * 100 + (s[1] - 'a');
    }

    std::pair<int, int> decode(int val)
    {
        return {val / 100, val % 100};
    }

    int getTarget(int val)
    {
        return val % 100 * 100 + val / 100;
    }
};