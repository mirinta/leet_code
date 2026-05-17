#include <array>
#include <queue>
#include <vector>

/**
 * Given an array of non-negative integers arr, you are initially positioned at start index of the
 * array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach
 * to any index with value 0.
 *
 * Notice that you can not jump outside of the array at any time.
 *
 * ! 1 <= arr.length <= 5 * 10^4
 * ! 0 <= arr[i] < arr.length
 * ! 0 <= start < arr.length
 */

class Solution {
public:
    bool canReach(std::vector<int>& arr, int start)
    {
        static constexpr std::array<int, 2> directions{-1, 1};
        const int n = arr.size();
        std::vector<bool> visited(n, false);
        visited[start] = true;
        std::queue<int> queue;
        queue.emplace(start);
        while (!queue.empty()) {
            const auto i = queue.front();
            queue.pop();
            if (arr[i] == 0)
                return true;

            for (const auto& d : directions) {
                const int j = i + d * arr[i];
                if (j >= 0 && j < n && !visited[j]) {
                    visited[j] = true;
                    queue.emplace(j);
                }
            }
        }
        return false;
    }
};