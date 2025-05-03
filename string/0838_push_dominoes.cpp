#include <string>
#include <vector>

/**
 * There are n dominoes in a line, and we place each domino vertically upright. In the beginning, we
 * simultaneously push some of the dominoes either to the left or to the right.
 *
 * After each second, each domino that is falling to the left pushes the adjacent domino on the
 * left. Similarly, the dominoes falling to the right push their adjacent dominoes standing on the
 * right.
 *
 * When a vertical domino has dominoes falling on it from both sides, it stays still due to the
 * balance of the forces.
 *
 * For the purposes of this question, we will consider that a falling domino expends no additional
 * force to a falling or already fallen domino.
 *
 * You are given a string dominoes representing the initial state where:
 *
 * - dominoes[i] = 'L', if the ith domino has been pushed to the left,
 *
 * - dominoes[i] = 'R', if the ith domino has been pushed to the right, and
 *
 * - dominoes[i] = '.', if the ith domino has not been pushed.
 *
 * Return a string representing the final state.
 *
 * ! n == dominoes.length
 * ! 1 <= n <= 10^5
 * ! dominoes[i] is either 'L', 'R', or '.'.
 */

class Solution
{
public:
    std::string pushDominoes(std::string dominoes)
    {
        const int n = dominoes.size();
        std::vector<int> forces(n, 0);
        for (int i = 0, f = 0; i < n; ++i) {
            if (dominoes[i] == 'R') {
                f = n;
            } else if (dominoes[i] == 'L') {
                f = 0;
            } else {
                f = std::max(0, f - 1);
            }
            forces[i] += f;
        }
        for (int i = n - 1, f = 0; i >= 0; --i) {
            if (dominoes[i] == 'L') {
                f = n;
            } else if (dominoes[i] == 'R') {
                f = 0;
            } else {
                f = std::max(0, f - 1);
            }
            forces[i] -= f;
        }
        std::string result;
        result.reserve(n);
        for (const auto& f : forces) {
            if (f > 0) {
                result.push_back('R');
            } else if (f < 0) {
                result.push_back('L');
            } else {
                result.push_back('.');
            }
        }
        return result;
    }
};
