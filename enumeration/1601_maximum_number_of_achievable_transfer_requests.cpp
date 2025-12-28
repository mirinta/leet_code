#include <algorithm>
#include <functional>
#include <vector>

/**
 * We have n buildings numbered from 0 to n - 1. Each building has a number of employees. It's
 * transfer season, and some employees want to change the building they reside in.
 *
 * You are given an array requests where requests[i] = [from_i, to_i] represents an employee's
 * request to transfer from building from_i to building to_i.
 *
 * All buildings are full, so a list of requests is achievable only if for each building, the net
 * change in employee transfers is zero. This means the number of employees leaving is equal to the
 * number of employees moving in. For example if n = 3 and two employees are leaving building 0, one
 * is leaving building 1, and one is leaving building 2, there should be two employees moving to
 * building 0, one employee moving to building 1, and one employee moving to building 2.
 *
 * Return the maximum number of achievable requests.
 *
 * ! 1 <= n <= 20
 * ! 1 <= requests.length <= 16
 * ! requests[i].length == 2
 * ! 0 <= from_i, to_i < n
 */

class Solution {
public:
    int maximumRequests(int n, std::vector<std::vector<int>>& requests)
    {
        return approach3(n, requests);
    }

private:
    // bit mask using std::next_permutation
    int approach3(int n, const std::vector<std::vector<int>>& requests)
    {
        const int m = requests.size();
        std::vector<int> mask(m, 0);
        std::vector<int> netChange(n, 0);
        auto isValid = [&]() {
            std::fill(netChange.begin(), netChange.end(), 0);
            for (int i = 0; i < mask.size(); ++i) {
                if (mask[i] == 1) {
                    netChange[requests[i][0]]--;
                    netChange[requests[i][1]]++;
                }
            }
            return std::all_of(netChange.begin(), netChange.end(), [](const auto& val) { return val == 0; });
        };
        for (int i = m; i >= 1; --i) {
            std::fill(mask.begin(), mask.end(), 0);
            std::fill(mask.begin() + m - i, mask.end(), 1);
            do {
                if (isValid())
                    return i;

            } while (std::next_permutation(mask.begin(), mask.end()));
        }
        return 0;
    }

    // bit mask
    int approach2(int n, const std::vector<std::vector<int>>& requests)
    {
        const int m = requests.size();
        std::vector<int> netChange(n, 0);
        auto isValid = [&](int mask) {
            std::fill(netChange.begin(), netChange.end(), 0);
            for (int i = 0; i < m; ++i) {
                if ((mask >> i) & 1) {
                    netChange[requests[i][0]]--;
                    netChange[requests[i][1]]++;
                }
            }
            return std::all_of(netChange.begin(), netChange.end(), [](const auto& val) { return val == 0; });
        };
        int result = 0;
        for (int mask = (1 << m) - 1; mask >= 1; --mask) {
            if (const int ones = numOfBinaryOnes(mask); ones > result && isValid(mask)) {
                result = std::max(result, ones);
            }
        }
        return result;
    }

    int numOfBinaryOnes(int n)
    {
        int result = 0;
        while (n) {
            result++;
            n &= n - 1;
        }
        return result;
    }

    // backtracking
    int approach1(int n, const std::vector<std::vector<int>>& requests)
    {
        std::vector<int> netChange(n, 0);
        int result = 0;
        std::function<void(int, int)> backtrack = [&](int i, int count) {
            if (i == requests.size()) {
                if (std::all_of(netChange.begin(), netChange.end(), [](const auto& val) { return val == 0; })) {
                    result = std::max(result, count);
                }
                return;
            }
            netChange[requests[i][0]]--;
            netChange[requests[i][1]]++;
            backtrack(i + 1, count + 1);
            netChange[requests[i][0]]++;
            netChange[requests[i][1]]--;
            backtrack(i + 1, count);
        };
        backtrack(0, 0);
        return result;
    }
};