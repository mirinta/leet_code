#include <algorithm>
#include <cmath>
#include <vector>

/**
 * Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The
 * guards have gone and will come back in h hours.
 *
 * Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of
 * bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of
 * them instead and will not eat any more bananas during this hour.
 *
 * Koko likes to eat slowly but still wants to finish eating all the bananas before the guards
 * return.
 *
 * Return the minimum integer k such that she can eat all the bananas within h hours.
 *
 * ! 1 <= piles.length <= 10^4
 * ! piles.length <= h <= 10^9
 * ! 1 <= piles[i] <= 10^9
 */

class Solution {
public:
    int minEatingSpeed(std::vector<int>& piles, int h)
    {
        // constraints: piles.length <= h
        // the problem must have a solution
        int min = 1;
        int max = *std::max_element(piles.begin(), piles.end());
        while (min < max) {
            const int speed = min + (max - min) / 2;
            if (isValid(speed, piles, h)) {
                max = speed;
            } else {
                min = speed + 1;
            }
        }
        return min;
    }

private:
    bool isValid(int speed, const std::vector<int>& piles, int h)
    {
        int time = 0;
        for (const auto& val : piles) {
            time += std::ceil(val * 1.0 / speed);
            if (time > h)
                return false;
        }
        return true;
    }
};