#include <vector>

/**
 * You are given an integer array arr of length n that represents a permutation of the integers in
 * the range [0, n - 1].
 *
 * We split arr into some number of chunks (i.e., partitions), and individually sort each chunk.
 * After concatenating them, the result should equal the sorted array.
 *
 * Return the largest number of chunks we can make to sort the array.
 *
 * ! n == arr.length
 * ! 1 <= n <= 10
 * ! 0 <= arr[i] < n
 * ! All the elements of arr are unique.
 */

class Solution {
public:
    int maxChunksToSorted(std::vector<int>& arr)
    {
        const int n = arr.size();
        int result = 0;
        for (int i = 0, expectedSum = 0, realSum = 0; i < n; ++i) {
            expectedSum += i;
            realSum += arr[i];
            result += realSum == expectedSum;
        }
        return result;
    }
};