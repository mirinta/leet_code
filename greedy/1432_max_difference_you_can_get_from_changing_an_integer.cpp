#include <algorithm>
#include <string>

/**
 * You are given an integer num. You will apply the following steps to num two separate times:
 *
 * - Pick a digit x (0 <= x <= 9).
 *
 * - Pick another digit y (0 <= y <= 9). Note y can be equal to x.
 *
 * - Replace all the occurrences of x in the decimal representation of num by y.
 *
 * Let a and b be the two results from applying the operation to num independently.
 *
 * Return the max difference between a and b.
 *
 * Note that neither a nor b may have any leading zeros, and must not be 0.
 *
 * ! 1 <= num <= 10^8
 */

class Solution {
public:
    int maxDiff(int num)
    {
        return findMax(num) - findMin(num);
    }

private:
    int findMax(int num)
    {
        std::string result = std::to_string(num);
        auto pos = result.find_first_not_of('9');
        if (pos != std::string::npos) {
            const char c = result[pos];
            std::replace(result.begin(), result.end(), c, '9');
        }
        return std::stoi(result);
    }

    int findMin(int num)
    {
        std::string result = std::to_string(num);
        char from = '0';
        char to = '0';
        if (result[0] != '1') {
            from = result[0];
            to = '1';
        } else {
            for (int i = 1; i < result.size(); ++i) {
                if (result[i] != '0' && result[i] != result[0]) {
                    from = result[i];
                    to = '0';
                    break;
                }
            }
        }
        std::replace(result.begin(), result.end(), from, to);
        return std::stoi(result);
    }
};