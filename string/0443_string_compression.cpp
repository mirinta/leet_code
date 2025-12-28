#include <string>
#include <vector>

/**
 * Given an array of characters chars, compress it using the following algorithm:
 *
 * Begin with an empty string s. For each group of consecutive repeating characters in chars:
 *
 * - If the group's length is 1, append the character to s.
 *
 * - Otherwise, append the character followed by the group's length.
 *
 * The compressed string s should not be returned separately, but instead, be stored in the input
 * character array chars. Note that group lengths that are 10 or longer will be split into multiple
 * characters in chars.
 *
 * After you are done modifying the input array, return the new length of the array.
 *
 * ! You must write an algorithm that uses only constant extra space.
 *
 * ! 1 <= chars.length <= 2000
 * ! chars[i] is a lowercase English letter, uppercase English letter, digit, or symbol.
 */

class Solution {
public:
    int compress(std::vector<char>& chars)
    {
        const int n = chars.size();
        int left = 0;
        int right = 0;
        int length = 0;
        while (true) {
            while (right < n && chars[right] == chars[left]) {
                right++;
            }
            chars[length++] = chars[left];
            if (right - left > 1) {
                const std::string freq = std::to_string(right - left);
                for (const auto& i : freq) {
                    chars[length++] = i;
                }
            }
            left = right;
            if (right == n)
                break;
        }
        return length;
    }
};
