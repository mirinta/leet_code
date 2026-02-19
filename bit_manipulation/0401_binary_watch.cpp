#include <string>
#include <vector>

/**
 * A binary watch has 4 LEDs on the top to represent the hours (0-11), and 6 LEDs on the bottom to represent the
 * minutes (0-59). Each LED represents a zero or one, with the least significant bit on the right.
 *
 * - For example, the below binary watch reads "4:51".
 *
 * Given an integer turnedOn which represents the number of LEDs that are currently on (ignoring the PM), return all
 * possible times the watch could represent. You may return the answer in any order.
 *
 * The hour must not contain a leading zero.
 *
 * - For example, "01:00" is not valid. It should be "1:00".
 *
 * The minute must consist of two digits and may contain a leading zero.
 *
 * - For example, "10:2" is not valid. It should be "10:02".
 *
 * ! 0 <= turnedOn <= 10
 */

class Solution {
public:
    std::vector<std::string> readBinaryWatch(int turnedOn)
    {
        std::vector<std::string> result;
        for (int i = 0; i < 1024; ++i) {
            const int h = i >> 6;
            const int m = i & 63;
            if (h > 11 || m > 59)
                continue;

            if (setbits(h) + setbits(m) != turnedOn)
                continue;

            result.push_back(std::to_string(h) + ":" + (m < 10 ? "0" + std::to_string(m) : std::to_string(m)));
        }
        return result;
    }

private:
    int setbits(int n)
    {
        int result = 0;
        while (n) {
            result++;
            n &= n - 1;
        }
        return result;
    }
};