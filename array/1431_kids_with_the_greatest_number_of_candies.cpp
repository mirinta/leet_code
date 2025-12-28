#include <vector>

/**
 * There are "n" kids with candies. You are given an integer array "candies", where each
 * "candies[i]" represents the number of candies the "ith" kid has, and an integer "extraCandies",
 * denoting the number of extra candies that you have.
 *
 *
 * Return a boolean array "result" of length "n", where "result[i]" is "true" if, after giving the
 * "ith" kid all the "extraCandies", they will have the greatest number of candies among all the
 * kids, or "false" otherwise.
 *
 * Note that multiple kids can have the greatest number of candies.
 */

class Solution {
public:
    std::vector<bool> kidsWithCandies(std::vector<int>& candies, int extraCandies)
    {
        if (candies.empty())
            return {};

        std::vector<bool> result(candies.size(), false);
        int maxValue = 0;
        for (const auto& candie : candies) {
            if (candie > maxValue) {
                maxValue = candie;
            }
        }
        for (size_t i = 0; i < candies.size(); ++i) {
            result[i] = extraCandies >= (maxValue - candies[i]);
        }
        return result;
    }
};
