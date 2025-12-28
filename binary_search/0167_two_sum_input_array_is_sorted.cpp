#include <vector>

/**
 * Given a 1-indexed array of integers "numbers" that is already sorted in non-decreasing order,
 * find two numbers such that they add up to a specific "target" number. Let these two numbers be
 * "numbers[index1]" and "numbers[index2]" where 1 <= index1 < index2 <= numbers.length.
 *
 * Return the indicies of the two numbers, "index1" and "index2", added by one as an integer array
 * "[index1, index2]" of length 2.
 *
 * The tests are generated such that there is exactly one solution.
 *
 * ! "numbers" is sorted in non-decreasing order.
 *
 * ! "index1" and "index2" are 1-indexed.
 *
 * ! You may not use the same element twice.
 *
 * ! Your solution must use only constant extra place.
 */

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& numbers, int target)
    {
        // the input array is sorted in non-decreasing order
        int left = 0;
        int right = numbers.size() - 1;
        while (left < right) {
            const int sum = numbers[left] + numbers[right];
            if (sum == target)
                return {left + 1, right + 1};

            if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        return {};
    }
};