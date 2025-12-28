#include <unordered_map>
#include <vector>

/**
 * You are visiting a farm that has a single row of fruit trees arranged from left to right. The
 * trees are represented by an integer array fruits where fruits[i] is the type of fruit the ith
 * tree produces.
 *
 * You want to collect as much fruit as possible. However, the owner has some strict rules that you
 * must follow:
 *
 * - You only have two baskets, and each basket can only hold a single type of fruit. There is no
 * limit on the amount of fruit each basket can hold.
 *
 * - Starting from any tree of your choice, you must pick exactly one fruit from every tree
 * (including the start tree) while moving to the right. The picked fruits must fit in one of your
 * baskets.
 *
 * - Once you reach a tree with fruit that cannot fit in your baskets, you must stop.
 *
 * Given the integer array fruits, return the maximum number of fruits you can pick.
 *
 * ! 1 <= fruits.length <= 10^5
 * ! 0 <= fruits[i] < fruits.length
 */

class Solution {
public:
    int totalFruit(std::vector<int>& fruits)
    {
        const int n = fruits.size();
        std::unordered_map<int, int> map;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            map[fruits[right]]++;
            while (map.size() > 2) {
                if (--map[fruits[left]] == 0) {
                    map.erase(fruits[left]);
                }
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};