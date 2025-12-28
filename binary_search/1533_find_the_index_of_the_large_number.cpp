/**
 * This is the ArrayReader's API interface.
 *
 * You should not implement it, or speculate about its implementation
 */
class ArrayReader {
public:
    // Compares the sum of arr[l..r] with the sum of arr[x..y]
    // return 1 if sum(arr[l..r]) > sum(arr[x..y])
    // return 0 if sum(arr[l..r]) == sum(arr[x..y])
    // return -1 if sum(arr[l..r]) < sum(arr[x..y])
    int compareSub(int l, int r, int x, int y);

    // Returns the length of the array
    int length();
};

/**
 * We have an integer array arr, where all the integers in arr are equal except for one integer
 * which is larger than the rest of the integers. You will not be given direct access to the array,
 * instead, you will have an API ArrayReader which have the following functions:
 *
 * 1. int compareSub(int l, int r, int x, int y): where 0 <= l, r, x, y < ArrayReader.length(), l <=
 * r and x <= y. The function compares the sum of sub-array arr[l..r] with the sum of the sub-array
 * arr[x..y] and returns:
 *
 * - 1 if arr[l]+arr[l+1]+...+arr[r] > arr[x]+arr[x+1]+...+arr[y].
 *
 * - 0 if arr[l]+arr[l+1]+...+arr[r] == arr[x]+arr[x+1]+...+arr[y].
 *
 * - -1 if arr[l]+arr[l+1]+...+arr[r] < arr[x]+arr[x+1]+...+arr[y].
 *
 * 2. int length(): Returns the size of the array.
 *
 * You are allowed to call compareSub() 20 times at most. You can assume both functions work in O(1)
 * time.
 *
 * Return the index of the array arr which has the largest integer.
 *
 * ! 2 <= arr.length <= 5 * 10^5
 * ! 1 <= arr[i] <= 100
 * ! All elements of arr are equal except for one element which is larger than all other elements.
 */

class Solution {
public:
    int getIndex(ArrayReader& reader)
    {
        // assume L is the length of the array
        // split it into two parts with the same size:
        // - even length, [left...mid][mid+1...right]
        // - odd length, [left...mid-1]mid[mid+1...right]
        const int n = reader.length();
        int left = 0;
        int right = n - 1;
        while (left < right) {
            const int mid = left + (right - left) / 2;
            const int leftEnd = (right - left + 1) % 2 == 0 ? mid : mid - 1;
            const int rightStart = mid + 1;
            const int compare = reader.compareSub(left, leftEnd, rightStart, right);
            if (compare == 0)
                return mid;

            if (compare > 0) {
                right = leftEnd;
            } else {
                left = rightStart;
            }
        }
        return left;
    }
};