#include <queue>
#include <string>
#include <unordered_map>

/**
 * You are given a string s and an integer repeatLimit. Construct a new string repeatLimitedString
 * using the characters of s such that no letter appears more than repeatLimit times in a row. You
 * do not have to use all characters from s.
 *
 * Return the lexicographically largest repeatLimitedString possible.
 *
 * A string a is lexicographically larger than a string b if in the first position where a and b
 * differ, string a has a letter that appears later in the alphabet than the corresponding letter in
 * b. If the first min(a.length, b.length) characters do not differ, then the longer string is the
 * lexicographically larger one.
 *
 * ! 1 <= repeatLimit <= s.length <= 10^5
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    std::string repeatLimitedString(std::string s, int repeatLimit)
    {
        std::unordered_map<char, int> map;
        for (const auto& c : s) {
            map[c]++;
        }
        std::priority_queue<std::pair<char, int>, std::vector<std::pair<char, int>>> pq;
        for (const auto& [c, count] : map) {
            pq.emplace(c, count);
        }
        std::string result;
        while (!pq.empty()) {
            const auto [c1, freq1] = pq.top();
            pq.pop();
            if (result.empty() || result.back() != c1) {
                const int count = std::min(freq1, repeatLimit);
                result.insert(result.end(), count, c1);
                if (freq1 > count) {
                    pq.emplace(c1, freq1 - count);
                }
                continue;
            }
            if (pq.empty())
                break;

            const auto [c2, freq2] = pq.top();
            pq.pop();
            result.push_back(c2);
            if (freq2 > 1) {
                pq.emplace(c2, freq2 - 1);
            }
            pq.emplace(c1, freq1);
        }
        return result;
    }
};