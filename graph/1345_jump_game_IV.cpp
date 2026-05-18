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
        static constexpr std::array<int, 2> directions{-1, 1};
        const int n = arr.size();
        std::unordered_map<int, std::vector<int>> map;
        for (int i = 0; i < n; ++i) {
            map[arr[i]].push_back(i);
        }
        std::queue<int> queue;
        queue.emplace(0);
        std::vector<bool> visited(n, false);
        visited[0] = true;
        int result = 0;
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto curr = queue.front();
                queue.pop();
                if (curr == n - 1)
                    return result;

                for (const auto& d : directions) {
                    const int next = curr + d;
                    if (next < 0 || next >= n || visited[next])
                        continue;

                    visited[next] = true;
                    queue.emplace(next);
                }
                if (!map.count(arr[curr]))
                    continue;

                for (const auto& next : map[arr[curr]]) {
                    if (next == curr || visited[next])
                        continue;

                    visited[next] = true;
                    queue.emplace(next);
                }
                map.erase(arr[curr]); // IMPORTANT!
            }
            result++;
        }
        return -1;
    }
};