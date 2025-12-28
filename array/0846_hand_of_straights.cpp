#include <set>
#include <vector>

/**
 * Alice has some number of cards and she wants to rearrange the cards into groups so that each
 * group is of size groupSize, and consists of groupSize consecutive cards.
 *
 * Given an integer array hand where hand[i] is the value written on the ith card and an integer
 * groupSize, return true if she can rearrange the cards, or false otherwise.
 *
 * ! 1 <= hand.length <= 10^4
 * ! 0 <= hand[i] <= 10^9
 * ! 1 <= groupSize <= hand.length
 *
 * ! This problem is the same as 1296.
 */

class Solution {
public:
    bool isNStraightHand(std::vector<int>& hand, int groupSize)
    {
        const int n = hand.size();
        if (n % groupSize)
            return false;

        std::multiset<int> set(hand.begin(), hand.end());
        for (int i = 0; i < n / groupSize; ++i) {
            const int min = *set.begin();
            for (int val = min; val <= min + groupSize - 1; ++val) {
                auto iter = set.find(val);
                if (iter == set.end())
                    return false;

                set.erase(iter);
            }
        }
        return true;
    }
};