#include <array>
#include <string>
#include <vector>

/**
 * Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
 *
 * In other words, return true if one of s1's permutations is the substring of s2.
 *
 * ! 1 <= s1.length, s2.length <= 10^4
 * ! s1 and s2 consist of lowercase English letters.
 */

class Solution {
public:
    bool checkInclusion(std::string s1, std::string s2)
    {
        return approach1(s1, s2);
    }

private:
    // sliding window
    bool approach1(const std::string& s1, const std::string& s2)
    {
        const int n = s1.size();
        std::array<int, 26> target{};
        for (const auto& c : s1) {
            target[c - 'a']++;
        }
        std::array<int, 26> count{};
        for (int left = 0, right = 0; right < s2.size(); ++right) {
            count[s2[right] - 'a']++;
            if (right - left + 1 > n) {
                count[s2[left] - 'a']--;
                left++;
            }
            if (right - left + 1 == n && target == count)
                return true;
        }
        return false;
    }

    // fixed size sliding window + prefix sum
    bool approach2(const std::string& s1, const std::string& s2)
    {
        const int n = s1.size();
        std::array<int, 26> target{};
        for (const auto& c : s1) {
            target[c - 'a']++;
        }
        const int m = s2.size();
        std::vector<std::array<int, 26>> count(m + 1);
        for (int i = 1; i <= m; ++i) {
            count[i] = count[i - 1];
            count[i][s2[i - 1] - 'a']++;
        }
        auto query = [&count](int l, int r) {
            std::array<int, 26> result{};
            for (int i = 0; i < 26; ++i) {
                result[i] = count[r + 1][i] - count[l][i];
            }
            return result;
        };
        for (int i = 0; i + n - 1 < m; ++i) {
            if (query(i, i + n - 1) == target)
                return true;
        }
        return false;
    }
};