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
    std::string rearrangeString(std::string s, int k)
    {
        if (k == 0)
            return s;

        std::unordered_map<char, int> map; // letter to frequency
        for (const auto& c : s) {
            map[c]++;
        }
        auto comparator = [](const auto& p1, const auto& p2) {
            // sort frequencies in descending order
            // if there's a tie, sort letters in ascending order
            return p1.second == p2.second ? p1.first > p2.first : p1.second < p2.second;
        };
        using Pair = std::pair<char, int>; // letter to frequency
        std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(comparator);
        for (const auto& pair : map) {
            pq.emplace(pair);
        }
        std::string result;
        while (!pq.empty()) {
            // less than k characters
            // - if there's only one letter left and its frequency is 1, ok
            // - otherwise, it is not possible to rearrange the string
            if (pq.size() < k && pq.top().second > 1)
                return {};

            // pick the top k frequent characters
            std::vector<Pair> vec(std::min<size_t>(k, pq.size()));
            for (auto& pair : vec) {
                pair = pq.top();
                pq.pop();
                result.push_back(pair.first);
                pair.second--;
            }
            for (const auto& pair : vec) {
                if (pair.second > 0) {
                    pq.emplace(pair);
                }
            }
        }
        return result;
    }
};
