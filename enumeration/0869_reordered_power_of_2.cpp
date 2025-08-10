#include <algorithm>
#include <functional>
#include <string>
#include <vector>

/**
 * You are given an integer n. We reorder the digits in any order (including the original order)
 * such that the leading digit is not zero.
 *
 * Return true if and only if we can do this so that the resulting number is a power of two.
 *
 * ! 1 <= n <= 10^9
 */

class Solution
{
public:
    bool reorderedPowerOf2(int n) { return approach2(n); }

private:
    bool approach2(int n)
    {
        std::string sortedDigits = std::to_string(n);
        std::sort(sortedDigits.begin(), sortedDigits.end(), std::greater<>());
        const int max = std::stoi(sortedDigits);
        int num = 1;
        while (num <= max) {
            auto digits = std::to_string(num);
            num *= 2;
            if (digits.size() != sortedDigits.size())
                continue;

            std::sort(digits.begin(), digits.end(), std::greater<>());
            if (digits == sortedDigits)
                return true;
        }
        return false;
    }

    bool approach1(int n)
    {
        auto isPowerOf2 = [](int n) -> bool {
            if (n <= 0)
                return false;

            return (n & (n - 1)) == 0;
        };
        std::string digits = std::to_string(n);
        std::sort(digits.begin(), digits.end());
        std::vector<bool> visited(digits.size(), false);
        std::function<bool(int, int)> backtrack = [&](int i, int num) {
            if (i == digits.size())
                return isPowerOf2(num);

            for (int j = 0; j < digits.size(); ++j) {
                if (visited[j])
                    continue;

                if (j > 0 && digits[j] == digits[j - 1] && !visited[j - 1])
                    continue;

                if (i == 0 && digits[j] == '0')
                    continue;

                visited[j] = true;
                if (backtrack(i + 1, 10 * num + (digits[j] - '0')))
                    return true;

                visited[j] = false;
            }
            return false;
        };
        return backtrack(0, 0);
    }
};