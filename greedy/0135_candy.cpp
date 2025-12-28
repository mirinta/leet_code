#include <numeric>
#include <vector>

/**
 * There are n children standing in a line. Each child is assigned a rating value given in the
 * integer array ratings.
 *
 * You are giving candies to these children subjected to the following requirements:
 *
 * - Each child must have at least one candy.
 *
 * - Children with a higher rating get more candies than their neighbors.
 *
 * Return the minimum number of candies you need to have to distribute the candies to the children.
 *
 * ! n == ratings.length
 * ! 1 <= n <= 2 * 10^4
 * ! 0 <= ratings[i] <= 2 * 10^4
 */

class Solution {
public:
    int candy(std::vector<int>& ratings)
    {
        const int n = ratings.size();
        std::vector<int> candies(n, 1);
        // step1: assign candies to the ith child according to his left neighbour
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }
        // step2: assign candies to the ith child according to his right neighbour
        // why not iterate forward?
        // assume:
        // indices: 0 1 2
        // ratings: 2 2 1
        // after step1: candies = [1,1,1]
        // if we iterate forward and check the right neighbour of the ith child:
        // candies = [1,2,1], because the condition is satisfied when we are at ratings[1]
        // ratings[0] is the same as ratings[1], but it is not updated
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = std::max(candies[i], candies[i + 1] + 1);
            }
        }
        return std::accumulate(candies.begin(), candies.end(), 0);
    }
};
