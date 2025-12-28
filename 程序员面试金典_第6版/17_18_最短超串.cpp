#include <unordered_map>
#include <vector>

/**
 * 假设你有两个数组，一个长一个短，短的元素均不相同。找到长数组中包含短数组所有的元素的最短子数组，其出现顺序无关紧要。
 *
 * 返回最短子数组的左端点和右端点，如有多个满足条件的子数组，返回左端点最小的一个。若不存在，返回空数组。
 *
 * ! big.length <= 100000
 * ! 1 <= small.length <= 100000
 */

class Solution {
public:
    std::vector<int> shortestSeq(std::vector<int>& big, std::vector<int>& small)
    {
        const int n = big.size();
        std::unordered_map<int, int> map;
        for (const auto& val : small) {
            map[val]++;
        }
        int distinct = 0;
        int startIndex = -1;
        int minLength = INT_MAX;
        for (int left = 0, right = 0; right < n; ++right) {
            if (map.count(big[right]) && --map[big[right]] == 0) {
                distinct++;
            }
            while (distinct == map.size()) {
                const int L = right - left + 1;
                if (L < minLength) {
                    minLength = L;
                    startIndex = left;
                } else if (L == minLength && left < startIndex) {
                    startIndex = left;
                }
                if (map.count(big[left]) && map[big[left]]++ == 0) {
                    distinct--;
                }
                left++;
            }
        }
        if (minLength == INT_MAX)
            return {};

        return {startIndex, minLength + startIndex - 1};
    }
};