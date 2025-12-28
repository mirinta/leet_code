#include <string>
#include <unordered_map>

/**
 * Given two strings "s" and "goal", return true if you can swap two letters in "s" so the result is
 * equal to "goal", otherwise, return false.
 *
 * Swapping letters is defined as taking two indices i and j (0-indexed) such that i != j and
 * swapping the characters at s[i] and s[j].
 *
 * - For example, swapping at indices 0 and 2 in "abcd" results in "cbad"
 *
 * ! s and goal consist of lowercase letters.
 */

class Solution {
public:
    bool buddyStrings(const std::string& s, const std::string& goal)
    {
        const auto n = s.size();
        if (n != goal.size() || n < 2)
            return false;

        std::unordered_map<char, int> freq;
        for (const auto& c : goal) {
            freq[c]++;
        }
        int counter = 0;
        for (size_t i = 0; i < n; ++i) {
            if (!freq.count(s[i]))
                return false;

            if (--freq[s[i]] < 0)
                return false;

            if (s[i] != goal[i]) {
                counter++;
            }
            if (counter > 2)
                return false;
        }
        return counter == 2 || freq.size() < n;
        // counter = 0 means "s" and "goal" are exact the same
        // in this case, check if there are duplicate characters in "s"
        // - if true, there exists i and j, s.t., i!=j and s[i]=s[j],
        //   then swapping s[i] and s[j] doesn't change "s" => "s" still equals to "goal"
        // - otherwise, swapping any two characters of "s" can make "s" != "goal"
    }
};