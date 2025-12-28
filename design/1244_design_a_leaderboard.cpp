#include <numeric>
#include <set>
#include <unordered_map>

/**
 * Design a Leaderboard class, which has 3 functions:
 *
 * 1. addScore(playerId, score): Update the leaderboard by adding score to the given player's score.
 * If there is no player with such id in the leaderboard, add him to the leaderboard with the given
 * score.
 *
 * 2. top(K): Return the score sum of the top K players.
 *
 * 3. reset(playerId): Reset the score of the player with the given id to 0 (in other words erase it
 * from the leaderboard). It is guaranteed that the player was added to the leaderboard before
 * calling this function.
 *
 * Initially, the leaderboard is empty.
 *
 * ! 1 <= playerId, K <= 10000
 * ! It's guaranteed that K is less than or equal to the current number of players.
 * ! 1 <= score <= 100
 * ! There will be at most 1000 function calls.
 */

class Leaderboard {
public:
    Leaderboard() {}

    void addScore(int playerId, int score)
    {
        if (map.count(playerId)) {
            set.erase(set.find(map[playerId]));
        }
        map[playerId] += score;
        set.insert(map[playerId]);
    }

    int top(int K)
    {
        const int k = std::min<int>(K, set.size());
        return std::accumulate(set.begin(), std::next(set.begin(), k), 0);
    }

    void reset(int playerId)
    {
        if (!map.count(playerId))
            return;

        set.erase(set.find(map[playerId]));
        map.erase(playerId);
    }

private:
    std::unordered_map<int, int> map;
    std::multiset<int, std::greater<>> set;
};

/**
 * Your Leaderboard object will be instantiated and called as such:
 * Leaderboard* obj = new Leaderboard();
 * obj->addScore(playerId,score);
 * int param_2 = obj->top(K);
 * obj->reset(playerId);
 */