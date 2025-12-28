#include <array>
#include <string>
#include <vector>

/**
 * You are given a string s, which is known to be a concatenation of anagrams of some string t.
 *
 * Return the minimum possible length of the string t.
 *
 * An anagram is formed by rearranging the letters of a string. For example, "aab", "aba", and,
 * "baa" are anagrams of "aab".
 *
 * ! 1 <= s.length <= 10^5
 * ! s consist only of lowercase English letters.
 */

class Solution {
public:
    int minAnagramLength(std::string s)
    {
        const int n = s.size();
        std::vector<std::array<int, 26>> count(n + 1);
        for (int i = 1; i <= n; ++i) {
            count[i] = count[i - 1];
            count[i][s[i - 1] - 'a']++;
        }
        for (int i = 1; i < n; ++i) {
            if (isValid(i, s, count))
                return i;
        }
        return n;
    }

private:
    std::array<int, 26> query(int left, int right, const std::vector<std::array<int, 26>>& count)
    {
        std::array<int, 26> result{};
        for (int i = 0; i < 26; ++i) {
            result[i] = count[right + 1][i] - count[left][i];
        }
        return result;
    }

    bool isValid(int k, const std::string& s, const std::vector<std::array<int, 26>>& count)
    {
        const int n = s.size();
        if (n % k != 0)
            return false;

        const auto target = query(0, k - 1, count);
        for (int i = k; i + k - 1 < n; i += k) {
            if (query(i, i + k - 1, count) != target)
                return false;
        }
        return true;
    }
};