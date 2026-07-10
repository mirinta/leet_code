#include <string>
#include <vector>

/**
 * You are given a string s of length m consisting of digits. You are also given a 2D integer array queries, where
 * queries[i] = [li, ri].
 *
 * For each queries[i], extract the substring s[li..ri]. Then, perform the following:
 *
 * - Form a new integer x by concatenating all the non-zero digits from the substring in their original order. If there
 * are no non-zero digits, x = 0.
 *
 * - Let sum be the sum of digits in x. The answer is x * sum.
 *
 * Return an array of integers answer where answer[i] is the answer to the ith query.
 *
 * Since the answers may be very large, return the modulo 10^9 + 7.
 *
 * ! 1 <= m == s.length <= 10^5
 * ! s consists of digits only.
 * ! 1 <= queries.length <= 10^5
 * ! queries[i] = [li, ri]
 * ! 0 <= li <= ri < m
 */

class Solution {
public:
    std::vector<int> sumAndMultiply(std::string& s, std::vector<std::vector<int>>& queries)
    {
        static constexpr long long kMod = 1e9 + 7;
        static constexpr auto kPow10 = [&] {
            std::array<long long, 100001> result{};
            result[0] = 1;
            for (int i = 1; i < result.size(); ++i) {
                result[i] = result[i - 1] * 10 % kMod;
            }
            return result;
        }();
        // 0 ... L-1 L ... R ...
        // num[L:R] = num[0:R] - num[0:L-1] * 10^(R-L+1)
        const int n = s.size();
        std::vector<long long> presum1(n + 1, 0);
        std::vector<std::pair<long long, long long>> presum2(n + 1, {0, 0});
        for (int i = 1; i <= n; ++i) {
            const long long d = s[i - 1] - '0';
            presum1[i] = presum1[i - 1] + d;
            presum2[i] = presum2[i - 1];
            if (d) {
                presum2[i].first = (presum2[i].first * 10 % kMod + d) % kMod;
                presum2[i].second++;
            }
        }
        std::vector<int> result;
        result.reserve(queries.size());
        for (const auto& q : queries) {
            const auto& L = q[0];
            const auto& R = q[1];
            const auto length = presum2[R + 1].second - presum2[L].second;
            const long long x = (presum2[R + 1].first - presum2[L].first * kPow10[length] % kMod + kMod) % kMod;
            const long long sum = (presum1[R + 1] - presum1[L] + kMod) % kMod;
            result.emplace_back(x * sum % kMod);
        }
        return result;
    }
};