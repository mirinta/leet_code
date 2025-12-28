#include <map>
#include <queue>
#include <vector>

/**
 * Given a list of the scores of different students, items, where items[i] = [IDi, scorei]
 * represents one score from a student with IDi, calculate each student's top five average.
 *
 * Return the answer as an array of pairs result, where result[j] = [IDj, topFiveAveragej]
 * represents the student with IDj and their top five average. Sort result by IDj in increasing
 * order.
 *
 * A student's top five average is calculated by taking the sum of their top five scores and
 * dividing it by 5 using integer division.
 *
 * ! 1 <= items.length <= 1000
 * ! items[i].length == 2
 * ! 1 <= IDi <= 1000
 * ! 0 <= scorei <= 100
 * ! For each IDi, there will be at least five scores.
 */

class Solution {
public:
    std::vector<std::vector<int>> highFive(std::vector<std::vector<int>>& items)
    {
        std::map<int, std::priority_queue<int, std::vector<int>, std::greater<>>> map;
        for (const auto& item : items) {
            map[item[0]].push(item[1]);
            if (map[item[0]].size() > 5) {
                map[item[0]].pop();
            }
        }
        std::vector<std::vector<int>> result;
        result.reserve(map.size());
        for (auto& [id, pq] : map) {
            int sum = 0;
            const int sz = pq.size();
            while (!pq.empty()) {
                sum += pq.top();
                pq.pop();
            }
            result.push_back({id, sum / sz});
        }
        return result;
    }
};