#include <vector>

/**
 * Given a positive integer n, there exists a 0-indexed array called powers, composed of the minimum
 * number of powers of 2 that sum to n. The array is sorted in non-decreasing order, and there is
 * only one way to form the array.
 *
 * You are also given a 0-indexed 2D integer array queries, where queries[i] = [lefti, righti]. Each
 * queries[i] represents a query where you have to find the product of all powers[j] with lefti <= j
 * <= righti.
 *
 * Return an array answers, equal in length to queries, where answers[i] is the answer to the ith
 * query. Since the answer to the ith query may be too large, each answers[i] should be returned
 * modulo 10^9 + 7.
 *
 * ! 1 <= n <= 10^9
 * ! 1 <= queries.length <= 10^5
 * ! 0 <= starti <= endi < powers.length
 */

class Solution
{
public:
    std::vector<int> productQueries(int n, std::vector<std::vector<int>>& queries)
    {
        const auto nums = helper(n);
        const int m = nums.size();
        std::vector<int> presum(m + 1, 1);
        for (int i = 1; i <= m; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        std::vector<int> result;
        result.reserve(queries.size());
        for (const auto& q : queries) {
            result.push_back(fastPowMod(2, presum[q[1] + 1] - presum[q[0]]));
        }
        return result;
    }

private:
    std::vector<int> helper(int n)
    {
        std::vector<int> result;
        for (int i = 0; n > 0; ++i) {
            if (n & 1) {
                result.push_back(i);
            }
            n >>= 1;
        }
        return result;
    }

    long long fastPowMod(long long a, long long b, long long mod = 1e9 + 7)
    {
        long long result = 1;
        long long base = a;
        while (b > 0) {
            if (b & 1) {
                result = result * base % mod;
            }
            base = base * base % mod;
            b >>= 1;
        }
        return result;
    }
};
