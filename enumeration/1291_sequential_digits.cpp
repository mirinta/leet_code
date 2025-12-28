#include <string>
#include <vector>

/**
 * An integer has sequential digits if and only if each digit in the number is one more than the
 * previous digit.
 *
 * Return a sorted list of all the integers in the range [low, high] inclusive that have sequential
 * digits.
 *
 * ! 10 <= low <= high <= 10^9
 */

class Solution {
public:
    std::vector<int> sequentialDigits(int low, int high)
    {
        const std::string s("123456789");
        std::vector<int> result;
        for (int length = std::to_string(low).size(); length <= std::to_string(high).size(); ++length) {
            for (int i = 0; i + length - 1 < s.size(); ++i) {
                const int val = std::stoi(s.substr(i, length));
                if (inRange(val, low, high)) {
                    result.push_back(val);
                }
            }
        }
        return result;
    }

private:
    bool inRange(int val, int low, int high)
    {
        return low <= val && val <= high;
    }
};