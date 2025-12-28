#include <algorithm>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * You are given two string arrays username and website and an integer array timestamp. All the
 * given arrays are of the same length and the tuple [username[i], website[i], timestamp[i]]
 * indicates that the user username[i] visited the website website[i] at time timestamp[i].
 *
 * A pattern is a list of three websites (not necessarily distinct).
 *
 * - For example, ["home", "away", "love"], ["leetcode", "love", "leetcode"], and ["luffy", "luffy",
 * "luffy"] are all patterns.
 *
 * The score of a pattern is the number of users that visited all the websites in the pattern in the
 * same order they appeared in the pattern.
 *
 * - For example, if the pattern is ["home", "away", "love"], the score is the number of users x
 * such that x visited "home" then visited "away" and visited "love" after that.
 *
 * - Similarly, if the pattern is ["leetcode", "love", "leetcode"], the score is the number of users
 * x such that x visited "leetcode" then visited "love" and visited "leetcode" one more time after
 * that.
 *
 * - Also, if the pattern is ["luffy", "luffy", "luffy"], the score is the number of users x such
 * that x visited "luffy" three different times at different timestamps.
 *
 * Return the pattern with the largest score. If there is more than one pattern with the same
 * largest score, return the lexicographically smallest such pattern.
 *
 * Note that the websites in a pattern do not need to be visited contiguously, they only need to be
 * visited in the order they appeared in the pattern.
 *
 * ! 3 <= username.length <= 50
 * ! 1 <= username[i].length <= 10
 * ! timestamp.length == username.length
 * ! 1 <= timestamp[i] <= 10^9
 * ! website.length == username.length
 * ! 1 <= website[i].length <= 10
 * ! username[i] and website[i] consist of lowercase English letters.
 * ! It is guaranteed that there is at least one user who visited at least three websites.
 * ! All the tuples [username[i], timestamp[i], website[i]] are unique.
 */

class Solution {
public:
    std::vector<std::string> mostVisitedPattern(std::vector<std::string>& username,
                                                std::vector<int>& timestamp,
                                                std::vector<std::string>& website)
    {
        const int n = username.size();
        std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> info;
        for (int i = 0; i < n; ++i) {
            info[username[i]].emplace_back(timestamp[i], website[i]);
        }
        std::map<std::string, int> map;
        int maxScore = 0;
        for (auto& [user, webs] : info) {
            std::sort(webs.begin(), webs.end(), [](const auto& p1, const auto& p2) { return p1.first < p2.first; });
            const auto set = helper(webs);
            for (const auto& pattern : set) {
                maxScore = std::max(maxScore, ++map[pattern]);
            }
        }
        for (const auto& [pattern, score] : map) {
            if (score == maxScore)
                return decode(pattern);
        }
        return {};
    }

private:
    std::unordered_set<std::string> helper(const std::vector<std::pair<int, std::string>>& webs)
    {
        std::unordered_set<std::string> set;
        for (int i = 0; i < webs.size(); ++i) {
            for (int j = i + 1; j < webs.size(); ++j) {
                for (int k = j + 1; k < webs.size(); ++k) {
                    set.insert(webs[i].second + '#' + webs[j].second + '#' + webs[k].second);
                }
            }
        }
        return set;
    }

    std::vector<std::string> decode(const std::string& s)
    {
        const auto first = s.find_first_of('#');
        const auto last = s.find_last_of('#');
        return {s.substr(0, first), s.substr(first + 1, last - first - 1), s.substr(last + 1)};
    }
};