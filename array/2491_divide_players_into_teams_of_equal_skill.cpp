#include <numeric>
#include <unordered_map>
#include <vector>

/**
 * You are given a positive integer array skill of even length n where skill[i] denotes the skill of
 * the ith player. Divide the players into n / 2 teams of size 2 such that the total skill of each
 * team is equal.
 *
 * The chemistry of a team is equal to the product of the skills of the players on that team.
 *
 * Return the sum of the chemistry of all the teams, or return -1 if there is no way to divide the
 * players into teams such that the total skill of each team is equal.
 *
 * ! 2 <= skill.length <= 10^5
 * ! skill.length is even.
 * ! 1 <= skill[i] <= 1000
 */

class Solution {
public:
    long long dividePlayers(std::vector<int>& skill)
    {
        const long long n = skill.size();
        const long long total = std::accumulate(skill.begin(), skill.end(), 0LL);
        const long long sum = total * 2 / n;
        std::unordered_map<long long, long long> map;
        for (const auto& val : skill) {
            map[val]++;
        }
        long long result = 0;
        for (const auto& [val, count] : map) {
            if (!map.count(sum - val) || map[sum - val] != count)
                return -1;

            result += val * (sum - val) * count;
        }
        return result / 2;
    }
};