#include <string>
#include <unordered_map>

/**
 * You're given strings jewels representing the types of stones that are jewels, and stones
 * representing the stones you have. Each character in stones is a type of stone you have. You want
 * to know how many of the stones you have are also jewels.
 *
 * Letters are case sensitive, so "a" is considered a different type of stone from "A".
 *
 * ! 1 <= jewels.length, stones.length <= 50
 * ! jewels and stones consist of only English letters.
 * ! All the characters of jewels are unique.
 */

class Solution {
public:
    int numJewelsInStones(std::string jewels, std::string stones)
    {
        std::unordered_map<char, int> map;
        for (const auto& c : stones) {
            map[c]++;
        }
        int result = 0;
        for (const auto& c : jewels) {
            if (map.count(c)) {
                result += map[c];
            }
        }
        return result;
    }
};