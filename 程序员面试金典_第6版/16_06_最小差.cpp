#include <algorithm>
#include <vector>

/**
 * 给定两个整数数组a和b，计算具有最小差绝对值的一对数值（每个数组中取一个值），并返回该对数值的差
 *
 * ! 1 <= a.length, b.length <= 100000
 * ! -2147483648 <= a[i], b[i] <= 2147483647
 * ! 正确结果在区间 [0, 2147483647] 内
 */

class Solution {
public:
    int smallestDifference(std::vector<int>& a, std::vector<int>& b)
    {
        if (a.size() > b.size())
            return smallestDifference(b, a);

        std::sort(a.begin(), a.end());
        long long result = INT_MAX;
        for (const auto& val : b) {
            auto ge = std::lower_bound(a.begin(), a.end(), val);
            if (ge != a.end()) {
                result = std::min(result, *ge - static_cast<long long>(val));
            }
            auto gt = std::upper_bound(a.begin(), a.end(), val);
            if (gt != a.begin()) {
                result = std::min(result, static_cast<long long>(val) - *std::prev(gt));
            }
            if (result == 0)
                break;
        }
        return result;
    }
};