#include <string>
#include <vector>

/**
 * You are given an array arr of size n consisting of non-empty strings.
 *
 * Find a string array answer of size n such that:
 *
 * - answer[i] is the shortest substring of arr[i] that does not occur as a substring in any other
 * string in arr. If multiple such substrings exist, answer[i] should be the lexicographically
 * smallest. And if no such substring exists, answer[i] should be an empty string.
 *
 * Return the array answer.
 *
 * ! n == arr.length
 * ! 2 <= n <= 100
 * ! 1 <= arr[i].length <= 20
 * ! arr[i] consists only of lowercase English letters.
 */

class Solution {
public:
    std::vector<std::string> shortestSubstrings(std::vector<std::string>& arr)
    {
        const int n = arr.size();
        std::vector<std::string> result;
        result.reserve(n);
        for (int i = 0; i < n; ++i) {
            result.emplace_back(solve(arr[i], i, arr));
        }
        return result;
    }

private:
    // return the shortest substring of s that does not occur as a substring of words[i!=ignore]
    std::string solve(const std::string& s, int ignore, const std::vector<std::string>& words)
    {
        const int n = s.size();
        std::string result;
        int minLength = INT_MAX;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                const auto sub = s.substr(i, j - i + 1);
                if (!isValid(sub, ignore, words))
                    continue;

                if (j - i + 1 < minLength) {
                    result = sub;
                    minLength = j - i + 1;
                } else if (j - i + 1 == minLength) {
                    result = std::min(result, sub);
                }
            }
        }
        return result;
    }

    // check if s is a substring of words[i!=ignore]
    bool isValid(const std::string& s, int ignore, const std::vector<std::string>& words)
    {
        for (int i = 0; i < words.size(); ++i) {
            if (i == ignore)
                continue;

            if (words[i].find(s) != std::string::npos)
                return false;
        }
        return true;
    }
};