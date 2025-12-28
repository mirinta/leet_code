#include <algorithm>
#include <queue>
#include <vector>

/**
 * You are given an integer array deck. There is a deck of cards where every card has a unique
 * integer. The integer on the ith card is deck[i].
 *
 * You can order the deck in any order you want. Initially, all the cards start face down
(unrevealed)
 * in one deck.
 *
 * You will do the following steps repeatedly until all cards are revealed:
 *
 * 1. Take the top card of the deck, reveal it, and take it out of the deck.
 *
 * 2. If there are still cards in the deck then put the next top card of the deck at the bottom of
 * the deck.
 *
 * 3. If there are still unrevealed cards, go back to step 1. Otherwise, stop.
 *
 * Return an ordering of the deck that would reveal the cards in increasing order.
 *
 * Note that the first entry in the answer is considered to be the top of the deck.
 *
 * ! 1 <= deck.length <= 1000
 * ! 1 <= deck[i] <= 10^6
 * ! All the values of deck are unique.
 */

class Solution {
public:
    std::vector<int> deckRevealedIncreasing(std::vector<int>& deck)
    {
        const int n = deck.size();
        std::sort(deck.begin(), deck.end());
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            queue.push(i);
        }
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            const int j = queue.front();
            queue.pop();
            result[j] = deck[i];
            if (queue.size() > 1) {
                queue.push(queue.front());
                queue.pop();
            }
        }
        return result;
    }
};