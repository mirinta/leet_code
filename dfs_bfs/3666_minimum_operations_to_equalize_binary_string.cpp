#include <queue>
#include <set>
#include <string>

/**
 * You are given a binary string s, and an integer k,
 *
 * In one operation, you must choose exactly k different indices and flip each '0' to '1' and each '1' to'0'.
 *
 * Return the minimum number of operations required to make all characters in the string equal to '1'. If it is not
 * possible, return -1.
 *
 * ! 1 <= s.length <= 10^5
 * ! s[i] is either '0' or '1'.
 * ! 1 <= k <= s.length
 */

class Solution {
public:
    int minOperations(std::string& s, int k)
    {
        // current round:
        // num of zeros = z, num ones = n - z
        // pick x zeros and pick k - x ones, constraints:
        // 1. x <= min(k, z)
        // 2. k - x <= min(k, n - z), which means x >= k - min(k, n - z) => x >= max(0, z + k - n)
        // thus, x is in the range of [min(k, z), max(0, z + k - n)]
        // after applying the operations,
        // num of zeros = z' = z + k - 2 * x
        // z' is in the range of [z + k - 2 * max(0, z + k - n), z + k - 2 * min(k, z)]
        // z' has the same parity with z + k
        const int n = s.size();
        std::array<std::set<int>, 2> sets{};
        for (int i = 0; i <= n; ++i) {
            sets[i % 2].emplace(i);
        }
        const int zeros = std::count(s.begin(), s.end(), '0');
        std::queue<int> queue;
        queue.emplace(zeros);
        int result = 0;
        while (!queue.empty()) {
            for (int sz = queue.size(); sz > 0; --sz) {
                const auto z = queue.front();
                queue.pop();
                if (z == 0)
                    return result;

                const int min = z + k - 2 * std::min(k, z);
                const int max = z + k - 2 * std::max(0, z + k - n);
                auto& set = sets[(z + k) % 2];
                for (auto iter = set.lower_bound(min); iter != set.end() && *iter <= max; iter = set.erase(iter)) {
                    queue.emplace(*iter);
                }
            }
            result++;
        }
        return -1;
    }
};