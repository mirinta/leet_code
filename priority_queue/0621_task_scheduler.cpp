#include <array>
#include <queue>
#include <vector>

/**
 * You are given an array of CPU tasks, each represented by letters A to Z, and a cooling time, n.
 * Each cycle or interval allows the completion of one task. Tasks can be completed in any order,
 * but there's a constraint: identical tasks must be separated by at least n intervals due to
 * cooling time.
 *
 * ​Return the minimum number of intervals required to complete all tasks.
 *
 * ! 1 <= tasks.length <= 10^4
 * ! tasks[i] is an uppercase English letter.
 * ! 0 <= n <= 100
 */

class Solution {
public:
    int leastInterval(std::vector<char>& tasks, int n)
    {
        std::array<int, 26> count{};
        for (const auto& c : tasks) {
            count[c - 'A']++;
        }
        std::priority_queue<int, std::vector<int>, std::less<>> pq;
        for (int i = 0; i < 26; ++i) {
            if (count[i] == 0)
                continue;

            pq.emplace(count[i]);
        }
        int result = 0;
        while (!pq.empty()) {
            const int sz = pq.size();
            std::vector<int> used;
            for (int i = 0; i < std::min(n + 1, sz); ++i) {
                const auto freq = pq.top();
                pq.pop();
                if (freq > 1) {
                    used.push_back(freq - 1);
                }
            }
            result += used.empty() ? std::min(n + 1, sz) : n + 1;
            for (const auto& val : used) {
                pq.emplace(val);
            }
        }
        return result;
    }
};