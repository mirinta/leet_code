#include <algorithm>
#include <array>
#include <string>
#include <unordered_set>
#include <vector>

/**
 * You are given two positive integers n and k.
 *
 * An integer x is called k-palindromic if:
 *
 * - x is a palindrome.
 *
 * x is divisible by k.
 *
 * An integer is called good if its digits can be rearranged to form a k-palindromic integer. For
 * example, for k = 2, 2020 can be rearranged to form the k-palindromic integer 2002, whereas 1010
 * cannot be rearranged to form a k-palindromic integer.
 *
 * Return the count of good integers containing n digits.
 *
 * Note that any integer must not have leading zeros, neither before nor after rearrangement. For
 * example, 1010 cannot be rearranged to form 101.
 *
 * ! 1 <= n <= 10
 * ! 1 <= k <= 9
 */

class Solution
{
public:
    long long countGoodIntegers(int n, int k)
    {
        std::vector<int> factorial(n + 1);
        factorial[0] = 1;
        for (int i = 1; i <= n; ++i) {
            factorial[i] = factorial[i - 1] * i;
        }
        // enumerate k-palindromic integers
        // n = 4, [a b] b a, [a b] in [10:99]
        // n = 5, [a b c] b a, [a b c] in [100:999]
        std::unordered_set<std::string> visited;
        int result = 0;
        for (int base = std::pow(10, (n - 1) / 2), i = base; i < 10 * base; ++i) {
            std::string s = std::to_string(i);
            s += std::string(s.rbegin() + n % 2, s.rend());
            if (std::stoll(s) % k)
                continue;

            std::sort(s.begin(), s.end());
            if (!visited.insert(s).second)
                continue;

            std::array<int, 10> freq{};
            for (const auto& c : s) {
                freq[c - '0']++;
            }
            int count = (n - freq[0]) * factorial[n - 1];
            for (const auto& val : freq) {
                count /= factorial[val];
            }
            result += count;
        }
        return result;
    }
};