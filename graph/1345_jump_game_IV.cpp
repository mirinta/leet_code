#include <array>
#include <queue>
#include <unordered_map>
#include <vector>

/**
 * Given an array of integers arr, you are initially positioned at the first index of the array.
 *
 * In one step you can jump from index i to index:
 *
 * - i + 1 where: i + 1 < arr.length.
 *
 * - i - 1 where: i - 1 >= 0.
 *
 * - j where: arr[i] == arr[j] and i != j.
 *
 * Return the minimum number of steps to reach the last index of the array.
 *
 * Notice that you can not jump outside of the array at any time.
 *
 * ! 1 <= arr.length <= 5 * 10^4
 * ! -10^8 <= arr[i] <= 10^8
 */

class Solution {
public:
    int minJumps(std::vector<int>& arr)
    {
        static const std::array<int, 2> kOffsets{-1, 1};
        const int n = arr.size();
        std::unordered_map<int, std::vector<int>> map;
        for (int i = 0; i < n; ++i) {
            map[arr[i]].push_back(i);
        }
        std::vector<bool> visited(n, false);
        visited[0] = true;
        std::queue<int> queue;
        queue.push(0);
        int steps = 0;
        while (!queue.empty()) {
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const int i = queue.front();
                queue.pop();
                if (i == n - 1)
                    return steps;

                for (const auto& offset : kOffsets) {
                    const int x = i + offset;
                    if (x < 0 || x >= n || visited[x])
                        continue;

                    visited[x] = true;
                    queue.push(x);
                }
                if (!map.count(arr[i]))
                    continue;

                for (const auto& j : map[arr[i]]) {
                    if (!visited[j]) {
                        visited[j] = true;
                        queue.push(j);
                    }
                }
                map.erase(arr[i]);
            }
            steps++;
        }
        return -1;
    }
};