#include <queue>
#include <vector>

/**
 * You have n boxes labeled from 0 to n - 1. You are given four arrays: status, candies, keys, and
 * containedBoxes where:
 *
 * - status[i] is 1 if the ith box is open and 0 if the ith box is closed,
 *
 * - candies[i] is the number of candies in the ith box,
 *
 * - keys[i] is a list of the labels of the boxes you can open after opening the ith box.
 *
 * - containedBoxes[i] is a list of the boxes you found inside the ith box.
 *
 * You are given an integer array initialBoxes that contains the labels of the boxes you initially
 * have. You can take all the candies in any open box and you can use the keys in it to open new
 * boxes and you also can use the boxes you find in it.
 *
 * Return the maximum number of candies you can get following the rules above.
 *
 * ! n == status.length == candies.length == keys.length == containedBoxes.length
 * ! 1 <= n <= 1000
 * ! status[i] is either 0 or 1.
 * ! 1 <= candies[i] <= 1000
 * ! 0 <= keys[i].length <= n
 * ! 0 <= keys[i][j] < n
 * ! All values of keys[i] are unique.
 * ! 0 <= containedBoxes[i].length <= n
 * ! 0 <= containedBoxes[i][j] < n
 * ! All values of containedBoxes[i] are unique.
 * ! Each box is contained in one box at most.
 * ! 0 <= initialBoxes.length <= n
 * ! 0 <= initialBoxes[i] < n
 */

class Solution
{
public:
    int maxCandies(std::vector<int>& status, std::vector<int>& candies,
                   std::vector<std::vector<int>>& keys,
                   std::vector<std::vector<int>>& containedBoxes, std::vector<int>& initialBoxes)
    {
        const int n = status.size();
        std::queue<int> queue;
        for (const auto& i : initialBoxes) {
            queue.emplace(i);
        }
        bool run = true;
        int result = 0;
        while (run && !queue.empty()) {
            run = false;
            for (int k = queue.size(); k > 0; --k) {
                const auto curr = queue.front();
                queue.pop();
                if (!status[curr]) {
                    queue.emplace(curr);
                    continue;
                }
                if (candies[curr] == 0)
                    continue;

                result += candies[curr];
                candies[curr] = 0;
                for (const auto& box : keys[curr]) {
                    status[box] = 1;
                }
                for (const auto& box : containedBoxes[curr]) {
                    queue.emplace(box);
                }
                run = true;
            }
        }
        return result;
    }
};