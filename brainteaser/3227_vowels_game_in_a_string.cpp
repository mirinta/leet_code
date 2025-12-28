#include <string>

/**
 * Alice and Bob are playing a game on a string.
 *
 * You are given a string s, Alice and Bob will take turns playing the following game where Alice
 * starts first:
 *
 * - On Alice's turn, she has to remove any non-empty substring from s that contains an odd number
 * of vowels.
 *
 * - On Bob's turn, he has to remove any non-empty substring from s that contains an even number of
 * vowels.
 *
 * The first player who cannot make a move on their turn loses the game. We assume that both
 * Alice and Bob play optimally.
 *
 * Return true if Alice wins the game, and false otherwise.
 *
 * The English vowels are: a, e, i, o, and u.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    bool doesAliceWin(std::string s)
    {
        // case 1: no vowels, Alice loses
        // case 2: odd vowels, Alice can remove the entire string, Alice wins
        // case 3: even vowels
        // - 1st round, Alice removes odd num of vowels, remaining odd num of vowels
        // - 2st round, Bob removes even num of vowels, remaining odd num of vowels
        // - 3st round, Alice removes the remaining string, Alice wins
        // therefore, if num of vowels > 0, Alice wins
        for (const auto& c : s) {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
                return true;
        }
        return false;
    }
};