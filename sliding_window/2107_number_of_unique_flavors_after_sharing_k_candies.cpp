#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed integer array candies, where candies[i] represents the flavor of the
 * ith candy. Your mom wants you to share these candies with your little sister by giving her k
 * consecutive candies, but you want to keep as many flavors of candies as possible.
 *
 * Return the maximum number of unique flavors of candy you can keep after sharing with your sister.
 *
 * ! 1 <= candies.length <= 10^5
 * ! 1 <= candies[i] <= 10^5
 * ! 0 <= k <= candies.length
 */

class Solution {
public:
    int shareCandies(std::vector<int>& candies, int k)
    {
        const int n = candies.size();
        std::unordered_map<int, int> map;
        for (const auto& flavor : candies) {
            map[flavor]++;
        }
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            if (--map[candies[right]] == 0) {
                map.erase(candies[right]);
            }
            if (right - left + 1 > k) {
                map[candies[left]]++;
                left++;
            }
            if (right - left + 1 == k) {
                result = std::max<int>(result, map.size());
            }
        }
        return result;
    }
};