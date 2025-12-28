#include <vector>

/**
 * You are playing a game of tag with your friends. In tag, people are divided into two teams:
 * people who are "it", and people who are not "it". The people who are "it" want to catch as many
 * people as possible who are not "it".
 *
 * You are given a 0-indexed integer array team containing only zeros (denoting people who are not
 * "it") and ones (denoting people who are "it"), and an integer dist. A person who is "it" at index
 * i can catch any one person whose index is in the range [i - dist, i + dist] (inclusive) and is
 * not "it".
 *
 * Return the maximum number of people that the people who are "it" can catch.
 *
 * ! 1 <= team.length <= 10^5
 * ! 0 <= team[i] <= 1
 * ! 1 <= dist <= team.length
 */

class Solution {
public:
    int catchMaximumAmountofPeople(std::vector<int>& team, int dist)
    {
        const int n = team.size();
        int result = 0;
        for (int i = 0, j = 0; i < n; ++i) {
            if (team[i] != 1)
                continue;

            j = std::max(j, i - dist);
            while (j < n && team[j] != 0) {
                j++;
            }
            if (j < n && std::abs(i - j) <= dist) {
                result++;
                j++;
            }
        }
        return result;
    }
};