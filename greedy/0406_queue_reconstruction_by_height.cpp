#include <algorithm>
#include <list>
#include <vector>

/**
 * You are given an array of people, people, which are the attributes of some people in a queue (not
 * necessarily in order). Each people[i] = [hi, ki] represents the ith person of height hi with
 * exactly ki other people in front who have a height greater than or equal to hi.
 *
 * Reconstruct and return the queue that is represented by the input array people. The returned
 * queue should be formatted as an array queue, where queue[j] = [hj, kj] is the attributes of the
 * jth person in the queue (queue[0] is the person at the front of the queue).
 *
 * ! 1 <= people.length <= 2000
 * ! 0 <= hi <= 10^6
 * ! 0 <= ki < people.length
 * ! It is guaranteed that the queue can be reconstructed.
 */

class Solution {
public:
    std::vector<std::vector<int>> reconstructQueue(std::vector<std::vector<int>>& people)
    {
        std::sort(people.begin(), people.end(), [](const auto& v1, const auto& v2) {
            if (v1[0] == v2[0])
                return v1[1] < v2[1];

            return v1[0] > v2[0];
        });
        std::list<std::vector<int>> list;
        for (const auto& v : people) {
            list.insert(std::next(list.begin(), v[1]), v);
        }
        return {list.begin(), list.end()};
    }
};