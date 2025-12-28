/**
 * This is the MountainArray's API interface.
 *
 * You should not implement it, or speculate about its implementation.
 */
class MountainArray {
public:
    int get(int index);
    int length();
};

/**
 * (This problem is an interactive problem.)
 *
 * You may recall that an array arr is a mountain array if and only if:
 *
 * - arr.length >= 3
 *
 * - There exists some i with 0 < i < arr.length - 1 such that:
 *
 *   - arr[0] < arr[1] < ... < arr[i-1] < arr[i]
 *
 *   - arr[i] > arr[i + 1] > ... > arr[arr.length-1]
 *
 * Given a mountain array mountainArr, return the minimum index such that mountainArr.get(index) ==
 * target. If such an index does not exist, return -1.
 *
 * You cannot access the mountain array directly. You may only access the array using a
 * MountainArray interface:
 *
 * - MountainArray.get(k) returns the element of the array at index k (0-indexed).
 *
 * - MountainArray.length() returns the length of the array.
 *
 * Submissions making more than 100 calls to MountainArray.get will be judged Wrong Answer. Also,
 * any solutions that attempt to circumvent the judge will result in disqualification.
 *
 * ! 3 <= mountain_arr.length() <= 10^4
 * ! 0 <= target <= 10^9
 * ! 0 <= mountain_arr.get(index) <= 10^9
 */

class Solution {
public:
    int findInMountainArray(int target, MountainArray& mountainArr)
    {
        // 1. find the peak element
        const int n = mountainArr.length();
        int lo = 1;
        int hi = n - 2;
        int peak = -1;
        while (lo <= hi) {
            peak = lo + (hi - lo) / 2;
            const int leftVal = mountainArr.get(peak - 1);
            const int midVal = mountainArr.get(peak);
            const int rightVal = mountainArr.get(peak + 1);
            if (leftVal < midVal && midVal > rightVal)
                break;

            if (leftVal < midVal && midVal < rightVal) {
                lo = peak + 1;
            } else {
                hi = peak - 1;
            }
        }
        if (peak == -1)
            return -1;

        // 2. find target in the left part (ascending order)
        lo = 0;
        hi = peak;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            const int val = mountainArr.get(mid);
            if (val == target)
                return mid;

            if (val > target) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        // 3. find the target in the right part (descending order)
        lo = peak;
        hi = n - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            const int val = mountainArr.get(mid);
            if (val == target)
                return mid;

            if (val > target) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return -1;
    }
};
