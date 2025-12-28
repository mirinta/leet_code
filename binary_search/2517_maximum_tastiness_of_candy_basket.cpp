#include <algorithm>
#include <vector>

/**
 * You are given an array of positive integers price where price[i] denotes the price of the ith
 * candy and a positive integer k.
 *
 * The store sells baskets of k distinct candies. The tastiness of a candy basket is the smallest
 * absolute difference of the prices of any two candies in the basket.
 *
 * Return the maximum tastiness of a candy basket.
 *
 * ! 2 <= k <= price.length <= 10^5
 * ! 1 <= price[i] <= 10^9
 */

class Solution {
public:
    int maximumTastiness(std::vector<int>& price, int k)
    {
        std::sort(price.begin(), price.end());
        int lo = 0;
        int hi = price.back() - price.front();
        while (lo < hi) {
            const int mid = hi - (hi - lo) / 2;
            if (isValid(mid, price, k)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return hi;
    }

private:
    bool isValid(int minDiff, const std::vector<int>& price, int k)
    {
        const int n = price.size();
        int count = 1;
        for (int i = 1, last = 0; i < n; ++i) {
            if (price[i] - price[last] >= minDiff) {
                count++;
                last = i;
            }
            if (count >= k)
                return true;
        }
        return false;
    }
};