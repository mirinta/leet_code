#include <array>
#include <vector>

/**
 * 给定 N 个人的出生年份和死亡年份，第 i 个人的出生年份为 birth[i]，死亡年份为
 * death[i]，实现一个方法以计算生存人数最多的年份。
 *
 * 你可以假设所有人都出生于 1900 年至 2000 年（含 1900 和 2000）之间。
 * 如果一个人在某一年的任意时期处于生存状态，那么他应该被纳入那一年的统计中。例如，生于 1908
 * 年、死于 1909 年的人应当被列入 1908 年和 1909 年的计数。
 *
 * 如果有多个年份生存人数相同且均为最大值，输出其中最小的年份。
 *
 * ! 0 < birth.length == death.length <= 10000
 * ! birth[i] <= death[i]
 */

class Solution {
public:
    int maxAliveYear(std::vector<int>& birth, std::vector<int>& death)
    {
        constexpr int offset = 1900;
        std::array<int, 101> diff{};
        const int n = birth.size();
        for (int i = 0; i < n; ++i) {
            diff[birth[i] - offset]++;
            if (death[i] + 1 - offset < 101) {
                diff[death[i] + 1 - offset]--;
            }
        }
        int maxFreq = 0;
        int maxIndex = -1;
        for (int i = 0; i < 101; ++i) {
            diff[i] += i > 0 ? diff[i - 1] : 0;
            if (diff[i] > maxFreq) {
                maxFreq = diff[i];
                maxIndex = i;
            }
        }
        return maxIndex + offset;
    }
};