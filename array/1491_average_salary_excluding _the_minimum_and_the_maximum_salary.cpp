#include <vector>

/**
 * You are given an array of unique integers "salary" where "salary[i]" is the salary of the "i"th
 * employee.
 *
 * Return the average salary of employees excluding the minimum and maximum salary. Answers within
 * 10^-5 of the actual answer will be accepted.
 */

class Solution {
public:
    double average(const std::vector<int>& salary)
    {
        if (salary.empty() || salary.size() < 3)
            return 0;

        double sum = 0;
        int min = INT_MAX;
        int max = INT_MIN;
        for (const auto& i : salary) {
            sum += i;
            min = std::min(min, i);
            max = std::max(max, i);
        }
        return (sum - min - max) / (salary.size() - 2);
    }
};