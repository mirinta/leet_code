#include <array>
#include <climits>
#include <unordered_set>
#include <vector>

/**
 * Given an integer array "nums", return the third distinct maximum number in this array. If the
 * third maximum does not exist, return the maximum number.
 *
 * ! Can you find an O(1) solution?
 */

class Solution {
public:
    int thirdMax(const std::vector<int>& nums)
    {
        long long top1 = LLONG_MIN;
        long long top2 = LLONG_MIN;
        long long top3 = LLONG_MIN;
        for (const auto& val : nums) {
            if (val > top1) {
                top3 = top2;
                top2 = top1;
                top1 = val;
            } else if (val > top2 && val < top1) {
                top3 = top2;
                top2 = val;
            } else if (val > top3 && val < top2) {
                top3 = val;
            }
        }
        return top3 == LLONG_MIN ? top1 : top3;
    }
};