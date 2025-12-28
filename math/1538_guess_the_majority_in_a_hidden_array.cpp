/**
 * This is the ArrayReader's API interface.
 * You should not implement it, or speculate about its implementation
 */
class ArrayReader {
public:
    // Compares 4 different elements in the array
    // return 4 if the values of the 4 elements are the same (0 or 1).
    // return 2 if three elements have a value equal to 0 and one element has value equal to 1 or
    // vice versa. return 0 : if two element have a value equal to 0 and two elements have a value
    // equal to 1.
    int query(int a, int b, int c, int d);

    // Returns the length of the array
    int length();
};

/**
 * We have an integer array nums, where all the integers in nums are 0 or 1. You will not be given
 * direct access to the array, instead, you will have an API ArrayReader which have the following
 * functions:
 *
 * - int query(int a, int b, int c, int d): where 0 <= a < b < c < d < ArrayReader.length(). The
 * function returns the distribution of the value of the 4 elements and returns:
 *
 * 4 : if the values of the 4 elements are the same (0 or 1).
 * 2 : if three elements have a value equal to 0 and one element has value equal to 1 or vice versa.
 * 0 : if two element have a value equal to 0 and two elements have a value equal to 1.
 *
 * - int length(): Returns the size of the array.
 *
 * You are allowed to call query() 2 * n times at most where n is equal to ArrayReader.length().
 *
 * Return any index of the most frequent value in nums, in case of tie, return -1.
 *
 * ! 5 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 1
 */

class Solution {
public:
    int guessMajority(ArrayReader& reader)
    {
        const int n = reader.length();
        // if query(0,1,2,3) == query(1,2,3,i)
        // then nums[0] = nums[i], i >= 4
        int same = 1;     // num of elements == nums[0]
        int diff = 0;     // num of elements != nums[0]
        int diffIdx = -1; // nums[diffIdx] != nums[0]
        const int q = reader.query(0, 1, 2, 3);
        for (int i = 4; i < n; ++i) {
            if (q == reader.query(1, 2, 3, i)) {
                same++;
            } else {
                diff++;
                diffIdx = i;
            }
        }
        // check nums[0] and nums[1]
        if (reader.query(0, 2, 3, 4) == reader.query(1, 2, 3, 4)) {
            same++;
        } else {
            diff++;
            diffIdx = 1;
        }
        // check nums[0] and nums[2]
        if (reader.query(0, 1, 3, 4) == reader.query(1, 2, 3, 4)) {
            same++;
        } else {
            diff++;
            diffIdx = 2;
        }
        // check nums[0] and nums[3]
        if (reader.query(0, 1, 2, 4) == reader.query(1, 2, 3, 4)) {
            same++;
        } else {
            diff++;
            diffIdx = 3;
        }
        if (same > diff)
            return 0;

        return same < diff ? diffIdx : -1;
    }
};