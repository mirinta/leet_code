#include <functional>
#include <vector>

/**
 * Given an integer n, find a sequence that satisfies all of the following:
 *
 * - The integer 1 occurs once in the sequence.
 *
 * - Each integer between 2 and n occurs twice in the sequence.
 *
 * - For every integer i between 2 and n, the distance between the two occurrences of i is exactly
 * i.
 *
 * The distance between two numbers on the sequence, a[i] and a[j], is the absolute difference of
 * their indices, |j - i|.
 *
 * Return the lexicographically largest sequence. It is guaranteed that under the given constraints,
 * there is always a solution.
 *
 * A sequence a is lexicographically larger than a sequence b (of the same length) if in the first
 * position where a and b differ, sequence a has a number greater than the corresponding number in
 * b. For example, [0,1,9,0] is lexicographically larger than [0,1,5,6] because the first position
 * they differ is at the third number, and 9 is greater than 5.
 *
 * ! 1 <= n <= 20
 */

class Solution {
public:
    std::vector<int> constructDistancedSequence(int n)
    {
        const int m = 2 * n - 1;
        std::vector<int> current(m);
        std::vector<bool> used(n + 1, false);
        std::vector<int> result;
        std::function<bool(int)> dfs = [&](int i) {
            if (i == m) {
                result = std::max(result, current);
                return true;
            }
            if (current[i] != 0)
                return dfs(i + 1);

            for (int val = n; val >= 1; --val) {
                if (used[val])
                    continue;

                if (val > 1 && i + val >= m)
                    continue;

                if (val > 1 && current[i + val] != 0)
                    continue;

                current[i] = val;
                used[val] = true;
                if (val > 1) {
                    current[i + val] = val;
                }
                if (dfs(i + 1))
                    return true;

                current[i] = 0;
                used[val] = false;
                if (val > 1) {
                    current[i + val] = 0;
                }
            }
            return false;
        };
        dfs(0);
        return result;
    }
};