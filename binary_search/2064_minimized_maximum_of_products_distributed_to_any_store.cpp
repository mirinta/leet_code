#include <algorithm>
#include <cmath>
#include <vector>

/**
 * You are given an integer n indicating there are n specialty retail stores. There are m product
 * types of varying amounts, which are given as a 0-indexed integer array quantities, where
 * quantities[i] represents the number of products of the ith product type.
 *
 * You need to distribute all products to the retail stores following these rules:
 *
 * A store can only be given at most one product type but can be given any amount of it.
 * After distribution, each store will have been given some number of products (possibly 0). Let x
 * represent the maximum number of products given to any store. You want x to be as small as
 * possible, i.e., you want to minimize the maximum number of products that are given to any store.
 * Return the minimum possible x.
 *
 * ! m == quantities.length
 * ! 1 <= m <= n <= 10^5
 * ! 1 <= quantities[i] <= 10^5
 */

class Solution {
public:
    int minimizedMaximum(int n, std::vector<int>& quantities)
    {
        int lo = 1;
        int hi = *std::max_element(quantities.begin(), quantities.end());
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, n, quantities)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

private:
    bool isValid(int max, int n, const std::vector<int>& quantities)
    {
        int sum = 0;
        for (const auto& val : quantities) {
            sum += std::ceil(val * 1.0 / max);
            if (sum > n)
                return false;
        }
        return true;
    }
};