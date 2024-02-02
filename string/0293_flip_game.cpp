#include <string>
#include <vector>

/**
 * You are playing a Flip Game with your friend.
 *
 * You are given a string currentState that contains only '+' and '-'. You and your friend take
 * turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a
 * move, and therefore the other person will be the winner.
 *
 * Return all possible states of the string currentState after one valid move. You may return the
 * answer in any order. If there is no valid move, return an empty list [].
 *
 * ! 1 <= currentState.length <= 500
 * ! currentState[i] is either '+' or '-'.
 */

class Solution
{
public:
    std::vector<std::string> generatePossibleNextMoves(std::string currentState)
    {
        const int n = currentState.size();
        std::vector<std::string> result;
        for (int i = 1; i < n; ++i) {
            if (currentState[i] == currentState[i - 1] && currentState[i] == '+') {
                auto state = currentState;
                state[i] = '-';
                state[i - 1] = '-';
                result.push_back(std::move(state));
            }
        }
        return result;
    }
};