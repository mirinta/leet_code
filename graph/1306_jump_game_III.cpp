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
        // our goal is to reach any "destination" such that arr[destination] = 0
        const int n = arr.size();
        std::vector<bool> visited(n, false);
        visited[start] = true;
        std::queue<int> queue;
        queue.push(start);
        while (!queue.empty()) {
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const int index = queue.front();
                queue.pop();
                if (arr[index] == 0)
                    return true;

                for (const auto& factor : kFactors) {
                    const int x = index + factor * arr[index];
                    if (x < 0 || x >= n)
                        continue;

                    if (!visited[x]) {
                        visited[x] = true;
                        queue.push(x);
                    }
                }
            }
        }
        return false;
    }

private:
    static const std::array<int, 2> kFactors;
};

const std::array<int, 2> Solution::kFactors{-1, 1};