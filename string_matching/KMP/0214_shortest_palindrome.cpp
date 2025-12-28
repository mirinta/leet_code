#include <string>
#include <vector>

/**
 * You are given a string s. You can convert s to a palindrome by adding characters in front of it.
 *
 * Return the shortest palindrome you can find by performing this transformation.
 *
 * ! 0 <= s.length <= 5 * 10^4
 * ! s consists of lowercase English letters only.
 */

class Solution {
public:
    std::string shortestPalindrome(std::string s)
    {
        // s can be divided into AB, where A is a palindrome substring of s
        // - A.size() can be 1
        // our goal is to find the longest A, then answer = B'AB = B's
        //
        // it is equivalent to find the maximum L such that x[0:L-1] = x[n-L:n-1],
        // where x = AB#B'A' = s#s'
        // length of the longest A = L
        const int n = s.size();
        const std::string r(s.rbegin(), s.rend());
        const auto next = preprocess(s + "#" + r);
        auto tail = s.substr(next.back(), n - next.back());
        std::reverse(tail.begin(), tail.end());
        return tail + s;
    }

private:
    std::vector<int> preprocess(const std::string& s)
    {
        const int n = s.size();
        std::vector<int> next(n);
        next[0] = 0;
        for (int i = 1; i < n; ++i) {
            int L = next[i - 1];
            while (L >= 1 && s[L] != s[i]) {
                L = next[L - 1];
            }
            next[i] = L + (s[L] == s[i]);
        }
        return next;
    }
};
