#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given some lists of regions where the first region of each list includes all other
 * regions in that list.
 *
 * Naturally, if a region x contains another region y then x is bigger than y. Also, by definition,
 * a region x contains itself.
 *
 * Given two regions: region1 and region2, return the smallest region that contains both of them.
 *
 * If you are given regions r1, r2, and r3 such that r1 includes r3, it is guaranteed there is no r2
 * such that r2 includes r3.
 *
 * It is guaranteed the smallest region exists.
 *
 * ! 2 <= regions.length <= 104
 * ! 2 <= regions[i].length <= 20
 * ! 1 <= regions[i][j].length, region1.length, region2.length <= 20
 * ! region1 != region2
 * ! regions[i][j], region1, and region2 consist of English letters.
 */

class Solution {
public:
    std::string
        findSmallestRegion(std::vector<std::vector<std::string>>& regions, std::string region1, std::string region2)
    {
        std::unordered_map<std::string, std::string> map; // child to parent
        for (const auto& r : regions) {
            for (int i = 1; i < r.size(); ++i) {
                map[r[i]] = r[0];
            }
        }
        // find the intersection of two linked lists
        auto s1 = region1;
        auto s2 = region2;
        while (s1 != s2) {
            s1 = map.count(s1) ? map[s1] : region2;
            s2 = map.count(s2) ? map[s2] : region1;
        }
        return s1;
    }
};
