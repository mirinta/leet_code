#include <string>
#include <vector>

/**
 * You are given the customer visit log of a shop represented by a 0-indexed string customers
 * consisting only of characters 'N' and 'Y':
 *
 * - if the ith character is 'Y', it means that customers come at the ith hour
 *
 * - whereas 'N' indicates that no customers come at the ith hour.
 *
 * If the shop closes at the jth hour (0 <= j <= n), the penalty is calculated as follows:
 *
 * - For every hour when the shop is open and no customers come, the penalty increases by 1.
 *
 * - For every hour when the shop is closed and customers come, the penalty increases by 1.
 *
 * Return the earliest hour at which the shop must be closed to incur a minimum penalty.
 *
 * Note that if a shop closes at the jth hour, it means the shop is closed at the hour j.
 *
 * ! 1 <= customers.length <= 10^5
 * ! customers consists only of characters 'Y' and 'N'.
 */

class Solution
{
public:
    int bestClosingTime(std::string customers) { return approach2(customers); }

private:
    int approach2(const std::string& customers)
    {
        const int n = customers.size();
        int min = 0;
        int result = 0;
        for (int i = 0, penalty = 0; i < n; ++i) {
            if (customers[i] == 'Y') {
                penalty--;
            } else {
                penalty++;
            }
            if (penalty < min) {
                min = penalty;
                result = i + 1;
            }
        }
        return result;
    }

    int approach1(const std::string& customers)
    {
        // penalty += 1 for each N in [0:j-1]
        // penalty += 1 for each Y in [j+1:n-1]
        const int n = customers.size();
        std::vector<std::pair<int, int>> presum(n + 1, {0, 0});
        for (int i = 1; i <= n; ++i) {
            presum[i].first = presum[i - 1].first + (customers[i - 1] == 'Y');
            presum[i].second = presum[i - 1].second + (customers[i - 1] == 'N');
        }
        int min = presum[n].second;
        int result = n;
        for (int j = 0; j < n; ++j) {
            const int penalty = presum[j].second + presum[n].first - presum[j].first;
            if (penalty < min) {
                min = penalty;
                result = j;
            } else if (penalty == min) {
                result = std::min(result, j);
            }
        }
        return result;
    }
};
