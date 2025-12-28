#include <algorithm>
#include <string>
#include <vector>

/**
 * You are given an array of strings names, and an array heights that consists of distinct positive
 * integers. Both arrays are of length n.
 *
 * For each index i, names[i] and heights[i] denote the name and height of the ith person.
 *
 * Return names sorted in descending order by the people's heights.
 *
 * ! n == names.length == heights.length
 * ! 1 <= n <= 10^3
 * ! 1 <= names[i].length <= 20
 * ! 1 <= heights[i] <= 10^5
 * ! names[i] consists of lower and upper case English letters.
 * ! All the values of heights are distinct.
 */

class Solution {
public:
    std::vector<std::string> sortPeople(std::vector<std::string>& names, std::vector<int>& heights)
    {
        const int n = names.size();
        std::vector<std::pair<int, int>> info(n);
        for (int i = 0; i < n; ++i) {
            info[i].first = heights[i];
            info[i].second = i;
        }
        std::sort(info.begin(), info.end(), [](const auto& p1, const auto& p2) { return p1.first > p2.first; });
        std::vector<std::string> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = names[info[i].second];
        }
        return result;
    }
};
