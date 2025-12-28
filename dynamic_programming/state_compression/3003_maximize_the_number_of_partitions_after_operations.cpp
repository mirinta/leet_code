#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed string s and an integer k.
 *
 * You are to perform the following partitioning operations until s is empty:
 *
 * - Choose the longest prefix of s containing at most k distinct characters.
 *
 * - Delete the prefix from s and increase the number of partitions by one. The remaining characters
 * (if any) in s maintain their initial order.
 *
 * Before the operations, you are allowed to change at most one index in s to another lowercase
 * English letter.
 *
 * Return an integer denoting the maximum number of resulting partitions after the operations by
 * optimally choosing at most one index to change.
 *
 * ! 1 <= s.length <= 10^4
 * ! s consists only of lowercase English letters.
 * ! 1 <= k <= 26
 */

class Solution {
public:
    int maxPartitionsAfterOperations(std::string s, int k)
    {
        return dp(0, 0, k, s);
    }

private:
    std::unordered_map<int, std::unordered_map<int, int>> memo;

    // combined state: X Y Y Y Y Y Y ... Y
    //                   |<--26 letters->|
    // X = changed or not
    int dp(int i, int state, int k, const std::string& s)
    {
        if (i == s.size())
            return 1;

        if (memo.count(i) && memo[i].count(state))
            return memo[i][state];

        const int curr = s[i] - 'a';
        const int letters = state & ((1 << 26) - 1);
        const int changed = (state >> 26) & 1 ? 1 : 0;
        int result = 0;
        // case1: we do not change the current letter
        if (numOfBinaryOnes(letters | (1 << curr)) > k) {
            result = std::max(result, 1 + dp(i + 1, (changed << 26) | (1 << curr), k, s));
        } else {
            result = std::max(result, dp(i + 1, (changed << 26) | letters | (1 << curr), k, s));
        }
        // case2: we change the current letter (if no letter is changed)
        for (int j = 0; !changed && j < 26; ++j) {
            if (j == curr)
                continue;

            if (numOfBinaryOnes(letters | (1 << j)) > k) {
                result = std::max(result, 1 + dp(i + 1, (1 << 26) | (1 << j), k, s));
            } else {
                result = std::max(result, dp(i + 1, (1 << 26) | letters | (1 << j), k, s));
            }
        }
        return memo[i][state] = result;
    }

    int numOfBinaryOnes(int n)
    {
        int result = 0;
        while (n) {
            result++;
            n &= n - 1;
        }
        return result;
    }
};