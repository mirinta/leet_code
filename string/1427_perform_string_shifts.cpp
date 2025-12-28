#include <string>
#include <vector>

/**
 * You are given a string s containing lowercase English letters, and a matrix shift, where shift[i]
 * = [directioni, amounti]:
 *
 * - directioni can be 0 (for left shift) or 1 (for right shift).
 *
 * - amounti is the amount by which string s is to be shifted.
 *
 * - A left shift by 1 means remove the first character of s and append it to the end.
 *
 * - Similarly, a right shift by 1 means remove the last character of s and add it to the beginning.
 *
 * Return the final string after all operations.
 *
 * ! 1 <= s.length <= 100
 * ! s only contains lower case English letters.
 * ! 1 <= shift.length <= 100
 * ! shift[i].length == 2
 * ! directioni is either 0 or 1.
 * ! 0 <= amounti <= 100
 */

class Solution {
public:
    std::string stringShift(std::string s, std::vector<std::vector<int>>& shift)
    {
        const int n = s.size();
        int offset = 0; // positive means shift right, negative means shift left
        for (const auto& info : shift) {
            if (info[0] == 0) {
                offset -= info[1];
            } else {
                offset += info[1];
            }
        }
        offset = offset > 0 ? offset % n : -1 * (-offset % n);
        if (offset == 0)
            return s;

        if (offset > 0)
            return s.substr(n - offset, offset) + s.substr(0, n - offset);

        return s.substr(-offset, n + offset) + s.substr(0, -offset);
    }
};
