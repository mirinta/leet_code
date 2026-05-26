#include <string>

/**
 * You are given a string word. A letter is called special if it appears both in lowercase and
 * uppercase in word.
 *
 * Return the number of special letters in word.
 *
 * ! 1 <= word.length <= 50
 * ! word consists of only lowercase and uppercase English letters.
 */

class Solution {
public:
    int numberOfSpecialChars(std::string& word)
    {
        int upper = 0;
        int lower = 0;
        for (const auto& c : word) {
            if (std::isupper(c)) {
                upper |= 1 << (c - 'A');
            } else {
                lower |= 1 << (c - 'a');
            }
        }
        return setbits(upper & lower);
    }

private:
    int setbits(int n)
    {
        int result = 0;
        while (n) {
            n &= n - 1;
            result++;
        }
        return result;
    }
};