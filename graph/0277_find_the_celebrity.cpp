#include <vector>

/**
 * The knows API is defined as follows.
 */
bool knows(int a, int b);

/**
 * Suppose you are at a party with n people labeled from 0 to n - 1 and among them, there may exist
 * one celebrity. The definition of a celebrity is that all the other n - 1 people know the
 * celebrity, but the celebrity does not know any of them.
 *
 * Now you want to find out who the celebrity is or verify that there is not one. You are only
 * allowed to ask questions like: "Hi, A. Do you know B?" to get information about whether A knows
 * B. You need to find out the celebrity (or verify there is not one) by asking as few questions as
 * possible (in the asymptotic sense).
 *
 * You are given a helper function bool knows(a, b) that tells you whether a knows b. Implement a
 * function int findCelebrity(n). There will be exactly one celebrity if they are at the party.
 *
 * Return the celebrity's label if there is a celebrity at the party. If there is no celebrity,
 * return -1.
 *
 * ! n == graph.length == graph[i].length
 * ! 2 <= n <= 100
 * ! graph[i][j] is 0 or 1.
 * ! graph[i][i] == 1
 *
 * ! If the maximum number of allowed calls to the API "knows" is 3 * n.
 * ! Could you find a solution without exceeding the maximum number of calls?
 */

class Solution {
public:
    int findCelebrity(int n)
    {
        return approach2(n);
    }

private:
    int approach2(int n)
    {
        int result = 0;
        for (int i = 1; i < n; ++i) {
            if (knows(result, i)) {
                result = i;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (i == result)
                continue;

            if (knows(result, i) || !knows(i, result))
                return -1;
        }
        return result;
    }

    int approach1(int n)
    {
        std::vector<int> degrees(n, 0); // in - out
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (knows(i, j)) {
                    degrees[i]--;
                    degrees[j]++;
                }
                if (knows(j, i)) {
                    degrees[j]--;
                    degrees[i]++;
                }
            }
        }
        int result = -1;
        for (int i = 0; i < n; ++i) {
            if (degrees[i] != n - 1)
                continue;

            if (result != -1)
                return -1;

            result = i;
        }
        return result;
    }
};
