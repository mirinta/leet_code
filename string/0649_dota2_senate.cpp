#include <queue>
#include <string>
#include <unordered_map>

/**
 * In the world of Dota2, there are two parties: the Radiant and the Dire.
 *
 * The Dota2 senate consist of senators coming from two parties. Now the Senate wants to decide on a
 * change in the Dota2 game. The voting for this change is a round-based procedure. In each round,
 * each senator can exercise on of the two rights:
 *
 * - Ban one senator's right: A senator can make another senator lose all his rights in this and all
 * the following rounds.
 *
 * - Announce the victory: If this senator found the senators who still have rights to vote are all
 * from the same party, he can announce the victory and decide on the change in the game.
 *
 * Given a string "senate" representing each senator's party belonging. The character 'R' and 'D'
 * represent the Radiant party and the Dire party. Then if there are "n" senators, the size of the
 * given string will be "n".
 *
 * Suppose every senators is smart enough and will play the best strategy for his own party. Predict
 * which party will finally announce the victory and change the Dota2 game. The output should be
 * "Radiant" or "Dire".
 */

class Solution {
public:
    std::string predictPartyVictory(const std::string& senate)
    {
        std::queue<char> queue;
        std::unordered_map<char, std::pair<int, int>> map; // <#remaining, #need to be skipped>
        constexpr char k_radiant = 'R';
        constexpr char k_dire = 'D';
        for (const auto& p : senate) {
            queue.push(p);
            map[p].first++;
        }
        while (map[k_radiant].first > 0 && map[k_dire].first > 0) {
            const auto p = queue.front();
            queue.pop();
            if (map[p].second > 0) {
                map[p].second--;
                map[p].first--;
            } else {
                map[p == k_radiant ? k_dire : k_radiant].second++;
                queue.push(p);
            }
        }
        return map[k_radiant].first > 0 ? "Radiant" : "Dire";
    }
};