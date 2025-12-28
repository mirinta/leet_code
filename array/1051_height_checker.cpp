#include <algorithm>
#include <vector>

/**
 * A school is tying to take an annual photo of all the students. The students are asked to stand
 * in a single file line in non-decreasing order by height. Let this ordering be represented by the
 * integer array "expected" where expected[i] is the expected height of the ith student in line.
 *
 * You are given an integer array "heights" representing the current order that the students are
 * standing in. Each heights[i] is the height of the ith student in line (0-indexed).
 *
 * Return the number of indicies where heights[i] != expected[i]
 */

class Solution {
public:
    int heightChecker(const std::vector<int>& heights)
    {
        if (heights.size() < 2)
            return 0;

        std::vector<int> copy(heights);
        std::sort(copy.begin(), copy.end());
        int count = 0;
        for (size_t i = 0; i < heights.size(); ++i) {
            if (heights[i] != copy[i]) {
                count++;
            }
        }
        return count;
    }
};