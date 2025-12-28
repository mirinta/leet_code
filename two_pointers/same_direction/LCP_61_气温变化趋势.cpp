#include <vector>

/**
 * 力扣城计划在两地设立「力扣嘉年华」的分会场，气象小组正在分析两地区的气温变化趋势，对于第 i ~
 * (i+1) 天的气温变化趋势，将根据以下规则判断：
 *
 * - 若第 i+1 天的气温 高于 第 i 天，为 上升 趋势
 *
 * - 若第 i+1 天的气温 等于 第 i 天，为 平稳 趋势
 *
 * - 若第 i+1 天的气温 低于 第 i 天，为 下降 趋势
 *
 * 已知 temperatureA[i] 和 temperatureB[i] 分别表示第 i 天两地区的气温。
 * 组委会希望找到一段天数尽可能多，且两地气温变化趋势相同的时间举办嘉年华活动。请分析并返回两地气温变化趋势相同的最大连续天数。
 *
 * - 即最大的 n，使得第 i~i+n 天之间，两地气温变化趋势相同
 *
 * ! 2 <= temperatureA.length == temperatureB.length <= 1000
 * ! -20 <= temperatureA[i], temperatureB[i] <= 40
 */

class Solution {
public:
    int temperatureTrend(std::vector<int>& temperatureA, std::vector<int>& temperatureB)
    {
        const int n = temperatureA.size();
        int i = 0;
        int result = 0;
        while (i < n) {
            int j = i + 1;
            int days = 0;
            while (j < n &&
                   compare(temperatureA[j], temperatureA[j - 1]) == compare(temperatureB[j], temperatureB[j - 1])) {
                j++;
                days++;
            }
            result = std::max(result, days);
            i = j;
        }
        return result;
    }

private:
    int compare(int a, int b)
    {
        if (a == b)
            return 0;

        return a > b ? 1 : -1;
    }
};