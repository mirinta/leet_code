#include <algorithm>
#include <vector>

/**
 * 堆箱子。给你一堆n个箱子，箱子宽 wi、深 di、高 hi。
 * 箱子不能翻转，将箱子堆起来时，下面箱子的宽度、高度和深度必须大于上面的箱子。
 * 实现一种方法，搭出最高的一堆箱子。箱堆的高度为每个箱子高度的总和。
 *
 * 输入使用数组[wi, di, hi]表示每个箱子。
 *
 * ! 箱子的数目不大于3000个。
 */

class Solution {
public:
    int pileBox(std::vector<std::vector<int>>& box)
    {
        // dp[i] = max height of subsequences of box[0:i] ending at box[i]
        const int n = box.size();
        std::sort(box.begin(), box.end(), [](const auto& b1, const auto& b2) { return b1[0] < b2[0]; });
        std::vector<int> dp(n);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            dp[i] = box[i][2];
            for (int j = i - 1; j >= 0; --j) {
                if (box[i][0] > box[j][0] && box[i][1] > box[j][1] && box[i][2] > box[j][2]) {
                    dp[i] = std::max(dp[i], dp[j] + box[i][2]);
                }
            }
            result = std::max(result, dp[i]);
        }
        return result;
    }
};