#include <unordered_map>
#include <vector>

/**
 * Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j] = [c, d] if and only
 * if either (a == c and b == d), or (a == d and b == c) - that is, one domino can be rotated to be
 * equal to another domino.
 *
 * Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length, and dominoes[i] is
 * equivalent to dominoes[j].
 *
 * ! 1 <= dominoes.length <= 4 * 10^4
 * ! dominoes[i].length == 2
 * ! 1 <= dominoes[i][j] <= 9
 */

class Solution
{
public:
    int numEquivDominoPairs(std::vector<std::vector<int>>& dominoes)
    {
        const int n = dominoes.size();
        std::unordered_map<int, int> map;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            const int e1 = encode(dominoes[i][0], dominoes[i][1]);
            const int e2 = encode(dominoes[i][1], dominoes[i][0]);
            if (map.count(e1)) {
                result += map[e1];
            } else if (map.count(e2)) {
                result += map[e2];
            }
            map[e1]++;
            if (e1 != e2) {
                map[e2]++;
            }
        }
        return result;
    }

private:
    int encode(int a, int b) { return 10 * a + b; }
};
