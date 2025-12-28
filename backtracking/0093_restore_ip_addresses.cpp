#include <string>
#include <vector>

/**
 * A valid IP address consists of exactly four integers separated by single dots. Each integer is
 * between 0 and 255 (inclusive) and cannot have leading zeros.
 *
 * - For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but "0.011.255.245",
 * "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
 *
 * Given a string "s" containing only digits, return all possible valid IP addresses that can be
 * formed by inserting dots into "s". You are not allowed to reorder or remove any digits in "s".
 * You may return the valid IP addresses in any order.
 *
 * ! "s" consists of digits only.
 */

class Solution {
public:
    std::vector<std::string> restoreIpAddresses(std::string s)
    {
        // 4 segments, each segment contains at least 1 digit and at most 3 digits
        if (s.size() < 4 || s.size() > 12)
            return {};

        backtrack(s, 0, 0);
        return result;
    }

private:
    std::vector<std::string> result;

    void backtrack(std::string& s, int start, int dotCount)
    {
        if (dotCount == 3) {
            if (isValid(s, start, s.size() - 1)) {
                result.push_back(s);
            }
            return;
        }
        for (int i = start; i < s.size(); ++i) {
            if (!isValid(s, start, i))
                break;

            s.insert(i + 1, 1, '.'); // insert dot
            dotCount++;
            backtrack(s, i + 2, dotCount);
            s.erase(i + 1, 1); // erase dot
            dotCount--;
        }
    }

    bool isValid(const std::string& s, int low, int high)
    {
        if (low > high)
            return false;

        const auto length = high - low + 1;
        if (length == 1)
            return true;

        if (s[low] == '0')
            return false;

        int num = 0;
        for (int i = low; i <= high; ++i) {
            num = 10 * num + (s[i] - '0');
        }
        return num <= 255;
    }
};