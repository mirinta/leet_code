/**
 * This is the ArrayReader's API interface.
 * You should not implement it, or speculate about its implementation
 */
class ArrayReader {
public:
    int get(int index) const;
};

/**
 * This is an interactive problem.
 *
 * You have a sorted array of unique elements and an unknown size. You do not have an access to the
 * array but you can use the ArrayReader interface to access it. You can call ArrayReader.get(i)
 * that:
 *
 * - returns the value at the ith index (0-indexed) of the secret array (i.e., secret[i]), or
 *
 * - returns 2^31 - 1 if the i is out of the boundary of the array.
 * You are also given an integer target.
 *
 * Return the index k of the hidden array where secret[k] == target or return -1 otherwise.
 *
 * You must write an algorithm with O(log n) runtime complexity.
 *
 * ! 1 <= secret.length <= 10^4
 * ! -10^4 <= secret[i], target <= 10^4
 * ! secret is sorted in a strictly increasing order.
 */

class Solution {
public:
    int search(const ArrayReader& reader, int target)
    {
        return approach2(reader, target);
    }

private:
    int approach1(const ArrayReader& reader, int target)
    {
        // find the boundary:
        int lo = 0;
        int hi = 1;
        while (reader.get(hi) < target) {
            lo = hi;
            hi *= 2;
        }
        // apply binary search:
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            const int val = reader.get(mid);
            if (val == target)
                return mid;

            if (val > target) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return -1;
    }

    int approach2(const ArrayReader& reader, int target)
    {
        // tricky:
        int lo = 0;
        int hi = 1e4 - 1; // the constraint tells us 1<=secret.length<=10^4
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            const int val = reader.get(mid);
            if (val == target)
                return mid;

            if (val > target) {
                // if mid is out of boundary,
                // then val = INT_MAX which is always larger than target
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return -1;
    }
};
