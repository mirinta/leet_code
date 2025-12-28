#include <string>

/**
 * The Solution classYou are given two positive integers x and y, denoting the number of coins with
 * values 75 and 10 respectively.
 *
 * Alice and Bob are playing a game. Each turn, starting with Alice, the player must pick up coins
 * with a total value 115. If the player is unable to do so, they lose the game.
 *
 * Return the name of the player who wins the game if both players play optimally.
 *
 * 1 <= x, y <= 100
 */

class Solution {
public:
    std::string losingPlayer(int x, int y)
    {
        // each player must pick 1x75 and 4x10
        if (x < 1 || y < 4)
            return "Bob";

        const int rounds = std::min(x, y / 4);
        if (rounds % 2)
            return "Alice";

        return "Bob";
    }
};
