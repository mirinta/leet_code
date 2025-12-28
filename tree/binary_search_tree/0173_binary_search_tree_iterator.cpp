#include <stack>
#include <vector>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * Implement the BSTIterator class that represents an iterator over the in-order traversal of a
 * binary search tree (BST):
 *
 * - BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The root of the BST
 * is given as part of the constructor. The pointer should be initialized to a non-existent number
 * smaller than any element in the BST.
 *
 * - boolean hasNext() Returns true if there exists a number in the traversal to the right of the
 * pointer, otherwise returns false.
 *
 * - int next() Moves the pointer to the right, then returns the number at the pointer.
 *
 * Notice that by initializing the pointer to a non-existent smallest number, the first call to
 * next() will return the smallest element in the BST.
 *
 * You may assume that next() calls will always be valid. That is, there will be at least a next
 * number in the in-order traversal when next() is called.
 *
 * ! The number of nodes in the tree is in the range [1, 10^5].
 * ! 0 <= Node.val <= 10^6
 * ! At most 10^5 calls will be made to hasNext, and next.
 */

class BSTIterator {
public:
    BSTIterator(TreeNode* root)
    {
        traverseLeft(root);
    }

    int next()
    {
        if (!hasNext())
            return -1;

        auto* node = stack.top();
        stack.pop();
        traverseLeft(node->right);
        return node->val;
    }

    bool hasNext()
    {
        return !stack.empty();
    }

private:
    void traverseLeft(TreeNode* node)
    {
        if (!node)
            return;

        while (node) {
            stack.push(node);
            node = node->left;
        }
    }

private:
    std::stack<TreeNode*> stack;
};

class BSTIterator2 {
public:
    BSTIterator2(TreeNode* root)
    {
        std::stack<TreeNode*> stack;
        auto* current = root;
        while (current || !stack.empty()) {
            while (current) {
                stack.push(current);
                current = current->left;
            }
            nums.push_back(stack.top()->val);
            current = stack.top()->right;
            stack.pop();
        }
    }

    int next()
    {
        if (hasNext())
            return nums[index++];

        return -1;
    }

    bool hasNext()
    {
        return index < nums.size();
    }

private:
    int index = 0;
    std::vector<int> nums;
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */