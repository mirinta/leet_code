#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * Given a string s, sort it in decreasing order based on the frequency of the characters. The
 * frequency of a character is the number of times it appears in the string.
 *
 * Return the sorted string. If there are multiple answers, return any of them.
 *
 * ! 1 <= s.length <= 5 * 10^5
 * ! s consists of uppercase and lowercase English letters and digits.
 */

class Solution {
public:
    std::string frequencySort(std::string s)
    {
        std::unordered_map<char, int> map;
        for (const auto& c : s) {
            map[c]++;
        }
        std::priority_queue<Pair, std::vector<Pair>, Compare> pq(map.begin(), map.end());
        std::string result;
        result.reserve(s.size());
        while (!pq.empty()) {
            const auto [c, count] = pq.top();
            pq.pop();
            result.append(count, c);
        }
        return result;
    }

private:
    using Pair = std::pair<char, int>;

    struct Compare {
        bool operator()(const Pair& p1, const Pair& p2)
        {
            if (p1.second == p2.second)
                return p1.first > p2.first;

            return p1.second < p2.second;
        }
    };
};