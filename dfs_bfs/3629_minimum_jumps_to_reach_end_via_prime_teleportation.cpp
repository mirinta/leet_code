#include <array>
#include <queue>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums of length n.
 *
 * You start at index 0, and your goal is to reach index n - 1.
 *
 * From any index i, you may perform one of the following operations:
 *
 * - Adjacent Step: Jump to index i + 1 or i - 1, if the index is within bounds.
 *
 * - Prime Teleportation: If nums[i] is a prime number p, you may instantly jump to any index j != i such that nums[j] %
 * p == 0.
 *
 * Return the minimum number of jumps required to reach index n - 1.
 *
 * ! 1 <= n == nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^6
 */

static const auto factors = []() {
    const int max = 1e6;
    std::array<std::vector<int>, max + 1> factors;
    for (int i = 2; i <= max; ++i) {
        if (!factors[i].empty())
            continue;

        for (int j = i; j <= max; j += i) {
            factors[j].push_back(i);
        }
    }
    return factors;
}();

class Solution {
public:
    int minJumps(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::unordered_map<int, std::vector<int>> teleportations;
        for (int i = 0; i < n; ++i) {
            for (const auto& f : factors[nums[i]]) {
                teleportations[f].push_back(i);
            }
        }
        std::vector<bool> visited(n, false);
        visited[0] = true;
        std::queue<int> queue;
        queue.emplace(0);
        int result = 0;
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto index = queue.front();
                queue.pop();
                if (index == n - 1)
                    return result;

                if (index + 1 < n && !visited[index + 1]) {
                    visited[index + 1] = true;
                    queue.emplace(index + 1);
                }
                if (index - 1 >= 0 && !visited[index - 1]) {
                    visited[index - 1] = true;
                    queue.emplace(index - 1);
                }
                if (!teleportations.count(nums[index]) || teleportations[nums[index]].empty())
                    continue;

                for (const auto& next : teleportations[nums[index]]) {
                    if (!visited[next]) {
                        visited[next] = true;
                        queue.emplace(next);
                    }
                }
                teleportations[nums[index]].clear(); // important
            }
            result++;
        }
        return -1;
    }
};
