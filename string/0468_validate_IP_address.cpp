#include <string>
#include <vector>

/**
 * Given a string queryIP, return "IPv4" if IP is a valid IPv4 address, "IPv6" if IP is a valid IPv6
 * address or "Neither" if IP is not a correct IP of any type.
 *
 * A valid IPv4 address is an IP in the form "x1.x2.x3.x4" where 0 <= xi <= 255 and xi cannot
 * contain leading zeros. For example, "192.168.1.1" and "192.168.1.0" are valid IPv4 addresses
 * while "192.168.01.1", "192.168.1.00", and "192.168@1.1" are invalid IPv4 addresses.
 *
 * A valid IPv6 address is an IP in the form "x1:x2:x3:x4:x5:x6:x7:x8" where:
 *
 * - 1 <= xi.length <= 4
 *
 * - xi is a hexadecimal string which may contain digits, lowercase English letter ('a' to 'f') and
 * upper-case English letters ('A' to 'F').
 *
 * - Leading zeros are allowed in xi.
 *
 * For example,
 *
 * - "2001:0db8:85a3:0000:0000:8a2e:0370:7334" and "2001:db8:85a3:0:0:8A2E:0370:7334" are valid IPv6
 * addresses, while "2001:0db8:85a3::8A2E:037j:7334" and !
 *
 * - "02001:0db8:85a3:0000:0000:8a2e:0370:7334" are ! invalid IPv6 addresses.
 *
 * ! queryIP consists only of English letters, digits and the characters '.' and ':'.
 */

class Solution {
public:
    std::string validIPAddress(std::string queryIP)
    {
        const auto strs = parse(queryIP);
        if (isIPv4(strs))
            return "IPv4";

        if (isIPv6(strs))
            return "IPv6";

        return "Neither";
    }

private:
    std::vector<std::string> parse(const std::string& s)
    {
        const int n = s.size();
        std::vector<std::string> result;
        for (int first = -1, second = 0; second <= n; ++second) {
            if (second == n || s[second] == '.' || s[second] == ':') {
                result.push_back(s.substr(first + 1, second - first - 1));
                first = second;
            }
        }
        return result;
    }

    bool isIPv4(const std::vector<std::string>& strs)
    {
        if (strs.size() != 4)
            return false;

        for (const auto& s : strs) {
            if (s.empty() || (s.size() > 1 && s[0] == '0'))
                return false;

            int val = 0;
            for (const auto& c : s) {
                if (!std::isdigit(c))
                    return false;

                val = val * 10 + (c - '0');
                if (val > 255)
                    return false;
            }
        }
        return true;
    }

    bool isIPv6(const std::vector<std::string>& strs)
    {
        if (strs.size() != 8)
            return false;

        for (const auto& s : strs) {
            if (s.empty() || s.size() > 4)
                return false;

            for (const auto& c : s) {
                if (!std::isalnum(c))
                    return false;

                if (std::isdigit(c))
                    continue;

                if (std::tolower(c) < 'a' || std::tolower(c) > 'f')
                    return false;
            }
        }
        return true;
    }
};