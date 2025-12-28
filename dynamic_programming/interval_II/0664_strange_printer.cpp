#include <string>
#include <vector>

/**
 * There is a strange printer with the following two special properties:
 *
 * - The printer can only print a sequence of the same character each time.
 *
 * - At each turn, the printer can print new characters starting from and ending at any place and
 * will cover the original existing characters.
 *
 * Given a string s, return the minimum number of turns the printer needed to print it.
 *
 * ! 1 <= s.length <= 100
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    int strangePrinter(std::string s)
    {
        const auto simplified = process(s);
        const int n = simplified.size();
        std::vector<std::vector<int>> memo(n, std::vector<int>(n, -1));
        return dfs(memo, 0, n - 1, simplified);
    }

private:
    // remove consecutive duplicates, e.g. aaabbb -> ab
    std::string process(const std::string& s)
    {
        const int n = s.size();
        std::string result;
        int i = 0;
        while (i < n) {
            if (result.empty() || s[i] != result.back()) {
                result.push_back(s[i]);
            }
            i++;
        }
        return result;
    }

    // min num of operations to print s[lo:hi]
    int dfs(std::vector<std::vector<int>>& memo, int lo, int hi, const std::string& s)
    {
        if (lo > hi)
            return 0;

        if (memo[lo][hi] != -1)
            return memo[lo][hi];

        // case 1: print one s[lo]
        // lo X X X ... X X hi
        //    |<-next round->|
        int result = 1 + dfs(memo, lo + 1, hi, s);
        for (int k = lo + 1; k <= hi; ++k) {
            if (s[lo] != s[k])
                continue;

            // case 2: print a sequence of s[lo]
            // if s[lo] = s[k], then let s[lo:k] = s[lo]
            // lo X X X ... k-1 k k+1 ... X X X hi
            // |<-next round->|   |<-next round->|
            result = std::min(result, dfs(memo, lo, k - 1, s) + dfs(memo, k + 1, hi, s));
        }
        return memo[lo][hi] = result;
    }
};
