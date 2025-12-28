#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given a binary string s, and two integers num1 and num2. num1 and num2 are coprime
 * numbers.
 *
 * A ratio substring is a substring of s where the ratio between the number of 0's and the number of
 * 1's in the substring is exactly num1 : num2.
 *
 * For example, if num1 = 2 and num2 = 3, then "01011" and "1110000111" are ratio substrings, while
 * "11000" is not. Return the number of non-empty ratio substrings of s.
 *
 * Note that:
 *
 * - A substring is a contiguous sequence of characters within a string.
 *
 * - Two values x and y are coprime if gcd(x, y) == 1 where gcd(x, y) is the greatest common divisor
 * of x and y.
 *
 * ! 1 <= s.length <= 10^5
 * ! 1 <= num1, num2 <= s.length
 * ! num1 and num2 are coprime integers.
 */

class Solution {
public:
    long long fixedRatio(std::string s, int num1, int num2)
    {
        // let N0[i] = num of 0's in s[0:i] and N1[i] = num of 1's in s[0:i]
        // if s[j+1:i] is a ratio substring, then
        // num2 * (N0[i] - N0[j]) = num1 * (N1[i] - N1[j])
        // num2 * N0[i] - num1 * N1[i] = num2 * N0[j] - num1 * N1[j]
        // since s is a binary string, then N0[i] + N1[i] = length of s[0:i] = i + 1
        // (num2 + num1) * N0[i] - num1 * (i + 1) = (num2 + num1) * N0[j] - num1 * (j + 1)
        // let f[i] = (num2 + num1) * N0[i] - num1 * (i + 1)
        // then for any given i, we need to know the num of j such that f[i] = f[j]
        const int n = s.size();
        std::unordered_map<long long, long long> map;
        // base case: the first ratio substring s[0:p]
        // since gcd(num1, num2) = 1, then N0[p] = num1 and N1[p] = num2
        // p + 1 = length of s[0:p] = N0[p] + N1[p] = num1 + num2
        // thus, f[p] = (num2 + num1) * num1 - num1 * (num1 + num2) = 0
        map[0] = 1;
        long long zeros = 0;
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            zeros += s[i] == '0' ? 1 : 0;
            const long long f = (num1 + num2) * zeros - num1 * (i + 1LL);
            if (map.count(f)) {
                result += map[f];
            }
            map[f]++;
        }
        return result;
    }
};