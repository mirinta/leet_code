#include <vector>

/**
 * In a town, there are n people labeled from 1 to n. There is a rumor that one of these people is
 * secretly the town judge.
 *
 * If the town judge exists, then:
 *
 * - The town judge trusts nobody.
 *
 * - Everybody (except for the town judge) trusts the town judge.
 *
 * - There is exactly one person that satisfies properties 1 and 2.
 *
 * You are given an array trust where trust[i] = [ai, bi] representing that the person labeled ai
 * trusts the person labeled bi. If a trust relationship does not exist in trust array, then such a
 * trust relationship does not exist.
 *
 * Return the label of the town judge if the town judge exists and can be identified, or return -1
 * otherwise.
 *
 * ! 1 <= n <= 1000
 * ! 0 <= trust.length <= 10^4
 * ! trust[i].length == 2
 * ! All the pairs of trust are unique.
 * ! ai != bi
 * ! 1 <= ai, bi <= n
 */

class Solution {
public:
    int findJudge(int n, std::vector<std::vector<int>>& trust)
    {
        std::vector<int> degree(n, 0); // in - out
        for (const auto& relationship : trust) {
            degree[relationship[0] - 1]--;
            degree[relationship[1] - 1]++;
        }
        for (int i = 0; i < n; ++i) {
            if (degree[i] == n - 1)
                return i + 1;
        }
        return -1;
    }
};