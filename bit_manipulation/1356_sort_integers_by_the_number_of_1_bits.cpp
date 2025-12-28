#include <algorithm>
#include <vector>

/**
 * You are given an integer array arr. Sort the integers in the array in ascending order by the
 * number of 1's in their binary representation and in case of two or more integers have the same
 * number of 1's you have to sort them in ascending order.
 *
 * Return the array after sorting it.
 *
 * ! 1 <= arr.length <= 500
 * ! 0 <= arr[i] <= 10^4
 */

class Solution {
public:
    std::vector<int> sortByBits(std::vector<int>& arr)
    {
        std::sort(arr.begin(), arr.end(), [this](const auto& val1, const auto& val2) {
            const auto count1 = binaryOnes(val1);
            const auto count2 = binaryOnes(val2);
            return count1 == count2 ? val1 < val2 : count1 < count2;
        });
        return arr;
    }

private:
    int binaryOnes(int n)
    {
        int count = 0;
        while (n) {
            count++;
            n &= (n - 1);
        }
        return count;
    }
};
