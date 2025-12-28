#include <vector>

/**
 * You are given two arrays of integers, fruits and baskets, each of length n, where fruits[i]
 * represents the quantity of the ith type of fruit, and baskets[j] represents the capacity of the
 * jth basket.
 *
 * From left to right, place the fruits according to these rules:
 *
 * - Each fruit type must be placed in the leftmost available basket with a capacity greater than or
 * equal to the quantity of that fruit type.
 *
 * - Each basket can hold only one type of fruit.
 *
 * - If a fruit type cannot be placed in any basket, it remains unplaced.
 *
 * Return the number of fruit types that remain unplaced after all possible allocations are made.
 *
 * ! n == fruits.length == baskets.length
 * ! 1 <= n <= 100
 * ! 1 <= fruits[i], baskets[i] <= 1000
 */

class Solution {
public:
    int numOfUnplacedFruits(std::vector<int>& fruits, std::vector<int>& baskets)
    {
        const int n = baskets.size();
        std::vector<bool> used(n, false);
        int result = 0;
        for (const auto& quantity : fruits) {
            bool placed = false;
            for (int i = 0; i < n; ++i) {
                if (!used[i] && quantity <= baskets[i]) {
                    used[i] = true;
                    placed = true;
                    break;
                }
            }
            result += !placed;
        }
        return result;
    }
};
