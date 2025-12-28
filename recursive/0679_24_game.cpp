#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <vector>

/**
 * You are given an integer array cards of length 4. You have four cards, each containing a number
 * in the range [1, 9]. You should arrange the numbers on these cards in a mathematical expression
 * using the operators ['+', '-', '*', '/'] and the parentheses '(' and ')' to get the value 24.
 *
 * You are restricted with the following rules:
 *
 * - The division operator '/' represents real division, not integer division.
 *
 *     - For example, 4 / (1 - 2 / 3) = 4 / (1 / 3) = 12.
 *
 * - Every operation done is between two numbers. In particular, we cannot use '-' as a unary
 * operator.
 *
 *     - For example, if cards = [1, 1, 1, 1], the expression "-1 - 1 - 1 - 1" is not allowed.
 *
 * - You cannot concatenate numbers together
 *
 *     - For example, if cards = [1, 2, 1, 2], the expression "12 + 12" is not valid.
 *
 * Return true if you can get such expression that evaluates to 24, and false otherwise.
 *
 * ! cards.length == 4
 * ! 1 <= cards[i] <= 9
 */

class Solution {
public:
    bool judgePoint24(std::vector<int>& cards)
    {
        const int n = cards.size();
        std::sort(cards.begin(), cards.end());
        std::vector<double> nums(cards.begin(), cards.end());
        while (std::next_permutation(nums.begin(), nums.end())) {
            const auto results = solve(0, n - 1, nums);
            for (const auto& v : results) {
                if (std::fabs(v - 24.0) < kEpsilon)
                    return true;
            }
        }
        return false;
    }

private:
    static constexpr double kEpsilon = 1e-8;

    // distinct results of expression[lo:hi]
    std::unordered_set<double> solve(int lo, int hi, const std::vector<double>& nums)
    {
        if (lo > hi)
            return {};

        if (lo == hi)
            return {nums[lo]};

        // lo x x x x x x x i i+1 x x x x x x hi
        // |<-expression1-->| |<-expression2-->|
        std::unordered_set<double> result;
        for (int split = lo; split < hi; ++split) {
            const auto results1 = solve(lo, split, nums);
            const auto results2 = solve(split + 1, hi, nums);
            for (const auto& v1 : results1) {
                for (const auto& v2 : results2) {
                    result.insert(v1 + v2);
                    result.insert(v1 - v2);
                    result.insert(v1 * v2);
                    if (std::fabs(v2) > kEpsilon) {
                        result.insert(v1 / v2);
                    }
                }
            }
        }
        return result;
    }
};
