#include <array>
#include <string>

/**
 * You are given a string s and an integer t, representing the number of transformations to perform.
 * In one transformation, every character in s is replaced according to the following rules:
 *
 * - If the character is 'z', replace it with the string "ab".
 *
 * - Otherwise, replace it with the next character in the alphabet. For example, 'a' is replaced
 * with 'b', 'b' is replaced with 'c', and so on.
 *
 * Return the length of the resulting string after exactly t transformations.
 *
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists only of lowercase English letters.
 * ! 1 <= t <= 10^5
 */

class Solution {
public:
    int lengthAfterTransformations(std::string s, int t)
    {
        static constexpr int kMod = 1e9 + 7;
        std::array<int, 26> count{};
        for (const auto& c : s) {
            count[c - 'a']++;
        }
        for (int i = 0; i < t; ++i) {
            const int countZ = count.back();
            for (int j = 25; j >= 1; --j) {
                count[j] = count[j - 1];
            }
            count[0] = countZ;
            count[1] = (count[1] + countZ) % kMod;
        }
        int result = 0;
        for (const auto& val : count) {
            result = (result + val) % kMod;
        }
        return result;
    }
};
