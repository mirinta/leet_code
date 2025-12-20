#include <string>
#include <vector>

/**
 * You are given an array of n strings strs, all of the same length.
 *
 * The strings can be arranged such that there is one on each line, making a grid.
 *
 * - For example, strs = ["abc", "bce", "cae"] can be arranged as follows:
 *     abc
 *     bce
 *     cae
 *
 * You want to delete the columns that are not sorted lexicographically. In the above example
 * (0-indexed), columns 0 ('a', 'b', 'c') and 2 ('c', 'e', 'e') are sorted, while column 1 ('b',
 * 'c', 'a') is not, so you would delete column 1.
 *
 * Return the number of columns that you will delete.
 *
 * ! n == strs.length
 * ! 1 <= n <= 100
 * ! 1 <= strs[i].length <= 1000
 * ! strs[i] consists of lowercase English letters.
 */

class Solution
{
public:
    int minDeletionSize(std::vector<std::string>& strs)
    {
        const int m = strs.size();
        const int n = strs[0].size();
        int result = 0;
        for (int col = 0; col < n; ++col) {
            bool isSorted = true;
            for (int row = 1; row < m; ++row) {
                if (strs[row][col] < strs[row - 1][col]) {
                    isSorted = false;
                    break;
                }
            }
            result += !isSorted;
        }
        return result;
    }
};