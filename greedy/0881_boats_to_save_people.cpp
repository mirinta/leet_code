#include <algorithm>
#include <vector>

/**
 * You are given an array people where people[i] is the weight of the ith person, and an infinite
 * number of boats where each boat can carry a maximum weight of limit. Each boat carries at most
 * two people at the same time, provided the sum of the weight of those people is at most limit.
 *
 * Return the minimum number of boats to carry every given person.
 *
 * ! 1 <= people.length <= 5 * 10^4
 * ! 1 <= people[i] <= limit <= 3 * 10^4
 */

class Solution {
public:
    int numRescueBoats(std::vector<int>& people, int limit)
    {
        const int n = people.size();
        std::sort(people.begin(), people.end());
        int i = 0;
        int j = n - 1;
        int result = 0;
        while (i <= j) {
            result++;
            if (people[i] + people[j] <= limit) {
                i++;
            }
            j--;
        }
        return result;
    }
};