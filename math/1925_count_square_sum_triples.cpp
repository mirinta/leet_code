#include <cmath>

/**
 * A square triple (a,b,c) is a triple where a, b, and c are integers and a2 + b2 = c2.
 *
 * Given an integer n, return the number of square triples such that 1 <= a, b, c <= n.
 *
 * ! 1 <= n <= 250
 */

class Solution {
public:
    int countTriples(int n)
    {
        int result = 0;
        for (int a = 1; a <= n; ++a) {
            for (int b = 1; b <= n; ++b) {
                const int c = std::ceil(std::sqrt(a * a + b * b));
                if (c <= n && c * c == a * a + b * b) {
                    result++;
                }
            }
        }
        return result;
    }
};