#include <algorithm>
#include <vector>

/**
 * You are given a 2D array of integers "envelopes" where "envelopes[i] = [wi, hi]" represents the
 * width and the height of an envelope.
 *
 * One envelope can fit into another if and only if both the width and the height of one envelope
 * are greater than the other envelope's width and height.
 *
 * Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).
 *
 * Note: you cannot rotate an envelope.
 *
 * ! 1 <= envelopes.length <= 10^5
 * ! envelopes[i].length == 2
 * ! 1 <= wi, hi <= 10^5
 */

class Solution {
public:
    int maxEnvelopes(std::vector<std::vector<int>>& envelopes)
    {
        // sort by width in increasing order:
        // width  height
        // 2      1
        // 5      2
        // 6      3
        // 6      4
        // 6      7
        // the length of longest LIS of heights = 6, it is wrong
        // if two envelopes have the same width,
        // we need to sort them by height in decreasing order
        std::sort(envelopes.begin(), envelopes.end(), [](const auto& v1, const auto& v2) {
            if (v1[0] == v2[0])
                return v1[1] > v2[1];

            return v1[0] < v2[0];
        });
        // then, it is the same as the original LIS problem (LC.300)
        std::vector<int> vec; // strictly increasing
        for (const auto& envelope : envelopes) {
            const auto& height = envelope[1];
            if (vec.empty() || height > vec.back()) {
                vec.push_back(height);
            } else {
                auto iter = std::lower_bound(vec.begin(), vec.end(), height);
                *iter = height;
            }
        }
        return vec.size();
    }
};
