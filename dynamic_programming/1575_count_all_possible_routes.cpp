#include <vector>

/**
 * You are given an array of distinct positive integers locations where locations[i] represents the
 * position of city i. You are also given integers start, finish and fuel representing the starting
 * city, ending city, and the initial amount of fuel you have, respectively.
 *
 * At each step, if you are at city i, you can pick any city j such that j != i and 0 <= j <
 * locations.length and move to city j. Moving from city i to city j reduces the amount of fuel you
 * have by |locations[i] - locations[j]|. Please notice that |x| denotes the absolute value of x.
 *
 * Notice that fuel cannot become negative at any point in time, and that you are allowed to visit
 * any city more than once (including start and finish).
 *
 * Return the count of all possible routes from start to finish. Since the answer may be too large,
 * return it modulo 10^9 + 7.
 *
 * ! 2 <= locations.length <= 100
 * ! 1 <= locations[i] <= 10^9
 * ! All integers in locations are distinct.
 * ! 0 <= start, finish < locations.length
 * ! 1 <= fuel <= 200
 */

class Solution {
public:
    int countRoutes(std::vector<int>& locations, int start, int finish, int fuel)
    {
        return approach1(locations, start, finish, fuel);
    }

private:
    static constexpr int kMod = 1e9 + 7;

    int approach2(const std::vector<int>& locations, int start, int finish, int fuel)
    {
        // dp[f][i] = num of routes from start to i
        // and the remaining fuel is f when arriving at i
        const int n = locations.size();
        std::vector<std::vector<int>> dp(1 + fuel, std::vector<int>(n, 0));
        dp[fuel][start] = 1;
        for (int f = fuel; f >= 0; --f) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (j == i)
                        continue;

                    const int cost = std::abs(locations[i] - locations[j]);
                    if (f + cost > fuel)
                        continue;

                    dp[f][i] = (dp[f][i] + dp[f + cost][j]) % kMod;
                }
            }
        }
        int result = 0;
        for (int f = 0; f <= fuel; ++f) {
            result = (result + dp[f][finish]) % kMod;
        }
        return result;
    }

    int approach1(const std::vector<int>& locations, int start, int finish, int fuel)
    {
        const int n = locations.size();
        std::vector<std::vector<int>> memo(n, std::vector<int>(fuel + 1, -1));
        return dfs(memo, start, finish, fuel, locations);
    }

    int dfs(std::vector<std::vector<int>>& memo, int i, int finish, int fuel, const std::vector<int>& locations)
    {
        if (fuel < 0)
            return 0;

        if (memo[i][fuel] != -1)
            return memo[i][fuel];

        int result = i == finish;
        for (int j = 0; j < locations.size(); ++j) {
            if (i == j)
                continue;

            const int cost = std::abs(locations[i] - locations[j]);
            result = (result + dfs(memo, j, finish, fuel - cost, locations)) % kMod;
        }
        return memo[i][fuel] = result;
    }
};
