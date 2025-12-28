#include <vector>

/**
 * You are given an array arr of positive integers. You are also given the array queries where
 * queries[i] = [lefti, righti].
 *
 * For each query i compute the XOR of elements from lefti to righti (that is, arr[lefti] XOR
 * arr[lefti + 1] XOR ... XOR arr[righti] ).
 *
 * Return an array answer where answer[i] is the answer to the ith query.
 *
 * ! 1 <= arr.length, queries.length <= 3 * 10^4
 * ! 1 <= arr[i] <= 10^9
 * ! queries[i].length == 2
 * ! 0 <= lefti <= righti < arr.length
 */

class Solution {
public:
    std::vector<int> xorQueries(std::vector<int>& arr, std::vector<std::vector<int>>& queries)
    {
        // prexor[i] = arr[0] ^ arr[1] ^ ... ^ arr[i-1]
        const int n = arr.size();
        std::vector<int> prexor(n + 1);
        for (int i = 1; i <= n; ++i) {
            prexor[i] = prexor[i - 1] ^ arr[i - 1];
        }
        std::vector<int> result;
        result.reserve(queries.size());
        for (const auto& q : queries) {
            result.push_back(prexor[q[1] + 1] ^ prexor[q[0]]);
        }
        return result;
    }
};
