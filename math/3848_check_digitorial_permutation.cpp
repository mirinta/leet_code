#include <algorithm>
#include <array>
#include <vector>

/**
 * You are given an integer n.
 *
 * A number is called digitorial if the sum of the factorials of its digits is equal to the number itself.
 *
 * Determine whether any permutation of n (including the original order) forms a digitorial number.
 *
 * Return true if such a permutation exists, otherwise return false.
 *
 * ! 1 <= n <= 10^9
 */

class Solution {
public:
    bool isDigitorialPermutation(int n)
    {
        if (n == 0)
            return false;

        static constexpr auto factorial = []() {
            std::array<int, 10> result{};
            result[0] = 1;
            result[1] = 1;
            for (int i = 2; i < result.size(); ++i) {
                result[i] = result[i - 1] * i;
            }
            return result;
        }();
        const int target = n;
        std::array<int, 10> count{};
        int sum = 0;
        while (n) {
            count[n % 10]++;
            sum += factorial[n % 10];
            n /= 10;
        }
        while (sum) {
            const int d = sum % 10;
            if (--count[sum % 10] < 0)
                return false;

            sum /= 10;
        }
        return std::all_of(count.begin(), count.end(), [](const auto& e) { return e == 0; });
    }
};