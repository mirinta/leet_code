#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given a string s. We want to partition the string into as many parts as possible so that
 * each letter appears in at most one part.
 *
 * Note that the partition is done so that after concatenating all the parts in order, the resultant
 * string should be s.
 *
 * Return a list of integers representing the size of these parts.
 *
 * ! 1 <= s.length <= 500
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    std::vector<int> partitionLabels(std::string s)
    {
        return approach2(s);
    }

private:
    // hash table, TC = O(N), SC = O(N)
    std::vector<int> approach2(const std::string& s)
    {
        const int n = s.size();
        std::unordered_map<int, int> last;
        for (int i = 0; i < n; ++i) {
            last[s[i]] = i;
        }
        std::vector<int> result;
        for (int i = 0, start = 0, end = 0; i < n; ++i) {
            end = std::max(end, last[s[i]]);
            if (i == end) {
                result.emplace_back(end - start + 1);
                start = i + 1;
            }
        }
        return result;
    }

    // merge intervals, TC = O(NlogN), SC = O(N)
    std::vector<int> approach1(const std::string& s)
    {
        std::vector<std::pair<int, int>> intervals(26, {-1, -1});
        for (int i = 0; i < s.size(); ++i) {
            const int index = s[i] - 'a';
            if (intervals[index].first == -1) {
                intervals[index].first = i;
                intervals[index].second = i;
            } else {
                intervals[index].second = i;
            }
        }
        intervals.erase(std::remove_if(intervals.begin(), intervals.end(), [](const auto& p) { return p.first == -1; }),
                        intervals.end());
        const auto merged = helper(intervals);
        std::vector<int> result;
        result.reserve(merged.size());
        for (const auto& [start, end] : merged) {
            result.emplace_back(end - start + 1);
        }
        return result;
    }

    std::vector<std::pair<int, int>> helper(std::vector<std::pair<int, int>>& intervals)
    {
        std::sort(intervals.begin(), intervals.end());
        std::vector<std::pair<int, int>> merged;
        for (const auto& interval : intervals) {
            if (merged.empty() || interval.first > merged.back().second) {
                merged.push_back(interval);
            } else {
                merged.back().second = std::max(merged.back().second, interval.second);
            }
        }
        return merged;
    }
};
