#include <unordered_map>
#include <vector>

/**
 * Definitions for a Node.
 */
class Node {
public:
    int val;
    std::vector<Node*> neighbors;
    Node()
    {
        val = 0;
        neighbors = std::vector<Node*>();
    }
    Node(int _val)
    {
        val = _val;
        neighbors = std::vector<Node*>();
    }
    Node(int _val, std::vector<Node*> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};

/**
 * Given a reference of a node in a connected undirected graph.
 *
 * Return a deep copy (clone) of the graph.
 *
 * Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.
 *
 * Test case format:
 *
 * For simplicity, each node's value is the same as the node's index (1-indexed). For example, the
 * first node with val == 1, the second node with val == 2, and so on. The graph is represented in
 * the test case using an adjacency list.
 *
 * An adjacency list is a collection of unordered lists used to represent a finite graph. Each list
 * describes the set of neighbors of a node in the graph.
 *
 * The given node will always be the first node with val = 1. You must return the copy of the given
 * node as a reference to the cloned graph.
 *
 * ! The number of nodes in the graph is in the range [0, 100].
 * ! 1 <= Node.val <= 100
 * ! Node.val is unique for each node.
 * ! There are no repeated edges and no self-loops in the graph.
 * ! The Graph is connected and all nodes can be visited starting from the given node.
 */

class Solution {
public:
    Node* cloneGraph(Node* node)
    {
        if (!node)
            return nullptr;

        // original node to copied node
        std::unordered_map<Node*, Node*> map;
        dfs(map, node);
        return map[node];
    }

    void dfs(std::unordered_map<Node*, Node*>& map, Node* node)
    {
        if (!node)
            return;

        if (map.count(node))
            return;

        map[node] = new Node(node->val);
        for (auto* neighbor : node->neighbors) {
            dfs(map, neighbor);
            map[node]->neighbors.push_back(map[neighbor]);
        }
    }
};
