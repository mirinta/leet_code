#include <queue>
#include <string>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * 请实现两个函数，分别用来序列化和反序列化二叉树。
 *
 * 你需要设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，
 * 你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。
 *
 * ! 本题与LC 297相同。
 */

class Codec {
public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root)
    {
        std::string str;
        toString(str, root);
        return str;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string data)
    {
        std::queue<std::string> preorder;
        for (int end = 0, start = 0; end < data.size(); ++end) {
            if (data[end] == kSeparator) {
                preorder.push(data.substr(start, end - start));
                start = end + 1;
            }
        }
        return toTree(preorder);
    }

private:
    static constexpr char kSeparator = ',';
    const std::string kNull = "NULL";

    void toString(std::string& str, TreeNode* node)
    {
        if (!node) {
            str.append("NULL");
            str.push_back(',');
            return;
        }
        str.append(std::to_string(node->val));
        str.push_back(',');
        toString(str, node->left);
        toString(str, node->right);
    }

    TreeNode* toTree(std::queue<std::string>& preorder)
    {
        if (preorder.empty())
            return nullptr;

        const auto str = preorder.front();
        preorder.pop();
        if (str == kNull)
            return nullptr;

        auto* node = new TreeNode(std::stoi(str));
        node->left = toTree(preorder);
        node->right = toTree(preorder);
        return node;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));