#include <unordered_set>
#include <vector>

/**
 * 从若干副扑克牌中随机抽 5 张牌，判断是不是一个顺子，即这5张牌是不是连续的。
 *
 * 2～10为数字本身，A为1，J为11，Q为12，K为13，而大、小王为 0 ，可以看成任意数字。
 *
 * A 不能视为 14。
 *
 * ! 数组长度为 5
 * ! 数组的数取值为 [0, 13]
 */

class Solution {
public:
    bool isStraight(std::vector<int>& nums)
    {
        // x1 x2 x3 x4 x5
        // - if it is straight without any zero,
        //   then diff = max(x1...x5) - min(x1...x5) = 4
        // - if it is straight with zeros, then diff < 4
        std::unordered_set<int> cards;
        int min = INT_MAX;
        int max = INT_MIN;
        for (const auto& val : nums) {
            if (val == 0)
                continue;

            if (cards.count(val))
                return false;

            cards.insert(val);
            min = std::min(min, val);
            max = std::max(max, val);
        }
        return max - min <= 4;
    }
};