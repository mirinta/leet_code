#include <string>

/**
 * You are given a string s representing a 12-hour format time where some of the digits (possibly
none) are replaced with a "?".
 *
 * 12-hour times are formatted as "HH:MM", where HH is between 00 and 11, and MM is between 00
 * and 59. The earliest 12-hour time is 00:00, and the latest is 11:59.
 *
 * You have to replace all the "?" characters in s with digits such that the time we obtain by the
 * resulting string is a valid 12-hour format time and is the latest possible.
 *
 * Return the resulting string.
 *
 * ! s.length == 5
 * ! s[2] is equal to the character ":".
 * ! All characters except s[2] are digits or "?" characters.
 * ! The input is generated such that there is at least one time between "00:00" and "11:59" that
 * ! you can obtain after replacing the "?" characters.
 */

class Solution {
public:
    std::string findLatestTime(std::string s)
    {
        for (int hours = 11; hours >= 0; --hours) {
            for (int minutes = 59; minutes >= 0; --minutes) {
                std::string candidate;
                if (hours < 10) {
                    candidate.push_back('0');
                }
                candidate.append(std::to_string(hours));
                candidate.push_back(':');
                if (minutes < 10) {
                    candidate.push_back('0');
                }
                candidate.append(std::to_string(minutes));
                if (isValid(candidate, s))
                    return candidate;
            }
        }
        return {};
    }

private:
    bool isValid(const std::string& s1, const std::string& s2)
    {
        for (int i = 0; i < s1.size(); ++i) {
            if (s2[i] != '?' && s1[i] != s2[i])
                return false;
        }
        return true;
    }
};