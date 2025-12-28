#include <string>
#include <vector>

/**
 * Given a string "s", partition "s" such that every substring of the partition is a palindrome.
 * Return all possible palindrome partitioning of "s".
 *
 * ! 1 <= s.length <= 16
 * ! s contains only lowercase English letters.
 */

class Solution {
public:
    std::vector<std::vector<std::string>> partition(std::string s)
    {
        std::vector<std::string> palindromes;
        std::vector<std::vector<std::string>> result;
        backtrack(result, palindromes, 0, s);
        return result;
    }

private:
    void backtrack(std::vector<std::vector<std::string>>& result,
                   std::vector<std::string>& palindromes,
                   int start,
                   const std::string& s)
    {
        if (start == s.size()) {
            result.push_back(palindromes);
            return;
        }
        for (int end = start; end < s.size(); ++end) {
            if (isValid(start, end, s)) {
                palindromes.push_back(s.substr(start, end - start + 1));
                backtrack(result, palindromes, end + 1, s);
                palindromes.pop_back();
            }
        }
    }

    bool isValid(int start, int end, const std::string& s)
    {
        if (start > end)
            return false;

        while (start < end) {
            if (s[start++] != s[end--])
                return false;
        }
        return true;
    }
};
