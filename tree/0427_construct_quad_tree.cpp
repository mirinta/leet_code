#include <vector>

/**
 * Definition for a QuadTree node.
 */
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node()
    {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf)
    {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight)
    {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

/**
 * Given a n * n matrix grid of 0's and 1's only. We want to represent grid with a Quad-Tree.
 *
 * Return the root of the Quad-Tree representing grid.
 *
 * A Quad-Tree is a tree data structure in which each internal node has exactly four children.
 * Besides, each node has two attributes:
 *
 * - val: True if the node represents a grid of 1's or False if the node represents a grid of 0's.
 * Notice that you can assign the val to True or False when isLeaf is False, and both are accepted
 * in the answer.
 *
 * - isLeaf: True if the node is a leaf node on the tree or False if the node has four children.
 *
 * We can construct a Quad-Tree from a two-dimensional area using the following steps:
 *
 * 1. If the current grid has the same value (i.e all 1's or all 0's) set isLeaf True and set val to
 * the value of the grid and set the four children to Null and stop.
 *
 * 2. If the current grid has different values, set isLeaf to False and set val to any value and
 * divide the current grid into four sub-grids as shown in the photo.
 *
 * 3. Recurse for each of the children with the proper sub-grid.
 *
 * ! n == grid.length == grid[i].length
 * ! n == 2^x where 0 <= x <= 6
 */

class Solution {
public:
    Node* construct(std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        return build(0, n - 1, 0, n - 1, grid);
    }

private:
    Node* build(int rowStart, int rowEnd, int colStart, int colEnd, const std::vector<std::vector<int>>& grid)
    {
        if (rowStart == rowEnd && colStart == colEnd)
            return new Node(grid[rowStart][colStart], true);

        const int rowMid = rowStart + (rowEnd - rowStart) / 2;
        const int colMid = colStart + (colEnd - colStart) / 2;
        auto* topLeft = build(rowStart, rowMid, colStart, colMid, grid);
        auto* topRight = build(rowStart, rowMid, colMid + 1, colEnd, grid);
        auto* bottomLeft = build(rowMid + 1, rowEnd, colStart, colMid, grid);
        auto* bottomRight = build(rowMid + 1, rowEnd, colMid + 1, colEnd, grid);
        if (allLeafWIthSameValue(topLeft, topRight, bottomLeft, bottomRight))
            return new Node(topLeft->val, true);

        return new Node(false, false, topLeft, topRight, bottomLeft, bottomRight);
    }

    bool allLeafWIthSameValue(Node* topLeft, Node* topRight, Node* bottomLeft, Node* bottomRight)
    {
        int val = topLeft->val;
        for (auto* node : {topLeft, topRight, bottomLeft, bottomRight}) {
            if (!node->isLeaf || node->val != val)
                return false;
        }
        return true;
    }
};