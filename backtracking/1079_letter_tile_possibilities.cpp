#include <functional>
#include <string>
#include <unordered_map>

/**
 * You have n  tiles, where each tile has one letter tiles[i] printed on it.
 *
 * Return the number of possible non-empty sequences of letters you can make using the letters
 * printed on those tiles.
 *
 * ! 1 <= tiles.length <= 7
 * ! tiles consists of uppercase English letters.
 */

class Solution {
public:
    int numTilePossibilities(std::string& tiles)
    {
        std::unordered_map<char, int> map;
        for (const auto& c : tiles) {
            map[c]++;
        }
        std::function<int(int)> dfs = [&](int i) {
            int count = 0;
            for (auto& [c, freq] : map) {
                if (freq == 0)
                    continue;

                freq--;
                count += 1 + dfs(i + 1);
                freq++;
            }
            return count;
        };
        return dfs(0);
    }
};
