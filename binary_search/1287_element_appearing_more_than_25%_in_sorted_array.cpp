#include <algorithm>
#include <vector>

/**
 * Given an integer array sorted in non-decreasing order, there is exactly one integer in the array
 * that occurs more than 25% of the time, return that integer.
 *
 *
 * ! 1 <= arr.length <= 10^4
 * ! 0 <= arr[i] <= 10^5
 */

class Solution {
public:
    int findSpecialInteger(std::vector<int>& arr)
    {
        return approach2(arr);
    }

private:
    // time O(logN), space O(1)
    int approach2(std::vector<int>& arr)
    {
        // if arr[i:j] is the target and its length > n/4,
        // it must overlap at least one of {index=n/4, index=n/2, index=3n/4}
        // X X i ... j X X
        //     |<--->|
        const int n = arr.size();
        for (const auto& val : {arr[n / 4], arr[n / 2], arr[3 * n / 4]}) {
            const int left = std::distance(arr.begin(), std::lower_bound(arr.begin(), arr.end(), val));
            const int right = std::distance(arr.begin(), std::prev(std::upper_bound(arr.begin(), arr.end(), val)));
            if (right - left + 1 > n / 4)
                return val;
        }
        return -1;
    }

    // time O(N), space O(1)
    int approach1(std::vector<int>& arr)
    {
        // if arr[i:j] is the target, then j-i+1 > n/4 => i+n/4 < j+1 => i+n/4 <= j
        // and the array is sorted, then arr[i] = arr[i+1] = ... = arr[j]
        // given arr[i], we know that arr[i] = arr[i + n/4]
        const int targetSize = arr.size() / 4;
        for (int i = 0; i + targetSize < arr.size(); ++i) {
            if (arr[i] == arr[i + targetSize])
                return arr[i];
        }
        return -1;
    }
};