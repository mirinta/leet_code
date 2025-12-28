#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * On a social network consisting of m users and some friendships between users, two users can
 * communicate with each other if they know a common language.
 *
 * You are given an integer n, an array languages, and an array friendships where:
 *
 * - There are n languages numbered 1 through n,
 *
 * - languages[i] is the set of languages the i​​​​​​th​​​​ user knows, and
 *
 * - friendships[i] = [u​​​​​​i​​​, v​​​​​​i] denotes a friendship between the users
 * u​​​​​​​​​​​i​​​​​ and vi.
 *
 * You can choose one language and teach it to some users so that all friends can communicate with
 * each other. Return the minimum number of users you need to teach.
 *
 * Note that friendships are not transitive, meaning if x is a friend of y and y is a friend of z,
 * this doesn't guarantee that x is a friend of z.
 *
 * ! 2 <= n <= 500
 * ! languages.length == m
 * ! 1 <= m <= 500
 * ! 1 <= languages[i].length <= n
 * ! 1 <= languages[i][j] <= n
 * ! 1 <= u​​​​​​i < v​​​​​​i <= languages.length
 * ! 1 <= friendships.length <= 500
 * ! All tuples (u​​​​​i, v​​​​​​i) are unique
 * ! languages[i] contains only unique values
 */

class Solution {
public:
    int minimumTeachings(int n, std::vector<std::vector<int>>& languages, std::vector<std::vector<int>>& friendships)
    {
        std::unordered_map<int, std::bitset<501>> map;
        for (int i = 0; i < languages.size(); ++i) {
            for (const auto& j : languages[i]) {
                map[i][j] = 1;
            }
        }
        std::unordered_set<int> filtered;
        for (int i = 0; i < friendships.size(); ++i) {
            const int u = friendships[i][0] - 1;
            const int v = friendships[i][1] - 1;
            if ((map[u] & map[v]).any())
                continue;

            filtered.insert(u);
            filtered.insert(v);
        }
        if (filtered.empty())
            return 0;

        std::vector<int> count(n + 1, 0);
        int maxFreq = 0;
        for (const auto& person : filtered) {
            for (const auto& language : languages[person]) {
                count[language]++;
                maxFreq = std::max(maxFreq, count[language]);
            }
        }
        return filtered.size() - maxFreq;
    }
};
