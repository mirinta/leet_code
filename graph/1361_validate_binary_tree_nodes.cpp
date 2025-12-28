#include <queue>
#include <vector>

/**
 * You have n binary tree nodes numbered from 0 to n - 1 where node i has two children leftChild[i]
 * and rightChild[i], return true if and only if all the given nodes form exactly one valid binary
 * tree.
 *
 * If node i has no left child then leftChild[i] will equal -1, similarly for the right child.
 *
 * Note that the nodes have no values and that we only use the node numbers in this problem.
 *
 * ! n == leftChild.length == rightChild.length
 * ! 1 <= n <= 10^4
 * ! -1 <= leftChild[i], rightChild[i] <= n - 1
 */

class Solution {
public:
    bool validateBinaryTreeNodes(int n, std::vector<int>& leftChild, std::vector<int>& rightChild)
    {
        // topological sorting, Kahn's algorithm
        std::vector<int> parent(n, -1);
        std::vector<int> indegrees(n, 0);
        for (int i = 0; i < n; ++i) {
            for (const auto& j : {leftChild[i], rightChild[i]}) {
                if (j == -1)
                    continue;

                // each node except the root node has and only has one parent node
                // left.parent == right.parent
                if (parent[j] != -1 && parent[j] != i)
                    return false;

                parent[j] = i;
                indegrees[j]++;
            }
        }
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            if (indegrees[i] == 0) {
                queue.push(i);
            }
        }
        // a valid binary has and only has one root node
        if (queue.size() > 1)
            return false;

        int count = 0;
        while (!queue.empty()) {
            const auto v = queue.front();
            queue.pop();
            count++;
            for (const auto& adj : {leftChild[v], rightChild[v]}) {
                if (adj == -1)
                    continue;

                if (--indegrees[adj] == 0) {
                    queue.push(adj);
                }
            }
        }
        return count == n;
    }
};
