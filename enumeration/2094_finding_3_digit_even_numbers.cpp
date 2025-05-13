#include <array>
#include <vector>

/**
 * You are given an integer array digits, where each element is a digit. The array may contain
 * duplicates.
 *
 * You need to find all the unique integers that follow the given requirements:
 *
 * - The integer consists of the concatenation of three elements from digits in any arbitrary order.
 *
 * - The integer does not have leading zeros.
 *
 * - The integer is even.
 *
 * For example, if the given digits were [1, 2, 3], integers 132 and 312 follow the requirements.
 *
 * Return a sorted array of the unique integers.
 *
 * ! 3 <= digits.length <= 100
 * ! 0 <= digits[i] <= 9
 */

class Solution
{
public:
    std::vector<int> findEvenNumbers(std::vector<int>& digits)
    {
        std::array<int, 10> count{};
        for (const auto& d : digits) {
            count[d]++;
        }
        std::vector<int> result;
        for (int val = 100; val <= 998; val += 2) {
            const int d1 = val / 100;
            const int d2 = val / 10 % 10;
            const int d3 = val % 10;
            count[d1]--;
            count[d2]--;
            count[d3]--;
            if (count[d1] >= 0 && count[d2] >= 0 && count[d3] >= 0) {
                result.push_back(val);
            }
            count[d1]++;
            count[d2]++;
            count[d3]++;
        }
        return result;
    }
};
