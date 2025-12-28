#include <string>
#include <vector>

/**
 * You are given a 0-indexed array of strings details. Each element of details provides information
 * about a given passenger compressed into a string of length 15. The system is such that:
 *
 * - The first ten characters consist of the phone number of passengers.
 *
 * - The next character denotes the gender of the person.
 *
 * - The following two characters are used to indicate the age of the person.
 *
 * - The last two characters determine the seat allotted to that person.
 *
 * Return the number of passengers who are strictly more than 60 years old.
 *
 * ! 1 <= details.length <= 100
 * ! details[i].length == 15
 * ! details[i] consists of digits from '0' to '9'.
 * ! details[i][10] is either 'M' or 'F' or 'O'.
 * ! The phone numbers and seat numbers of the passengers are distinct.
 */

class Solution {
public:
    int countSeniors(std::vector<std::string>& details)
    {
        int result = 0;
        for (const auto& s : details) {
            int age = 0;
            age = age * 10 + (s[11] - '0');
            age = age * 10 + (s[12] - '0');
            result += age > 60;
        }
        return result;
    }
};