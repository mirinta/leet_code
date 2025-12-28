#include <queue>
#include <string>

/**
 * Definition of a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * Serialization is the process of converting a data structure or object into a sequence of bits so
 * that it can be stored in a file or memory buffer, or transmitted across a network connection link
 * to be reconstructed later in the same or another computer environment.
 *
 * Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how
 * your serialization/deserialization algorithm should work. You just need to ensure that a binary
 * tree can be serialized to a string and this string can be deserialized to the original tree
 * structure.
 *
 * Clarification: The input/output format is the same as how LeetCode serializes a binary tree. You
 * do not necessarily need to follow this format, so please be creative and come up with different
 * approaches yourself.
 *
 * ! The number of nodes in the tree is in the range [0, 10^4].
 * ! -1000 <= Node.val <= 1000
 */

/**
 *    Serialize to                          |   Can deserialize to unique binary tree
 * ------------------------------------------------------------------------------------
 * 1. one traversal order w/o nullptr info  |   NO
 * 2. preorder + inorder w/o nullptr info   |   YES
 * 3. postorder + inorder w/o nullptr info  |   YES
 * 4. preorder + postorder w/o nullptr info |   YES (if all the values are unique)
 * 5. preorder w/ nullptr info              |   YES
 * 6. postorder w/ nullptr info             |   YES
 * 7. inorder w/ nullptr info               |   YES (if all the values are unique)
 */

class Codec {
public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root)
    {
        if (!root)
            return {};

        std::string s;
        _serialize(s, root);
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string data)
    {
        if (data.empty())
            return nullptr;

        std::queue<std::string> preorder;
        for (int i = 0, j = 0; j < data.size(); ++j) {
            if (data[j] == kComma) {
                preorder.push(data.substr(i, j - i));
                i = j + 1;
            }
        }
        return _deserialize(preorder);
    }

private:
    void _serialize(std::string& s, TreeNode* root)
    {
        if (!root) {
            s.push_back(kNull);
            s.push_back(kComma);
            return;
        }
        s.append(std::to_string(root->val));
        s.push_back(kComma);
        _serialize(s, root->left);
        _serialize(s, root->right);
    }

    TreeNode* _deserialize(std::queue<std::string>& preorder)
    {
        if (preorder.empty())
            return nullptr;

        if (preorder.front().size() == 1 && preorder.front()[0] == kNull) {
            preorder.pop();
            return nullptr;
        }
        TreeNode* root = new TreeNode(std::stoi(preorder.front()));
        preorder.pop();
        root->left = _deserialize(preorder);
        root->right = _deserialize(preorder);
        return root;
    }

private:
    static constexpr char kNull = '#';
    static constexpr char kComma = ',';
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));