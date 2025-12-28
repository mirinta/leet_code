#include <vector>

/**
 * You are given a 0-indexed array mountain. Your task is to find all the peaks in the mountain
 * array.
 *
 * Return an array that consists of indices of peaks in the given array in any order.
 *
 * Notes:
 *
 * - A peak is defined as an element that is strictly greater than its neighboring elements.
 *
 * - The first and last elements of the array are not a peak.
 *
 * ! 3 <= mountain.length <= 100
 * ! 1 <= mountain[i] <= 100
 */

class Solution {
public:
    std::vector<int> findPeaks(std::vector<int>& mountain)
    {
        std::vector<int> result;
        for (int i = 1; i + 1 < mountain.size(); ++i) {
            if (mountain[i] > mountain[i - 1] && mountain[i] > mountain[i + 1]) {
                result.push_back(i);
            }
        }
        return result;
    }
};