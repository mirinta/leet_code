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
        static const std::string s{"123456789"};
        std::vector<int> result;
        for (int L = std::to_string(low).size(); L <= std::to_string(high).size(); ++L) {
            for (int start = 0; start + L - 1 < s.size(); ++start) {
                const auto sub = s.substr(start, L);
                const auto val = std::stoi(sub);
                if (val >= low && val <= high) {
                    result.emplace_back(val);
                }
            }
        }
        return result;
    }
};