#include <algorithm>
#include <array>
#include <string>
#include <vector>

/**
 * In a special ranking system, each voter gives a rank from highest to lowest to all teams
 * participating in the competition.
 *
 * The ordering of teams is decided by who received the most position-one votes. If two or more
 * teams tie in the first position, we consider the second position to resolve the conflict, if they
 * tie again, we continue this process until the ties are resolved. If two or more teams are still
 * tied after considering all positions, we rank them alphabetically based on their team letter.
 *
 * You are given an array of strings votes which is the votes of all voters in the ranking systems.
 * Sort all teams according to the ranking system described above.
 *
 * Return a string of all teams sorted by the ranking system.
 *
 * ! 1 <= votes.length <= 1000
 * ! 1 <= votes[i].length <= 26
 * ! votes[i].length == votes[j].length for 0 <= i, j < votes.length.
 * ! votes[i][j] is an English uppercase letter.
 * ! All characters of votes[i] are unique.
 * ! All the characters that occur in votes[0] also occur in votes[j] where 1 <= j < votes.length.
 */

class Solution
{
public:
    std::string rankTeams(std::vector<std::string>& votes)
    {
        std::array<std::array<int, 26>, 26> count{};
        for (const auto& v : votes) {
            for (int i = 0; i < v.size(); ++i) {
                count[v[i] - 'A'][i]++;
            }
        }
        auto result = votes[0];
        std::sort(result.begin(), result.end(), [&](const auto& c1, const auto& c2) {
            if (count[c1 - 'A'] == count[c2 - 'A'])
                return c1 < c2;

            return count[c1 - 'A'] > count[c2 - 'A'];
        });
        return result;
    }
};