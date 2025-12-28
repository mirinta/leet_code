#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * A string s is called good if there are no two different characters in s that have the same
 * frequency.
 *
 * Given a string s, return the minimum number of characters you need to delete to make s good.
 *
 * The frequency of a character in a string is the number of times it appears in the string. For
 * example, in the string "aab", the frequency of 'a' is 2, while the frequency of 'b' is 1.
 *
 * ! 1 <= s.length <= 10^5
 * ! s contains only lowercase English letters.
 */

class Solution {
public:
    int minDeletions(std::string s)
    {
        // if A and B have the same frequency,
        // delete one of A (or B),
        // repeat the process until all characters have different frequencies
        return approach2(s);
    }

private:
    int approach2(const std::string& s)
    {
        std::unordered_map<char, int> map;
        for (const auto& c : s) {
            map[c]++;
        }
        std::priority_queue<int> pq; // max heap
        for (const auto& [c, freq] : map) {
            pq.push(freq);
        }
        int result = 0;
        while (pq.size() > 1) {
            const int freq = pq.top();
            pq.pop();
            if (freq == pq.top()) {
                result++;
                if (freq - 1 > 0) {
                    pq.push(freq - 1);
                }
            }
        }
        return result;
    }

    int approach1(const std::string& s)
    {
        std::unordered_map<char, int> map;
        for (const auto& c : s) {
            map[c]++;
        }
        std::unordered_set<int> checked;
        int result = 0;
        for (const auto& pair : map) {
            int freq = pair.second;
            // frequency of 0 is valid
            while (freq > 0 && checked.count(freq)) {
                freq--;
                result++;
            }
            checked.insert(freq);
        }
        return result;
    }
};