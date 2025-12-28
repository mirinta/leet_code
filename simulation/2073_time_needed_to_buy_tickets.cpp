#include <queue>
#include <vector>

/**
 * There are n people in a line queuing to buy tickets, where the 0th person is at the front of the
 * line and the (n - 1)th person is at the back of the line.
 *
 * You are given a 0-indexed integer array tickets of length n where the number of tickets that the
 * ith person would like to buy is tickets[i].
 *
 * Each person takes exactly 1 second to buy a ticket. A person can only buy 1 ticket at a time and
 * has to go back to the end of the line (which happens instantaneously) in order to buy more
 * tickets. If a person does not have any tickets left to buy, the person will leave the line.
 *
 * Return the time taken for the person at position k (0-indexed) to finish buying tickets.
 *
 * ! n == tickets.length
 * ! 1 <= n <= 100
 * ! 1 <= tickets[i] <= 100
 * ! 0 <= k < n
 */

class Solution {
public:
    int timeRequiredToBuy(std::vector<int>& tickets, int k)
    {
        return approach2(tickets, k);
    }

private:
    int approach2(const std::vector<int>& tickets, int k)
    {
        const int n = tickets.size();
        int result = 0;
        for (int i = 0; i < n; ++i) {
            if (i <= k) {
                result += std::min(tickets[i], tickets[k]);
            } else {
                result += std::min(tickets[i], tickets[k] - 1);
            }
        }
        return result;
    }

    int approach1(std::vector<int>& tickets, int k)
    {
        const int n = tickets.size();
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            queue.push(i);
        }
        int result = 0;
        while (!queue.empty()) {
            result++;
            const int i = queue.front();
            queue.pop();
            tickets[i]--;
            if (i == k && tickets[i] == 0)
                break;

            if (tickets[i] > 0) {
                queue.push(i);
            }
        }
        return result;
    }
};