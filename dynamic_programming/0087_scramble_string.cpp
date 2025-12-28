#include <array>
#include <functional>
#include <string>
#include <vector>

/**
 * We can scramble a string s to get a string t using the following algorithm:
 *
 * 1. If the length of the string is 1, stop.
 *
 * 2. If the length of the string is > 1, do the following:
 *
 * - Split the string into two non-empty substrings at a random index, i.e., if the string is s,
 * divide it to x and y where s = x + y.
 *
 * - Randomly decide to swap the two substrings or to keep them in the same order. i.e., after this
 * step, s may become s = x + y or s = y + x.
 *
 * - Apply step 1 recursively on each of the two substrings x and y.
 *
 * Given two strings s1 and s2 of the same length, return true if s2 is a scrambled string of s1,
 * otherwise, return false.
 *
 * ! s1.length == s2.length
 * ! 1 <= s1.length <= 30
 * ! s1 and s2 consist of lowercase English letters.
 */

class Solution {
public:
    bool isScramble(std::string s1, std::string s2)
    {
        const int n = s1.size();
        std::vector<std::array<int, 26>> count1(n + 1);
        std::vector<std::array<int, 26>> count2(n + 1);
        for (int i = 1; i <= n; ++i) {
            count1[i] = count1[i - 1];
            count1[i][s1[i - 1] - 'a']++;
            count2[i] = count2[i - 1];
            count2[i][s2[i - 1] - 'a']++;
        }
        std::vector<std::vector<std::vector<int>>> memo(n,
                                                        std::vector<std::vector<int>>(n, std::vector<int>(n + 1, -1)));
        // check if s2[j:j+L-1] is a scramble string of s1[i:i+L-1]
        std::function<bool(int, int, int)> dfs = [&](int i, int j, int L) -> bool {
            if (L == 1)
                return s1[i] == s2[j];

            if (memo[i][j][L] != -1)
                return memo[i][j][L];

            if (isSame(i, j, L, s1, s2))
                return true;

            if (!isAnagram(i, j, L, count1, count2))
                return false;

            // s2: j X X X X X X X X X X X X j+length-1
            // s1: i X X X X X X X X X X X X i+length-1
            //     |<-left length->| |<-right length->|
            //     |<---------------L---------------->|
            for (int left = 1; left < L; ++left) {
                // case 1: isScramble(s1.left, s2.left) && isScramble(s1.right, s2.right)
                if (dfs(i, j, left) && dfs(i + left, j + left, L - left))
                    return memo[i][j][L] = true;

                // case 2: isScramble(s1.left, s2.right) && isScramble(s1.right, s2.left)
                if (dfs(i, j + L - left, left) && dfs(i + left, j, L - left))
                    return memo[i][j][L] = true;
            }
            return memo[i][j][L] = false;
        };
        return dfs(0, 0, n);
    }

private:
    bool isSame(int i, int j, int L, const std::string& s1, const std::string& s2)
    {
        for (int k = 0; k < L; ++k) {
            if (s1[i + k] != s2[j + k])
                return false;
        }
        return true;
    }

    bool isAnagram(int i,
                   int j,
                   int L,
                   const std::vector<std::array<int, 26>>& count1,
                   const std::vector<std::array<int, 26>>& count2)
    {
        for (int k = 0; k < 26; ++k) {
            if (count1[i + L][k] - count1[i][k] != count2[j + L][k] - count2[j][k])
                return false;
        }
        return true;
    }
};