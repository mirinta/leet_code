#include <algorithm>
#include <array>
#include <queue>
#include <string>
#include <vector>

/**
 * You are given a string s. s[i] is either a lowercase English letter or '?'.
 *
 * For a string t having length m containing only lowercase English letters, we define the function
 * cost(i) for an index i as the number of characters equal to t[i] that appeared before it, i.e. in
 * the range [0, i - 1].
 *
 * The value of t is the sum of cost(i) for all indices i.
 *
 * For example, for the string t = "aab":
 *
 * - cost(0) = 0
 *
 * - cost(1) = 1
 *
 * - cost(2) = 0
 *
 * - Hence, the value of "aab" is 0 + 1 + 0 = 1.
 *
 * Your task is to replace all occurrences of '?' in s with any lowercase English letter so that the
 * value of s is minimized.
 *
 * Return a string denoting the modified string with replaced occurrences of '?'. If there are
 * multiple strings resulting in the minimum value, return the lexicographically smallest one.
 *
 * ! 1 <= s.length <= 10^5
 * ! s[i] is either a lowercase English letter or '?'.
 */

class Solution {
public:
    std::string minimizeStringValue(std::string& s)
    {
        // let X = frequency of letter c in s
        // say the occurrences of c are i1, i2, ..., iX
        // then cost(i1) = 0, cost(i2) = 1, ..., cost(iX) = X-1
        // then cost(i1) + cost(i2) + ... + cost(iX) = X(X-1)/2
        // thus, total cost of s = sum of X(X-1)/2
        // where X is the frequency of each distinct letter of s
        // total cost is irrelevant to letters' positions
        const int n = s.size();
        std::array<int, 26> count{};
        for (const auto& c : s) {
            if (c == '?')
                continue;

            count[c - 'a']++;
        }
        using Pair = std::pair<int, int>; // <frequency, letter index>
        std::priority_queue<Pair, std::vector<Pair>, std::greater<>> pq;
        for (int i = 0; i < 26; ++i) {
            pq.emplace(count[i], i);
        }
        std::string candidates;
        for (const auto& c : s) {
            if (c != '?')
                continue;

            const auto [freq, i] = pq.top();
            pq.pop();
            candidates.push_back('a' + i);
            pq.emplace(freq + 1, i);
        }
        std::sort(candidates.begin(), candidates.end());
        std::string result;
        result.reserve(n);
        for (int i = 0, j = 0; i < n; ++i) {
            if (s[i] != '?') {
                result.push_back(s[i]);
            } else {
                result.push_back(candidates[j++]);
            }
        }
        return result;
    }
};