#include <vector>

/**
 * You are given an array of characters "letters" that is sorted in non-decreasing order, and a
 * character "target". There are at least two different characters in "letters".
 *
 * Return the smallest character in "letters" that is lexicographically greater than "target". If
 * such a character does not exist, return the first character in "letters".
 *
 * ! 2 <= letters.length <= 10^4
 * ! letters[i] is a lowercase English letter.
 * ! letters is sorted in non-decreasing order.
 * ! letters contains at least two different characters.
 * ! target is a lowercase English letter.
 */

class Solution {
public:
    char nextGreatestLetter(const std::vector<char>& letters, char target)
    {
        int lo = 0;
        int hi = letters.size() - 1;
        int mid = 0;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (letters[mid] <= target) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        } // the loop is terminated when lo = hi + 1
        return lo == letters.size() ? letters[0] : letters[lo];
    }
};