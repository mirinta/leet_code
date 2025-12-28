#include <algorithm>
#include <array>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given three arrays of length n that describe the properties of n coupons: code,
 * businessLine, and isActive. The ith coupon has:
 *
 * - code[i]: a string representing the coupon identifier.
 *
 * - businessLine[i]: a string denoting the business category of the coupon.
 *
 * - isActive[i]: a boolean indicating whether the coupon is currently active.
 *
 * A coupon is considered valid if all of the following conditions hold:
 *
 * - code[i] is non-empty and consists only of alphanumeric characters (a-z, A-Z, 0-9) and
 * underscores (_).
 *
 * - businessLine[i] is one of the following four categories: "electronics", "grocery",
 * "pharmacy", "restaurant".
 *
 * - isActive[i] is true.
 *
 * Return an array of the codes of all valid coupons, sorted first by their businessLine in the
 * order: "electronics", "grocery", "pharmacy", "restaurant", and then by code in lexicographical
 * (ascending) order within each category.
 *
 * ! n == code.length == businessLine.length == isActive.length
 * ! 1 <= n <= 100
 * ! 0 <= code[i].length, businessLine[i].length <= 100
 * ! code[i] and businessLine[i] consist of printable ASCII characters.
 * ! isActive[i] is either true or false.
 */

class Solution {
public:
    std::vector<std::string> validateCoupons(std::vector<std::string>& code,
                                             std::vector<std::string>& businessLine,
                                             std::vector<bool>& isActive)
    {
        const int n = code.size();
        static const std::unordered_map<std::string, int> map{
            {"electronics", 0}, {"grocery", 1}, {"pharmacy", 2}, {"restaurant", 3}};
        std::array<std::vector<std::string>, 4> data{};
        int size = 0;
        for (int i = 0; i < n; ++i) {
            if (!isActive[i] || !map.count(businessLine[i]) || !isValid(code[i]))
                continue;

            data[map.at(businessLine[i])].push_back(code[i]);
            size++;
        }
        std::vector<std::string> result;
        result.reserve(size);
        for (auto& codes : data) {
            std::sort(codes.begin(), codes.end());
            result.insert(result.end(), codes.begin(), codes.end());
        }
        return result;
    }

private:
    bool isValid(const std::string& s)
    {
        if (s.empty())
            return false;

        for (const auto& c : s) {
            if (c != '_' && !std::isalnum(c))
                return false;
        }
        return true;
    }
};