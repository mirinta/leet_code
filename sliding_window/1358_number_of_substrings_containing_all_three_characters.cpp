#include <algorithm>
#include <array>
#include <string>

/**
 * Given a string s consisting only of characters a, b and c.
 *
 * Return the number of substrings containing at least one occurrence of all these characters a, b
 * and c.
 *
 * ! 3 <= s.length <= 5 x 10^4
 * ! s only consists of a, b or c characters.
 */

class Solution {
public:
    int numberOfSubstrings(std::string s)
    {
        const int n = s.size();
        std::array<int, 3> count{};
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            count[s[right] - 'a']++;
            while (isValid(count)) {
                count[s[left] - 'a']--;
                left++;
            }
            result += left;
        }
        return result;
    }

private:
    bool isValid(const std::array<int, 3>& count)
    {
        return std::all_of(count.begin(), count.end(), [](const auto& val) { return val >= 1; });
    }
};
