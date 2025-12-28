#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed array of unique strings words.
 *
 * A palindrome pair is a pair of integers (i, j) such that:
 *
 * - 0 <= i, j < words.length,
 *
 * - i != j, and
 *
 * - words[i] + words[j] (the concatenation of the two strings) is a palindrome.
 *
 * Return an array of all the palindrome pairs of words.
 *
 * You must write an algorithm with O(sum of words[i].length) runtime complexity.
 *
 * ! 1 <= words.length <= 5000
 * ! 0 <= words[i].length <= 300
 * ! words[i] consists of lowercase English letters.
 */

class Solution {
public:
    std::vector<std::vector<int>> palindromePairs(std::vector<std::string>& words)
    {
        // X ...... X X ....... X
        // |<-left->| |<-right->|
        // |<---------s-------->|
        //
        // case1: s_right is a palindrome, then we need to find reverse(s_left)
        // case2: s_left is a palindrome, then we need to find reverse(s_right)
        const int n = words.size();
        std::unordered_map<std::string, int> map; // all strings are unique
        for (int i = 0; i < n; ++i) {
            map[words[i]] = i;
        }
        std::vector<std::vector<int>> result;
        for (int i = 0; i < n; ++i) {
            auto s = words[i];
            for (int len = 0; len <= s.size(); ++len) {
                if (isPalindrome(s, 0, len - 1)) {
                    auto right = s.substr(len, s.size() - len);
                    std::reverse(right.begin(), right.end());
                    if (map.count(right) && map[right] != i) {
                        result.push_back({map[right], map[s]});
                    }
                }
                if (len < s.size() && isPalindrome(s, len, s.size() - 1)) {
                    auto left = s.substr(0, len);
                    std::reverse(left.begin(), left.end());
                    if (map.count(left) && map[left] != i) {
                        result.push_back({map[s], map[left]});
                    }
                }
            }
        }
        return result;
    }

private:
    bool isPalindrome(const std::string& s, int lo, int hi)
    {
        while (lo < hi) {
            if (s[lo] != s[hi])
                return false;

            lo++;
            hi--;
        }
        return true;
    }
};