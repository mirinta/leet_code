#include <algorithm>
#include <unordered_set>
#include <vector>

/**
 * There is a large (m - 1) x (n - 1) rectangular field with corners at (1, 1) and (m, n) containing
 * some horizontal and vertical fences given in arrays hFences and vFences respectively.
 *
 * Horizontal fences are from the coordinates (hFences[i], 1) to (hFences[i], n) and vertical fences
 * are from the coordinates (1, vFences[i]) to (m, vFences[i]).
 *
 * Return the maximum area of a square field that can be formed by removing some fences (possibly
 * none) or -1 if it is impossible to make a square field.
 *
 * Since the answer may be large, return it modulo 10^9 + 7.
 *
 * Note: The field is surrounded by two horizontal fences from the coordinates (1, 1) to (1, n) and
 * (m, 1) to (m, n) and two vertical fences from the coordinates (1, 1) to (m, 1) and (1, n) to (m,
 * n). These fences cannot be removed.
 *
 * ! 3 <= m, n <= 10^9
 * ! 1 <= hFences.length, vFences.length <= 600
 * ! 1 < hFences[i] < m
 * ! 1 < vFences[i] < n
 * ! hFences and vFences are unique.
 */

class Solution {
public:
    int maximizeSquareArea(int m, int n, std::vector<int>& hFences, std::vector<int>& vFences)
    {
        hFences.push_back(1);
        hFences.push_back(m);
        std::sort(hFences.begin(), hFences.end());
        std::unordered_set<long long> set;
        set.reserve(hFences.size() * hFences.size());
        for (int i = 0; i < hFences.size(); ++i) {
            for (int j = i + 1; j < hFences.size(); ++j) {
                set.insert(hFences[j] - hFences[i]);
            }
        }
        vFences.push_back(1);
        vFences.push_back(n);
        std::sort(vFences.begin(), vFences.end());
        long long result = -1;
        for (int i = 0; i < vFences.size(); ++i) {
            for (int j = i + 1; j < vFences.size(); ++j) {
                const long long length = vFences[j] - vFences[i];
                if (set.count(length)) {
                    result = std::max(result, length * length);
                }
            }
        }
        static constexpr long long kMod = 1e9 + 7;
        return result % kMod;
    }
};
