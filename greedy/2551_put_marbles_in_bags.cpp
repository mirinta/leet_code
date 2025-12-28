#include <algorithm>
#include <vector>

/**
 * You have k bags. You are given a 0-indexed integer array weights where weights[i] is the weight
 * of the ith marble. You are also given the integer k.
 *
 * Divide the marbles into the k bags according to the following rules:
 *
 * - No bag is empty.
 *
 * - If the ith marble and jth marble are in a bag, then all marbles with an index between the ith
 * and jth indices should also be in that same bag.
 *
 * - If a bag consists of all the marbles with an index from i to j inclusively, then the cost of
 * the bag is weights[i] + weights[j].
 *
 * The score after distributing the marbles is the sum of the costs of all the k bags.
 *
 * Return the difference between the maximum and minimum scores among marble distributions.
 *
 * ! 1 <= k <= weights.length <= 10^5
 * ! 1 <= weights[i] <= 10^9
 */

class Solution {
public:
    long long putMarbles(std::vector<int>& weights, int k)
    {
        // for any partition: [0:i1] [i1+1:i2] [i2+1:i3] ... [ik-1+1:n-1]
        // score = nums[0] + nums[i1] + nums[i1+1] + nums[i2] + ... + nums[ik-1+1] + nums[n-1]
        //
        // to calculate the difference of two scores: nums[0] and nums[n-1] can be ignored
        //
        // diff = (nums[i1] + nums[i1+1]) + ... + (nums[ik-1] + nums[ik-1+1])
        //      = k-1 adjacent sums
        //
        // answer = greatest k-1 adjacent sums - smallest k-1 adjacent sums
        const int n = weights.size();
        std::vector<long long> adjacentSums(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            adjacentSums[i] = weights[i] + weights[i + 1];
        }
        std::sort(adjacentSums.begin(), adjacentSums.end());
        long long result = 0;
        for (int i = 0; i < k - 1; ++i) {
            result += adjacentSums[adjacentSums.size() - 1 - i] - adjacentSums[i];
        }
        return result;
    }
};
