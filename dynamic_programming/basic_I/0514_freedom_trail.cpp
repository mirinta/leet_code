#include <string>
#include <unordered_map>
#include <vector>

/**
 * In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial
 * called the "Freedom Trail Ring" and use the dial to spell a specific keyword to open the door.
 *
 * Given a string ring that represents the code engraved on the outer ring and another string key
 * that represents the keyword that needs to be spelled, return the minimum number of steps to spell
 * all the characters in the keyword.
 *
 * Initially, the first character of the ring is aligned at the "12:00" direction. You should spell
 * all the characters in key one by one by rotating ring clockwise or anticlockwise to make each
 * character of the string key aligned at the "12:00" direction and then by pressing the center
 * button.
 *
 * At the stage of rotating the ring to spell the key character key[i]:
 *
 * 1. You can rotate the ring clockwise or anticlockwise by one place, which counts as one step. The
 * final purpose of the rotation is to align one of ring's characters at the "12:00" direction,
 * where this character must equal key[i].
 *
 * 2. If the character key[i] has been aligned at the "12:00" direction, press the center button to
 * spell, which also counts as one step. After the pressing, you could begin to spell the next
 * character in the key (next stage). Otherwise, you have finished all the spelling.
 *
 * ! 1 <= ring.length, key.length <= 100
 * ! ring and key consist of only lower case English letters.
 * ! It is guaranteed that key could always be spelled by rotating ring.
 */

class Solution {
public:
    int findRotateSteps(std::string ring, std::string key)
    {
        std::vector<std::vector<int>> memo(ring.size(), std::vector<int>(key.size(), -1));
        return dfs(memo, 0, 0, ring, key);
    }

private:
    // min operations to spell key[j:n-1] while ring[i] is aligned at 12:00 direction
    int dfs(std::vector<std::vector<int>>& memo, int i, int j, const std::string& ring, const std::string& key)
    {
        if (j == key.size())
            return 0;

        if (memo[i][j] != -1)
            return memo[i][j];

        const int n = ring.size();
        int result = INT_MAX;
        for (int k = 0; k < n; ++k) {
            if (ring[k] != key[j])
                continue;

            const int dist = std::min(std::abs(k - i), n - std::abs(k - i));
            result = std::min(result, 1 + dist + dfs(memo, k, j + 1, ring, key));
        }
        return memo[i][j] = result;
    }
};