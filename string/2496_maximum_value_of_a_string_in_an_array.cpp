#include <string>
#include <vector>

/**
 * The value of an alphanumeric string can be defined as:
 *
 * The numeric representation of the string in base 10, if it comprises of digits only.
 *
 * The length of the string, otherwise.
 *
 * Given an array strs of alphanumeric strings, return the maximum value of any string in strs.
 *
 * ! 1 <= strs.length <= 100
 * ! 1 <= strs[i].length <= 9
 * ! strs[i] consists of only lowercase English letters and digits.
 */

class Solution {
public:
    int maximumValue(std::vector<std::string>& strs)
    {
        int result = 0;
        for (const auto& str : strs) {
            result = std::max(result, parse(str));
        }
        return result;
    }

private:
    int parse(const std::string& str)
    {
        if (str.empty())
            return 0;

        int result = 0;
        for (const auto& c : str) {
            if (c >= '0' && c <= '9') {
                result = result * 10 + (c - '0');
            } else {
                return str.size();
            }
        }
        return result;
    }
};