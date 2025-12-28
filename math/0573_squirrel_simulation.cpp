#include <vector>

/**
 * You are given two integers height and width representing a garden of size height x width. You are
 * also given:
 *
 * - an array tree where tree = [treer, treec] is the position of the tree in the garden,
 *
 * - an array squirrel where squirrel = [squirrelr, squirrelc] is the position of the squirrel in
 * the garden,
 *
 * - and an array nuts where nuts[i] = [nutir, nutic] is the position of the ith nut in the garden.
 *
 * The squirrel can only take at most one nut at one time and can move in four directions: up, down,
 * left, and right, to the adjacent cell.
 *
 * Return the minimal distance for the squirrel to collect all the nuts and put them under the tree
 * one by one.
 *
 * The distance is the number of moves.
 *
 * ! 1 <= height, width <= 100
 * ! tree.length == 2
 * ! squirrel.length == 2
 * ! 1 <= nuts.length <= 5000
 * ! nuts[i].length == 2
 * ! 0 <= treer, squirrelr, nutir <= height
 * ! 0 <= treec, squirrelc, nutic <= width
 */

class Solution {
public:
    int minDistance(int height,
                    int width,
                    std::vector<int>& tree,
                    std::vector<int>& squirrel,
                    std::vector<std::vector<int>>& nuts)
    {
        // assume the squirrel picks nuts[i] at first
        // - pick nuts[i] and put it under the tree, dist = manhattan(nuts[i],tree) +
        // manhattan(nuts[i],squirrel)
        // - for each of the remaining nuts, dist = 2*manhattan(nuts[j!=i],tree)
        // thus, total dist =
        // sum(2*manhattan(nuts[k],tree))-(manhattan(nuts[i],tree)-manhattan(nuts[i],squirrel))
        int total = 0;
        int delta = INT_MIN;
        for (const auto& nut : nuts) {
            total += 2 * manhattan(nut, tree);
            delta = std::max(delta, manhattan(nut, tree) - manhattan(nut, squirrel));
        }
        return total - delta;
    }

private:
    int manhattan(const std::vector<int>& p1, const std::vector<int>& p2)
    {
        return std::abs(p1[0] - p2[0]) + std::abs(p1[1] - p2[1]);
    }
};
