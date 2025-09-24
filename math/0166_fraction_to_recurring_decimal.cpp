#include <string>
#include <unordered_map>

/**
 * Given two integers representing the numerator and denominator of a fraction, return the fraction
 * in string format.
 *
 * If the fractional part is repeating, enclose the repeating part in parentheses.
 *
 * If multiple answers are possible, return any of them.
 *
 * It is guaranteed that the length of the answer string is less than 104 for all the given inputs.
 *
 * ! -2^31 <= numerator, denominator <= 2^31 - 1
 * ! denominator != 0
 */

class Solution
{
public:
    std::string fractionToDecimal(int numerator, int denominator)
    {
        if (numerator == 0)
            return "0";

        // y = ax + b, y/x = a + b/x
        const bool isNegative = numerator < 0 ^ denominator < 0;
        long long Y = std::abs(static_cast<long long>(numerator));
        long long X = std::abs(static_cast<long long>(denominator));
        std::string result;
        if (isNegative) {
            result.push_back('-');
        }
        result.append(std::to_string(Y / X));
        if (Y % X == 0)
            return result;

        result.push_back('.');
        std::unordered_map<std::string, int> map;
        Y = Y % X * 10;
        while (Y != 0) {
            const auto expr = std::to_string(Y) + "/" + std::to_string(X);
            if (map.count(expr)) {
                result.insert(result.begin() + map[expr], '(');
                result.push_back(')');
                break;
            }
            map[expr] = result.size();
            result.append(std::to_string(Y / X));
            Y = Y % X * 10;
        }
        return result;
    }
};
