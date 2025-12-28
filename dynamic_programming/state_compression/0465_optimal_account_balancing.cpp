#include <unordered_map>
#include <vector>

/**
 * You are given an array of transactions transactions where transactions[i] = [fromi, toi, amounti]
 * indicates that the person with ID = fromi gave amounti $ to the person with ID = toi.
 *
 * Return the minimum number of transactions required to settle the debt.
 *
 * ! 1 <= transactions.length <= 8
 * ! transactions[i].length == 3
 * ! 0 <= fromi, toi < 12
 * ! fromi != toi
 * ! 1 <= amounti <= 100
 */

class Solution {
public:
    int minTransfers(std::vector<std::vector<int>>& transactions)
    {
        return approach2(transactions);
    }

private:
    int approach2(const std::vector<std::vector<int>>& transactions)
    {
        std::unordered_map<int, int> map;
        for (const auto& trans : transactions) {
            map[trans[0]] -= trans[2];
            map[trans[1]] += trans[2];
        }
        std::vector<int> v;
        for (const auto& pair : map) {
            v.push_back(pair.second);
        }
        // dp[i] = min num of transactions to settle the debt of group i
        // if group i can be settled and group i has N people,
        // then debt[i] = 0 and we need at most N-1 transactions
        // if j is a subgroup of i and debt[j] = 0,
        // then dp[i] = min(dp[i], dp[j] + dp[i^j])
        const int n = v.size(); // num of people
        const int m = 1 << n;   // num of groups
        std::vector<int> debt(m, 0);
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i >> j) & 1) {
                    debt[i] += v[j];
                }
            }
        }
        std::vector<int> dp(m, INT_MAX / 2);
        dp[0] = 0;
        for (int i = 1; i < m; ++i) {
            if (debt[i] != 0)
                continue;

            dp[i] = numOfBinaryOnes(i) - 1;
            for (int sub = i; sub > 0; sub = (sub - 1) & i) {
                if (debt[sub] == 0) {
                    dp[i] = std::min(dp[i], dp[sub] + dp[i ^ sub]);
                }
            }
        }
        return dp[m - 1];
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

    int approach1(const std::vector<std::vector<int>>& transactions)
    {
        std::unordered_map<int, int> map;
        for (const auto& trans : transactions) {
            map[trans[0]] -= trans[2];
            map[trans[1]] += trans[2];
        }
        std::vector<int> debt;
        for (const auto& pair : map) {
            if (pair.second != 0) {
                debt.push_back(pair.second);
            }
        }
        return backtrack(debt, 0);
    }

    // min num of transactions to settle debt[i:n-1]
    int backtrack(std::vector<int>& debt, int i)
    {
        while (i < debt.size() && debt[i] == 0) {
            i++;
        }
        if (i == debt.size())
            return 0;

        int result = INT_MAX / 2;
        for (int j = i + 1; j < debt.size(); ++j) {
            if ((debt[i] ^ debt[j]) < 0) {
                debt[j] += debt[i];
                result = std::min(result, 1 + backtrack(debt, i + 1));
                debt[j] -= debt[i];
            }
        }
        return result;
    }
};