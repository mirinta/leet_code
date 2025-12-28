#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given a 2D 0-indexed array of strings, access_times, with size n. For each i where 0 <= i
 * <= n - 1, access_times[i][0] represents the name of an employee, and access_times[i][1]
 * represents the access time of that employee. All entries in access_times are within the same day.
 *
 * The access time is represented as four digits using a 24-hour time format, for example, "0800" or
 * "2250".
 *
 * An employee is said to be high-access if he has accessed the system three or more times within a
 * one-hour period.
 *
 * Times with exactly one hour of difference are not considered part of the same one-hour period.
 * For example, "0815" and "0915" are not part of the same one-hour period.
 *
 * Access times at the start and end of the day are not counted within the same one-hour period. For
 * example, "0005" and "2350" are not part of the same one-hour period.
 *
 * Return a list that contains the names of high-access employees with any order you want.
 *
 * ! 1 <= access_times.length <= 100
 * ! access_times[i].length == 2
 * ! 1 <= access_times[i][0].length <= 10
 * ! access_times[i][0] consists only of English small letters.
 * ! access_times[i][1].length == 4
 * ! access_times[i][1] is in 24-hour time format.
 * ! access_times[i][1] consists only of '0' to '9'.
 */

class Solution {
public:
    std::vector<std::string> findHighAccessEmployees(std::vector<std::vector<std::string>>& access_times)
    {
        std::unordered_map<std::string, std::vector<int>> map;
        for (const auto& info : access_times) {
            map[info[0]].push_back(std::stoi(info[1]));
        }
        std::vector<std::string> result;
        for (auto& [name, times] : map) {
            std::sort(times.begin(), times.end());
            if (isValid(times)) {
                result.push_back(name);
            }
        }
        return result;
    }

private:
    bool isValid(const std::vector<int>& times)
    {
        if (times.size() < 3)
            return false;

        for (int i = 0; i + 2 < times.size(); ++i) {
            auto iter = std::upper_bound(times.begin() + i, times.end(), endTime(times[i]));
            if (std::distance(times.begin() + i, iter) >= 3)
                return true;
        }
        return false;
    }

    int endTime(int time)
    {
        int hours = time / 100;
        int mins = time % 100;
        hours += (mins + 59) / 60;
        mins = (mins + 59) % 60;
        return std::min(2359, hours * 100 + mins);
    }
};