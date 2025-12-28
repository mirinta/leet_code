#include <algorithm>
#include <queue>
#include <vector>

/**
 * Suppose LeetCode will start its IPO soon. In order to sell a good price of its shares to Venture
 * Capital, LeetCode would like to work on some projects to increase its capital before the IPO.
 * Since it has limited resources, it can only finish at most k distinct projects before the IPO.
 * Help LeetCode design the best way to maximize its total capital after finishing at most k
 * distinct projects.
 *
 * You are given n projects where the ith project has a pure profit profits[i] and a minimum capital
 * of capital[i] is needed to start it.
 *
 * Initially, you have w capital. When you finish a project, you will obtain its pure profit and the
 * profit will be added to your total capital.
 *
 * Pick a list of at most k distinct projects from given projects to maximize your final capital,
 * and return the final maximized capital.
 *
 * The answer is guaranteed to fit in a 32-bit signed integer.
 *
 * ! 1 <= k <= 10^5
 * ! 0 <= w <= 10^9
 * ! n == profits.length
 * ! n == capital.length
 * ! 1 <= n <= 10^5
 * ! 0 <= profits[i] <= 10^4
 * ! 0 <= capital[i] <= 10^9
 */

class Solution {
public:
    int findMaximizedCapital(int k, int w, std::vector<int>& profits, std::vector<int>& capital)
    {
        const int n = profits.size();
        using Pair = std::pair<int, int>; // <capital, profit>
        std::vector<Pair> info(n);
        for (int i = 0; i < n; ++i) {
            info[i].first = capital[i];
            info[i].second = profits[i];
        }
        std::sort(info.begin(), info.end(), [](const auto& p1, const auto& p2) { return p1.first < p2.first; });
        std::priority_queue<int> pq; // max heap storing profits of available projects
        for (int t = 0, i = 0; t < k; ++t) {
            while (i < n && info[i].first <= w) {
                pq.push(info[i].second);
                i++;
            }
            if (pq.empty())
                break;

            w += pq.top();
            pq.pop();
        }
        return w;
    }
};
