#include <queue>
#include <unordered_set>
#include <vector>

/**
 * You are given an m x n matrix mat that has its rows sorted in non-decreasing order and an integer
 * k.
 *
 * You are allowed to choose exactly one element from each row to form an array.
 *
 * Return the kth smallest array sum among all possible arrays.
 *
 * ! m == mat.length
 * ! n == mat.length[i]
 * ! 1 <= m, n <= 40
 * ! 1 <= mat[i][j] <= 5000
 * ! 1 <= k <= min(200, nm)
 * ! mat[i] is a non-decreasing array.
 */

class Solution {
public:
    int kthSmallest(std::vector<std::vector<int>>& mat, int k)
    {
        return approach2(mat, k);
    }

private:
    static constexpr int kMod = 1e9 + 7;

    int approach2(const std::vector<std::vector<int>>& mat, int k)
    {
        int lo = 0;
        int hi = INT_MAX;
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, k, mat)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

    // count the num of arrays whose sum <= target and check if count >= k
    bool isValid(int target, int k, const std::vector<std::vector<int>>& mat)
    {
        const int m = mat.size();
        const int n = mat[0].size();
        int sum = 0;
        for (int i = 0; i < m; ++i) {
            sum += mat[i][0];
        }
        if (sum > target)
            return false;

        int count = 1;
        dfs(count, 0, sum, target, k, mat);
        return count >= k;
    }

    void dfs(int& count, int row, int sum, int target, int k, const std::vector<std::vector<int>>& mat)
    {
        const int m = mat.size();
        const int n = mat[0].size();
        if (row == m || count >= k)
            return;

        for (int j = 0; j < n; ++j) {
            if (sum - mat[row][0] + mat[row][j] <= target) {
                if (j > 0) {
                    count++;
                }
                dfs(count, row + 1, sum - mat[row][0] + mat[row][j], target, k, mat);
            }
        }
    }

    int approach1(const std::vector<std::vector<int>>& mat, int k)
    {
        const int m = mat.size();
        const int n = mat[0].size();
        using Pair = std::pair<int, std::vector<int>>;
        auto comparator = [](const auto& p1, const auto& p2) { return p1.first > p2.first; };
        std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(comparator);
        int sum = 0;
        for (int i = 0; i < m; ++i) {
            sum += mat[i][0];
        }
        pq.emplace(sum, std::vector<int>(m, 0));
        std::unordered_set<long long> visited;
        visited.insert(0);
        for (int t = 1; t < k; ++t) {
            auto [sum, indices] = pq.top();
            pq.pop();
            for (int i = 0; i < m; ++i) {
                indices[i]++;
                const long long key = encode(n, indices);
                if (indices[i] < n && !visited.count(key)) {
                    pq.emplace(sum + mat[i][indices[i]] - mat[i][indices[i] - 1], indices);
                    visited.insert(key);
                }
                indices[i]--;
            }
        }
        return pq.top().first;
    }

    long long encode(int n, const std::vector<int>& indices)
    {
        const int m = indices.size();
        long long result = 0;
        for (int i = 0; i < m; ++i) {
            result = (result + fastPowMod(n, i, kMod) * indices[i] % kMod);
        }
        return result;
    }

    long long fastPowMod(long long a, long long b, long long mod)
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