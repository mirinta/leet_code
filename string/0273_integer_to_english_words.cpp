#include <string>

/**
 * Convert a non-negative integer num to its English words representation.
 *
 * ! 0 <= num <= 2^31 - 1
 */

class Solution {
public:
    std::string numberToWords(int num)
    {
        if (num == 0)
            return "Zero";

        return solve(num);
    }

private:
    std::string solve(int num)
    {
        if (num < 10) {
            static const std::string words1[]{"",     "One", "Two",   "Three", "Four",
                                              "Five", "Six", "Seven", "Eight", "Nine"};
            return words1[num];
        }
        if (num < 20) {
            static const std::string words2[]{"Ten",     "Eleven",  "Twelve",    "Thirteen", "Fourteen",
                                              "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
            return words2[num - 10];
        }
        if (num < 100) {
            static const std::string words3[]{"",      "Ten",   "Twenty",  "Thirty", "Forty",
                                              "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
            return words3[num / 10] + (num % 10 ? " " : "") + solve(num % 10);
        }
        if (num < 1000)
            return solve(num / 100) + " Hundred" + (num % 100 ? " " : "") + solve(num % 100);

        if (num < 1000000)
            return solve(num / 1000) + " Thousand" + (num % 1000 ? " " : "") + solve(num % 1000);

        if (num < 1000000000)
            return solve(num / 1000000) + " Million" + (num % 1000000 ? " " : "") + solve(num % 1000000);

        return solve(num / 1000000000) + " Billion" + (num % 1000000000 ? " " : "") + solve(num % 1000000000);
    }
};