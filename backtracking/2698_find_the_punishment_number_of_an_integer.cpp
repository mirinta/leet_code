#include <string>

/**
 * Given a positive integer n, return the punishment number of n.
 *
 * The punishment number of n is defined as the sum of the squares of all integers i such that:
 *
 * - 1 <= i <= n
 *
 * - The decimal representation of i * i can be partitioned into contiguous substrings such that the
 * sum of the integer values of these substrings equals i.
 *
 * ! 1 <= n <= 1000
 */

class Solution {
public:
    int punishmentNumber(int n)
    {
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            const int square = i * i;
            if (isValid(0, 0, std::to_string(square), i)) {
                result += square;
            }
        }
        return result;
    }

private:
    bool isValid(int i, int sum, const std::string& s, const int target)
    {
        if (i == s.size())
            return sum == target;

        // i X X X j X X X ... X
        // |<-num->|
        for (int j = i; j < s.size(); ++j) {
            if (isValid(j + 1, sum + std::stoi(s.substr(i, j - i + 1)), s, target))
                return true;
        }
        return false;
    }
};
