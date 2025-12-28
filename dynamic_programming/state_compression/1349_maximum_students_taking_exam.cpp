#include <algorithm>
#include <unordered_set>
#include <vector>

/**
 * Given a m * n matrix seats  that represent seats distributions in a classroom. If a seat is
 * broken, it is denoted by '#' character otherwise it is denoted by a '.' character.
 *
 * Students can see the answers of those sitting next to the left, right, upper left and upper
 * right, but he cannot see the answers of the student sitting directly in front or behind him.
 * Return the maximum number of students that can take the exam together without any cheating being
 * possible.
 *
 * Students must be placed in seats in good condition.
 *
 * ! seats contains only characters '.' and'#'.
 * ! m == seats.length
 * ! n == seats[i].length
 * ! 1 <= m <= 8
 * ! 1 <= n <= 8
 */

class Solution {
public:
    int maxStudents(std::vector<std::vector<char>>& seats)
    {
        return approach2(seats);
    }

private:
    int approach2(std::vector<std::vector<char>>& seats)
    {
        // DP with space optimization: 1D-DP + hash_set
        const int m = seats.size();
        const int n = seats[0].size();
        const unsigned maxState = 1 << n;
        std::vector<int> dp(maxState, 0);
        std::vector<int> iMinus1(maxState, 0);
        std::unordered_set<int> prevStates;
        std::unordered_set<int> currStates;
        for (unsigned state = 0; state < maxState; ++state) {
            if (isValid(state, seats[0])) {
                iMinus1[state] = binaryOnes(state);
                prevStates.insert(state);
            }
        }
        for (int i = 1; i < m; ++i) {
            currStates.clear();
            for (unsigned current = 0; current < maxState; ++current) {
                if (!isValid(current, seats[i]))
                    continue;

                dp[current] = 0;
                const int ones = binaryOnes(current);
                for (const auto& previous : prevStates) {
                    if (!isValid(previous, seats[i - 1]) || isCheatingPossible(previous, current, n))
                        continue;

                    currStates.insert(current);
                    dp[current] = std::max(dp[current], iMinus1[previous] + ones);
                }
            }
            iMinus1 = dp;
            prevStates = currStates;
        }
        return *std::max_element(dp.begin(), dp.end());
    }

    int approach1(std::vector<std::vector<char>>& seats)
    {
        const int m = seats.size();
        const int n = seats[0].size(); // constraints: 1 <= m, n <= 8
        // dp[i][j] = max students within the first i rows, and the state of the ith row is j
        const unsigned maxState = 1 << n;
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(maxState, 0));
        for (unsigned state = 0; state < maxState; ++state) {
            if (isValid(state, seats[0])) {
                dp[1][state] = binaryOnes(state);
            }
        }
        for (int i = 2; i <= m; ++i) {
            for (unsigned current = 0; current < maxState; ++current) {
                if (!isValid(current, seats[i - 1]))
                    continue;

                for (unsigned previous = 0; previous < maxState; ++previous) {
                    if (!isValid(previous, seats[i - 2]) || isCheatingPossible(previous, current, n))
                        continue;

                    dp[i][current] = std::max(dp[i][current], dp[i - 1][previous] + binaryOnes(current));
                }
            }
        }
        return *std::max_element(dp[m].begin(), dp[m].end());
    }

    // helper functions:
    std::vector<unsigned> binaryForm(unsigned val, int numOfBits)
    {
        std::vector<unsigned> result(numOfBits, 0);
        for (int i = result.size() - 1; i >= 0; --i) {
            result[i] = val & 1 ? 1 : 0;
            val >>= 1;
        }
        return result;
    }

    bool isValid(unsigned state, const std::vector<char>& seats)
    {
        const std::vector<unsigned> bits = binaryForm(state, seats.size());
        for (int i = 0; i < seats.size(); ++i) {
            if (bits[i] == 1 && seats[i] == '#')
                return false;

            if (bits[i] == 1 && i >= 1 && bits[i - 1] == 1)
                return false;
        }
        return true;
    }

    bool isCheatingPossible(unsigned prevRow, unsigned currRow, int numOfBits)
    {
        const std::vector<unsigned> prevBits = binaryForm(prevRow, numOfBits);
        const std::vector<unsigned> currBits = binaryForm(currRow, numOfBits);
        for (int i = 0; i < numOfBits; ++i) {
            if (currBits[i] == 1 && i - 1 >= 0 && prevBits[i - 1] == 1)
                return true;

            if (currBits[i] == 1 && i + 1 < numOfBits && prevBits[i + 1] == 1)
                return true;
        }
        return false;
    }

    int binaryOnes(unsigned val)
    {
        int result = 0;
        while (val) {
            result++;
            val &= (val - 1);
        }
        return result;
    }
};