#include <algorithm>
#include <string>
#include <unordered_map>

/**
 * You are given a string s of length n containing only four kinds of characters: 'Q', 'W', 'E', and
 * 'R'.
 *
 * A string is said to be balanced if each of its characters appears n / 4 times where n is the
 * length of the string.
 *
 * Return the minimum length of the substring that can be replaced with any other string of the same
 * length to make s balanced. If s is already balanced, return 0.
 *
 * ! n == s.length
 * ! 4 <= n <= 10^5
 * ! n is a multiple of 4.
 * ! s contains only 'Q', 'W', 'E', and 'R'.
 */

class Solution {
public:
    int balancedString(std::string s)
    {
        // if s[j:i] can be replaced to make s balanced,
        // then the remaining frequencies of Q/W/E/R must be <= n/4
        const int n = s.size();
        std::unordered_map<char, int> map;
        for (const auto& c : s) {
            map[c]++;
        }
        if (std::all_of(map.begin(), map.end(), [&](const auto& p) { return p.second == n / 4; }))
            return 0;

        auto predicate = [&](const auto& p) { return p.second <= n / 4; };
        int result = INT_MAX;
        for (int left = 0, right = 0; right < n; ++right) {
            map[s[right]]--;
            while (std::all_of(map.begin(), map.end(), predicate)) {
                map[s[left]]++;
                result = std::min(result, right - left + 1);
                left++;
            }
        }
        return result;
    }
};