#include <algorithm>
#include <numeric>
#include <vector>

/**
 * You are given an integer array cookies, where cookies[i] denotes the number of cookies in the ith
 * bag. You are also given an integer k that denotes the number of children to distribute all the
 * bags of cookies to. All the cookies in the same bag must go to the same child and cannot be split
 * up.
 *
 * The unfairness of a distribution is defined as the maximum total cookies obtained by a single
 * child in the distribution.
 *
 * Return the minimum unfairness of all distributions.
 *
 * ! 2 <= cookies.length <= 8
 * ! 1 <= cookies[i] <= 10^5
 * ! 2 <= k <= cookies.length
 */

class Solution {
public:
    int distributeCookies(std::vector<int>& cookies, int k)
    {
        return approach2(cookies, k);
    }

private:
    int result = INT_MAX;
    std::vector<int> distribution; // distribution[i] = num of cookies the ith child has

    // Binary search + Backtracking
    int approach2(std::vector<int>& cookies, int k)
    {
        // find a limit L such that each child has at most L cookies
        // - L is the unfairness of a distribution
        // - our goal is to find the min value of L
        int lo = *std::min_element(cookies.begin(), cookies.end());
        int hi = std::accumulate(cookies.begin(), cookies.end(), 0);
        distribution.resize(k);
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            std::fill(distribution.begin(), distribution.end(), 0);
            if (canDistribute(0, mid, cookies, k)) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

    bool canDistribute(int bagID, int limit, const std::vector<int>& cookies, int k)
    {
        if (bagID == cookies.size())
            return true;

        for (int i = 0; i < k; ++i) {
            if (distribution[i] + cookies[bagID] > limit)
                continue; // this bag can be given to the child_i

            distribution[i] += cookies[bagID];
            // try to distribute the next bag of cookies
            if (canDistribute(bagID + 1, limit, cookies, k))
                return true;

            distribution[i] -= cookies[bagID];
        }
        return false;
    }

    // Backtracking
    int approach1(std::vector<int>& cookies, int k)
    {
        // the ith bag of cookies can be given to the jth child
        // - i = 1, ..., n, and j = 1, ..., k
        // - there are std::pow(k, n) distributions!
        distribution.resize(k);
        std::fill(distribution.begin(), distribution.end(), 0);
        backtrack(0, cookies, k);
        return result;
    }

    void backtrack(int bagID, const std::vector<int>& cookies, int k)
    {
        if (bagID == cookies.size()) {
            result = std::min(result, *std::max_element(distribution.begin(), distribution.end()));
            return;
        }
        for (int i = 0; i < k; ++i) {
            distribution[i] += cookies[bagID];
            backtrack(bagID + 1, cookies, k);
            distribution[i] -= cookies[bagID];
        }
    }
};