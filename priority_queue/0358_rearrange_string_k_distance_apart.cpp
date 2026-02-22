#include <queue>
#include <string>
#include <unordered_map>

/**
 * Given a string s and an integer k, rearrange s such that the same characters are at least
 * distance k from each other. If it is not possible to rearrange the string, return an empty string
 * "".
 *
 * ! 1 <= s.length <= 3 * 10^5
 * ! s consists of only lowercase English letters.
 * ! 0 <= k <= s.length
 */

class Solution {
public:
    std::string rearrangeString(std::string& s, int k)
    {
        if (k == 0)
            return s;

        // i i+1 ........... i+k-1 i+k
        // x |<-different chars->| x
        // from index i to index i+k-1, we need at least k different chars
        std::unordered_map<char, int> map;
        for (const auto& c : s) {
            map[c]++;
        }
        using Pair = std::pair<char, int>; // <char, freq>
        auto compare = [](const auto& p1, const auto& p2) {
            if (p1.second == p2.second)
                return p1.first > p2.first;

            return p1.second < p2.second;
        };
        std::priority_queue<Pair, std::vector<Pair>, decltype(compare)> pq(compare);
        for (const auto& [c, freq] : map) {
            pq.emplace(c, freq);
        }
        std::string result;
        result.reserve(s.size());
        while (!pq.empty()) {
            if (pq.top().second > 1 && pq.size() < k)
                return {};

            // use the top k characters (must be different)
            std::vector<Pair> pairs;
            const int count = std::min<int>(k, pq.size());
            pairs.reserve(k);
            for (int i = 0; i < count; ++i) {
                const auto [c, freq] = pq.top();
                pq.pop();
                result.push_back(c);
                if (freq - 1 > 0) {
                    pairs.emplace_back(c, freq - 1);
                }
            }
            for (const auto& [c, freq] : pairs) {
                pq.emplace(c, freq);
            }
        }
        return result;
    }
};
