#include <string>
#include <vector>

/**
 * You are given a 0-indexed string s and a 0-indexed integer array spaces that describes the
 * indices in the original string where spaces will be added. Each space should be inserted before
 * the character at the given index.
 *
 * - For example, given s = "EnjoyYourCoffee" and spaces = [5, 9], we place spaces before 'Y' and
 * 'C', which are at indices 5 and 9 respectively. Thus, we obtain "Enjoy Your Coffee".
 *
 * Return the modified string after the spaces have been added.
 *
 * ! 1 <= s.length <= 3 * 10^5
 * ! s consists only of lowercase and uppercase English letters.
 * ! 1 <= spaces.length <= 3 * 10^5
 * ! 0 <= spaces[i] <= s.length - 1
 * ! All the values of spaces are strictly increasing.
 */

class Solution {
public:
    std::string addSpaces(std::string& s, std::vector<int>& spaces)
    {
        std::string result;
        result.reserve(s.size() + spaces.size());
        for (int i = 0, j = 0; i < s.size(); ++i) {
            if (j < spaces.size() && spaces[j] == i) {
                result.push_back(' ');
                j++;
            }
            result.push_back(s[i]);
        }
        return result;
    }
};