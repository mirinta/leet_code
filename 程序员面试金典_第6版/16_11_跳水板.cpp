#include <vector>

/**
 * 你正在使用一堆木板建造跳水板。
 * 有两种类型的木板，其中长度较短的木板长度为shorter，长度较长的木板长度为longer。
 * 你必须正好使用k块木板。编写一个方法，生成跳水板所有可能的长度。
 *
 * 返回的长度需要从小到大排列。
 *
 * ! 0 < shorter <= longer
 * ! 0 <= k <= 100000
 */

class Solution {
public:
    std::vector<int> divingBoard(int shorter, int longer, int k)
    {
        if (k == 0)
            return {};

        if (shorter == longer)
            return {shorter * k};

        std::vector<int> result;
        result.reserve(k + 1);
        for (int numOfLonger = 0; numOfLonger <= k; ++numOfLonger) {
            const int numOfShorter = k - numOfLonger;
            result.push_back(shorter * numOfShorter + longer * numOfLonger);
        }
        return result;
    }
};