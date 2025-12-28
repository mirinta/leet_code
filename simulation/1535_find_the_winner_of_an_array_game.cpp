#include <queue>
#include <unordered_map>

/**
 * Given an integer array arr of distinct integers and an integer k.
 *
 * A game will be played between the first two elements of the array (i.e. arr[0] and arr[1]). In
 * each round of the game, we compare arr[0] with arr[1], the larger integer wins and remains at
 * position 0, and the smaller integer moves to the end of the array. The game ends when an integer
 * wins k consecutive rounds.
 *
 * Return the integer which will win the game.
 *
 * It is guaranteed that there will be a winner of the game.
 *
 * ! 2 <= arr.length <= 10^5
 * ! 1 <= arr[i] <= 10^6
 * ! arr contains distinct integers.
 * ! 1 <= k <= 10^9
 */

class Solution {
public:
    int getWinner(std::vector<int>& arr, int k)
    {
        return approach2(arr, k);
    }

private:
    // simulation, time O(N), space O(1)
    int approach2(const std::vector<int>& arr, int k)
    {
        const int maxValue = *std::max_element(arr.begin(), arr.end());
        const int n = arr.size();
        int current = arr[0];
        int currentWins = 0;
        for (int i = 1; i < n; ++i) {
            if (current > arr[i]) {
                currentWins++;
            } else {
                current = arr[i];
                currentWins = 1;
            }
            if (currentWins >= k || current == maxValue)
                return current;
        }
        return -1;
    }

    // simulation using deque, time O(N), space O(N)
    int approach1(const std::vector<int>& arr, int k)
    {
        std::unordered_map<int, int> map; // value to win_count
        std::deque<int> deque;
        int maxValue = INT_MIN;
        for (const auto& val : arr) {
            deque.push_back(val);
            maxValue = std::max(maxValue, val);
        }
        while (deque.size() >= 2) {
            const auto val1 = deque.front();
            deque.pop_front();
            const auto val2 = deque.front();
            deque.pop_front();
            const auto winner = std::max(val1, val2);
            const auto loser = std::min(val1, val2);
            map[winner]++;
            if (map[winner] >= k || winner == maxValue)
                return winner;

            deque.push_front(winner);
            deque.push_back(loser);
        }
        return -1;
    }
};