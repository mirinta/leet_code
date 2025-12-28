#include <vector>

/**
 * You have a long flowerbed in which some of the plots are planted, and some are not. However,
 * flowers cannot be planted in adjacent plots.
 *
 * Given an integer array flowerbed containing 0's and 1's, where 0 means empty and 1 means not
 * empty, and an integer n, return true if n new flowers can be planted in the flowerbed without
 * violating the no-adjacent-flowers rule and false otherwise.
 *
 * ! 1 <= flowerbed.length <= 2 * 10^4
 * ! flowerbed[i] is 0 or 1.
 * ! There are no two adjacent flowers in flowerbed.
 * ! 0 <= n <= flowerbed.length
 */

class Solution {
public:
    bool canPlaceFlowers(std::vector<int>& flowerbed, int n)
    {
        if (n <= 0)
            return true;

        const int size = flowerbed.size();
        flowerbed.insert(flowerbed.begin(), 0);
        flowerbed.push_back(0);
        for (int i = 1; i <= size; ++i) {
            if (flowerbed[i] != 0)
                continue;

            if (flowerbed[i - 1] == 0 && flowerbed[i + 1] == 0) {
                flowerbed[i] = 1;
                n--;
                if (n == 0)
                    return true;
            }
        }
        return false;
    }
};