#include <string>

/**
 * Given the binary representation of an integer as a string s, return the number of steps to reduce
 * it to 1 under the following rules:
 *
 * - If the current number is even, you have to divide it by 2.
 *
 * - If the current number is odd, you have to add 1 to it.
 *
 * It is guaranteed that you can always reach one for all test cases.
 *
 * ! 1 <= s.length <= 500
 * ! s consists of characters '0' or '1'
 * ! s[0] == '1'
 */

class Solution {
public:
    int numSteps(std::string s)
    {
        return approach2(s);
    }

private:
    int approach2(const std::string& s)
    {
        const int n = s.size();
        int carry = 0;
        int result = 0;
        for (int i = n - 1; i > 0; --i) {
            if ((s[i] - '0' + carry) & 1) {
                carry = 1;
                result += 2;
            } else {
                result++;
            }
        }
        result += carry;
        return result;
    }

    int approach1(std::string& s)
    {
        int result = 0;
        while (s.size() > 1) {
            if (s.back() == '0') {
                s.pop_back();
            } else {
                addOne(s);
            }
            result++;
        }
        return result;
    }

    void addOne(std::string& s)
    {
        const int n = s.size();
        int i = n - 1;
        while (i >= 0 && s[i] == '1') {
            s[i] = '0';
            i--;
        }
        if (i < 0) {
            s.insert(s.begin(), '1');
        } else {
            s[i] = '1';
        }
    }
};