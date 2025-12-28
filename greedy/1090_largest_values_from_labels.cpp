#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * There is a set of n items. You are given two integer arrays values and labels where the value and
 * the label of the ith element are values[i] and labels[i] respectively. You are also given two
 * integers numWanted and useLimit.
 *
 * Choose a subset s of the n elements such that:
 *
 * - The size of the subset s is less than or equal to numWanted.
 *
 * - There are at most useLimit items with the same label in s.
 *
 * The score of a subset is the sum of the values in the subset.
 *
 * Return the maximum score of a subset s.
 *
 * ! n == values.length == labels.length
 * ! 1 <= n <= 2 * 10^4
 * ! 0 <= values[i], labels[i] <= 2 * 10^4
 * ! 1 <= numWanted, useLimit <= n
 */

class Solution {
public:
    int largestValsFromLabels(std::vector<int>& values, std::vector<int>& labels, int numWanted, int useLimit)
    {
        const int n = values.size();
        std::vector<std::pair<int, int>> v(n);
        for (int i = 0; i < n; ++i) {
            v[i].first = values[i];
            v[i].second = i;
        }
        std::sort(v.begin(), v.end(), [](const auto& p1, const auto& p2) { return p1.first > p2.first; });
        std::unordered_map<int, int> map;
        int result = 0;
        for (int i = 0; i < n && numWanted > 0; ++i) {
            const auto& [value, index] = v[i];
            const auto& label = labels[index];
            if (map[label] + 1 > useLimit)
                continue;

            map[label]++;
            result += value;
            numWanted--;
        }
        return result;
    }
};