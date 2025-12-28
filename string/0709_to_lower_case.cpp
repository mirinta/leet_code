#include <string>

/**
 * Given a string "s", return the string after replacing every uppercase letter with the same
 * lowercase letter.
 *
 * ! s consists of printable ASCII characters.
 */

class Solution {
public:
    std::string toLowerCase(const std::string& s)
    {
        if (s.empty())
            return {};

        constexpr auto offset = 'A' - 'a';
        std::string result(s);
        for (auto& c : result) {
            if (c - 'A' >= 0 && c - 'A' < 26) {
                c -= offset;
            }
        }
        return result;
    }
};