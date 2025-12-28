#include <algorithm>
#include <vector>

/**
 * In the universe Earth C-137, Rick discovered a special form of magnetic force between two balls
 * if they are put in his new invented basket. Rick has n empty baskets, the ith basket is at
 * position[i], Morty has m balls and needs to distribute the balls into the baskets such that the
 * minimum magnetic force between any two balls is maximum.
 *
 * Rick stated that magnetic force between two different balls at positions x and y is |x - y|.
 *
 * Given the integer array position and the integer m. Return the required force.
 *
 * ! n == position.length
 * ! 2 <= n <= 10^5
 * ! 1 <= position[i] <= 10^9
 * ! All integers in position are distinct.
 * ! 2 <= m <= position.length
 */

class Solution {
public:
    int maxDistance(std::vector<int>& position, int m)
    {
        std::sort(position.begin(), position.end());
        int lo = 1; // position[i] are distinct
        int hi = position.back() - position.front();
        while (lo < hi) {
            const int mid = hi - (hi - lo) / 2;
            if (isValid(mid, position, m)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return hi;
    }

private:
    // check if it is possible to distribute x balls such that
    // min magnetic force >= min and x = m
    bool isValid(int min, const std::vector<int>& position, int m)
    {
        const int n = position.size();
        int count = 1;
        for (int i = 1, last = 0; i < n; ++i) {
            if (position[i] - position[last] >= min) {
                count++;
                last = i;
            }
            if (count >= m)
                return true;
        }
        return false;
    }
};