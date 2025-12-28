#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * Given a string s, rearrange the characters of s so that any two adjacent characters are not the
 * same.
 *
 * Return any possible rearrangement of s or return "" if not possible.
 *
 * ! 1 <= s.length <= 500
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    std::string reorganizeString(std::string s)
    {
        // for any character x,
        // if freq[x] > (N+1)/2, then there's no way to reorganize the given string
        // - N is the length of the given string
        // - if N is odd, say s = aab, freq[a]=2 <= (N+1)/2, OK
        // - if N is odd, say s = aaa, freq[a]=3 > (N+1)/2, NO SOLUTION
        // - if N is even, say s = aabb, freq[a]=2 <= (N+1)/2, OK
        // - if N is even, say s = aaab, freq[a]=3 > (N+1)/2, NO SOLUTION
        std::unordered_map<char, int> map;
        for (const auto& c : s) {
            map[c]++;
        }
        using Pair = std::pair<char, int>;
        auto comparator = [](const auto& p1, const auto& p2) {
            return p1.second == p2.second ? p1.first > p2.first : p1.second < p2.second;
        };
        // sort by frequency in decreasing order
        // if two characters have the same frequency, sort by letter in increasing order
        std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(comparator);
        for (const auto& pair : map) {
            if (pair.second > (s.size() + 1) / 2)
                return {};

            pq.emplace(pair);
        }
        std::string result;
        while (!pq.empty()) {
            const auto [c1, freq1] = pq.top();
            pq.pop();
            result.push_back(c1);
            if (!pq.empty()) {
                const auto [c2, freq2] = pq.top();
                pq.pop();
                result.push_back(c2);
                if (freq2 > 1) {
                    pq.emplace(c2, freq2 - 1);
                }
            }
            if (freq1 > 1) {
                pq.emplace(c1, freq1 - 1);
            }
        }
        return result;
    }
};
