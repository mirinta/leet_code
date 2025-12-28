#include <string>

/**
 * You are given two strings start and target, both of length n. Each string consists only of the
 * characters 'L', 'R', and '_' where:
 *
 * - The characters 'L' and 'R' represent pieces, where a piece 'L' can move to the left only if
 * there is a blank space directly to its left, and a piece 'R' can move to the right only if there
 * is a blank space directly to its right.
 *
 * - The character '_' represents a blank space that can be occupied by any of the 'L' or 'R'
 * pieces.
 *
 * Return true if it is possible to obtain the string target by moving the pieces of the string
 * start any number of times. Otherwise, return false.
 *
 * ! n == start.length == target.length
 * ! 1 <= n <= 10^5
 * ! start and target consist of the characters 'L', 'R', and '_'.
 */

class Solution {
public:
    bool canChange(std::string& start, std::string& target)
    {
        const int n = start.size();
        int i = 0;
        int j = 0;
        while (i < n && j < n) {
            while (i < n && start[i] == '_') {
                i++;
            }
            while (j < n && target[j] == '_') {
                j++;
            }
            if (i == n || j == n)
                break;

            if (start[i] != target[j])
                return false;

            if (start[i] == 'L' && i < j)
                return false;

            if (start[i] == 'R' && i > j)
                return false;

            i++;
            j++;
        }
        while (i < n && start[i] == '_') {
            i++;
        }
        while (j < n && target[j] == '_') {
            j++;
        }
        return i == n && j == n;
    }
};