#include <array>
#include <string>
#include <vector>

/**
 * The set [1, 2, 3, ..., n] contains a total of n! unique permutations.
 *
 * By listing and labeling all of the permutations in order,
 * we get the following sequence for n = 3:
 *
 * 1. "123"
 * 2. "132"
 * 3. "213"
 * 4. "231"
 * 5. "312"
 * 6. "321"
 *
 * Given n and k, return the kth permutation sequence.
 *
 * ! 1 <= n <= 9
 * ! 1 <= k <= n!
 */

class Solution {
public:
    std::string getPermutation(int n, int k)
    {
        std::array<bool, 10> used{};
        std::fill(used.begin(), used.end(), false);
        std::vector<int> factorial(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            factorial[i] = factorial[i - 1] * i;
        }
        std::string result;
        dfs(result, used, 0, n, k, factorial);
        return result;
    }

private:
    void dfs(std::string& result, std::array<bool, 10>& used, int i, int n, int k, const std::vector<int>& factorial)
    {
        if (i == n)
            return;

        for (int v = 1; v <= 9; ++v) {
            if (used[v])
                continue;

            if (factorial[n - i - 1] < k) {
                k -= factorial[n - i - 1];
                continue;
            }
            result.push_back(v + '0');
            used[v] = true;
            break;
        }
        dfs(result, used, i + 1, n, k, factorial);
    }
};