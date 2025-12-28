#include <queue>
#include <string>

/**
 * A string s is called happy if it satisfies the following conditions:
 *
 * - s only contains the letters 'a', 'b', and 'c'.
 *
 * - s does not contain any of "aaa", "bbb", or "ccc" as a substring.
 *
 * - s contains at most a occurrences of the letter 'a'.
 *
 * - s contains at most b occurrences of the letter 'b'.
 *
 * - s contains at most c occurrences of the letter 'c'.
 *
 * Given three integers a, b, and c, return the longest possible happy string. If there are multiple
 * longest happy strings, return any of them. If there is no such string, return the empty string
 * "".
 *
 * A substring is a contiguous sequence of characters within a string.
 *
 * ! 0 <= a, b, c <= 100
 * ! a + b + c > 0
 */

class Solution {
public:
    std::string longestDiverseString(int a, int b, int c)
    {
        std::priority_queue<std::pair<int, char>> pq;
        if (a > 0) {
            pq.emplace(a, 'a');
        }
        if (b > 0) {
            pq.emplace(b, 'b');
        }
        if (c > 0) {
            pq.emplace(c, 'c');
        }
        std::string result;
        while (!pq.empty()) {
            if (pq.size() == 1) {
                for (int i = 0; i < std::min(2, pq.top().first); ++i) {
                    result.push_back(pq.top().second);
                }
                break;
            }
            auto [freq1, c1] = pq.top();
            pq.pop();
            auto [freq2, c2] = pq.top();
            pq.pop();
            for (int i = 0; i < std::min(2, freq1 - freq2 + 1); ++i) {
                result.push_back(c1);
                freq1--;
            }
            result.push_back(c2);
            freq2--;
            if (freq1 > 0) {
                pq.emplace(freq1, c1);
            }
            if (freq2 > 0) {
                pq.emplace(freq2, c2);
            }
        }
        return result;
    }
};