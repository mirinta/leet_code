#include <queue>
#include <string>
#include <vector>

/**
 * Serialization is the process of converting a data structure or object into a sequence of bits so
 * that it can be stored in a file or memory buffer, or transmitted across a network connection link
 * to be reconstructed later in the same or another computer environment.
 *
 * Design an algorithm to serialize and deserialize an N-ary tree. An N-ary tree is a rooted tree in
 * which each node has no more than N children. There is no restriction on how your
 * serialization/deserialization algorithm should work. You just need to ensure that an N-ary tree
 * can be serialized to a string and this string can be deserialized to the original tree structure.
 *
 * ! The number of nodes in the tree is in the range [0, 10^4].
 * ! 0 <= Node.val <= 10^4
 * ! The height of the n-ary tree is less than or equal to 1000
 * ! Do not use class member/global/static variables to store states. Your encode and decode
 * ! algorithms should be stateless.
 */

/**
 * Definition for a Node.
 */
class Node {
public:
    int val;
    std::vector<Node*> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, std::vector<Node*> _children)
    {
        val = _val;
        children = _children;
    }
};

class Codec {
public:
    // Encodes a tree to a single string.
    std::string serialize(Node* root)
    {
        if (!root)
            return {};

        std::string result;
        result.append(std::to_string(root->val));
        result.push_back('#');
        std::queue<Node*> queue;
        queue.push(root);
        while (!queue.empty()) {
            for (int i = queue.size(); i > 0; --i) {
                auto* node = queue.front();
                queue.pop();
                for (int child = 0; child < node->children.size(); ++child) {
                    result.append(std::to_string(node->children[child]->val));
                    if (child != node->children.size() - 1) {
                        result.push_back(',');
                    }
                    queue.push(node->children[child]);
                }
                result.push_back('#');
            }
        }
        return result;
    }

    // Decodes your encoded data to tree.
    Node* deserialize(std::string data)
    {
        if (data.empty())
            return nullptr;

        // 1#2,3,4,5##6,7#8#9,10##11#12#13##14####
        int i = 0;
        auto parseNodes = [&i, &data]() {
            std::vector<Node*> nodes;
            int val = 0;
            while (i < data.size() && data[i] != '#') {
                while (i < data.size() && std::isdigit(data[i])) {
                    val = val * 10 + (data[i] - '0');
                    i++;
                } // data[i] is either '#' or ','
                nodes.push_back(new Node(val));
                if (i < data.size() && data[i] == ',') {
                    i++;
                    val = 0;
                }
            }
            i++;
            return nodes;
        };
        auto* root = parseNodes()[0];
        std::queue<Node*> queue;
        queue.push(root);
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                auto* node = queue.front();
                queue.pop();
                node->children = parseNodes();
                for (auto* child : node->children) {
                    queue.push(child);
                }
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));