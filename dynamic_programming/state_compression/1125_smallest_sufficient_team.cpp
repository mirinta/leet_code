#include <string>
#include <unordered_map>
#include <vector>

/**
 * In a project, you have a list of required skills req_skills, and a list of people. The ith person
 * people[i] contains a list of skills that the person has.
 *
 * Consider a sufficient team: a set of people such that for every required skill in req_skills,
 * there is at least one person in the team who has that skill. We can represent these teams by the
 * index of each person.
 *
 * For example, team = [0, 1, 3] represents the people with skills people[0], people[1], and
 * people[3]. Return any sufficient team of the smallest possible size, represented by the index of
 * each person. You may return the answer in any order.
 *
 * It is guaranteed an answer exists.
 *
 * ! 1 <= req_skills.length <= 16
 * ! 1 <= req_skills[i].length <= 16
 * ! req_skills[i] consists of lowercase English letters.
 * ! All the strings of req_skills are unique.
 * ! 1 <= people.length <= 60
 * ! 0 <= people[i].length <= 16
 * ! 1 <= people[i][j].length <= 16
 * ! people[i][j] consists of lowercase English letters.
 * ! All the strings of people[i] are unique.
 * ! Every skill in people[i] is a skill in req_skills.
 * ! It is guaranteed a sufficient team exists.
 */

class Solution {
public:
    std::vector<int> smallestSufficientTeam(std::vector<std::string>& req_skills,
                                            std::vector<std::vector<std::string>>& people)
    {
        const int n = req_skills.size();
        std::unordered_map<std::string, int> map;
        for (int i = 0; i < n; ++i) {
            map[req_skills[i]] = 1 << i;
        }
        const int m = people.size();
        std::vector<int> v(m, 0);
        for (int i = 0; i < m; ++i) {
            for (const auto& s : people[i]) {
                if (map.count(s)) {
                    v[i] |= map[s];
                }
            }
        }
        // dp[i][j] = min team size that satisfies requirement j using people[0:i-1]
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(1 << n, INT_MAX / 2));
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = 0;
        }
        std::vector<std::vector<int>> result(1 << n);
        for (int i = 1; i <= m; ++i) {
            const int skills = v[i - 1];
            for (int j = 0; j < (1 << n); ++j) {
                dp[i][j] = std::min(dp[i][j], dp[i - 1][j]);
                const int next = j | skills;
                dp[i][next] = std::min(dp[i][next], dp[i - 1][next]);
                if (dp[i][next] > dp[i - 1][j] + 1) {
                    dp[i][next] = dp[i - 1][j] + 1;
                    result[next] = result[j];
                    result[next].push_back(i - 1);
                }
            }
        }
        return result.back();
    }
};