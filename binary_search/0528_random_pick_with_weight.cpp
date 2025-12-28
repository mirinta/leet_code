#include <random>
#include <vector>

/**
 * You are given a 0-indexed array of positive integers "w" where "w[i]" describes the weight of the
 * "i"th index.
 *
 * You need to implement the function "pickIndex()", which randomly picks an index in the range "[0,
 * w.length - 1]" and returns it. The probability of picking an index "i" is "w[i] / sum(w)".
 *
 * Example:
 * If w = [1, 3], the probability of picking index "0" is 1 / (1 + 3) = 0.25, and the
 * probability of picking index "1" is 3 / (1 + 3) = 0.75.
 */

class Solution {
public:
    //    indices = [0, 1, 2]
    //    weights = [2, 3, 4]
    // prefix sum = [2, 5, 9]
    // generate a random number x in range [1, 9]:
    // - if x in [1, 2], pickIndex = 0
    // - if x in (2, 5], pickIndex = 1;
    // - if x in (5, 9], pickIndex = 2;
    Solution(std::vector<int>& w) : prefixSum(getPrefixSum(w)), engine(rd()), distrib(1, prefixSum.back()) {}

    int pickIndex()
    {
        const int x = distrib(engine);
        // find the first index of prefixSum s.t. prefixSum[index] >= x
        int lo = 0;
        int hi = prefixSum.size();
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (prefixSum[mid] < x) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return lo;
    }

private:
    static std::vector<int> getPrefixSum(const std::vector<int>& weights)
    {
        auto result = weights;
        for (int i = 1; i < result.size(); ++i) {
            result[i] = result[i - 1] + weights[i];
        }
        return result;
    }

private:
    std::vector<int> prefixSum;
    std::random_device rd;
    std::mt19937 engine;
    std::uniform_int_distribution<int> distrib;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */