#include <stack>
#include <vector>

/**
 * You are given an integer array nums.
 *
 * From any index i, you can jump to another index j under the following rules:
 *
 * - Jump to index j where j > i is allowed only if nums[j] < nums[i].
 *
 * - Jump to index j where j < i is allowed only if nums[j] > nums[i].
 *
 * For each index i, find the maximum value in nums that can be reached by following any sequence of valid jumps
 * starting at i.
 *
 * Return an array ans where ans[i] is the maximum value reachable starting from index i.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution {
public:
    std::vector<int> maxValue(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    std::vector<int> approach2(const std::vector<int>& nums)
    {
        // case 1:
        // if prefixMax[i] <= suffixMin[i+1], then i can not jump to [i+1,n-1]
        // thus, answer[i] = prefix[i]
        // case 2:
        // if prefixMax[i] > suffixMin[i+1], then i can jump to the index of prefixMax[i], then jump to i+1
        // thus, answer[i] = answer[i+1]
        const int n = nums.size();
        std::vector<int> prefixMax(n);
        prefixMax[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            prefixMax[i] = std::max(prefixMax[i - 1], nums[i]);
        }
        std::vector<int> suffixMin(n);
        suffixMin[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffixMin[i] = std::min(suffixMin[i + 1], nums[i]);
        }
        std::vector<int> result(n);
        result[n - 1] = prefixMax[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            if (prefixMax[i] <= suffixMin[i + 1]) {
                result[i] = prefixMax[i];
            } else {
                result[i] = result[i + 1];
            }
        }
        return result;
    }

    std::vector<int> approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> root(n);
        for (int i = 0; i < n; ++i) {
            root[i] = i;
        }
        std::function<int(int)> find = [&](int x) {
            if (root[x] != x) {
                root[x] = find(root[x]);
            }
            return root[x];
        };
        std::function<void(int, int)> connect = [&](int p, int q) {
            int rootP = find(p);
            int rootQ = find(q);
            if (rootP == rootQ)
                return;

            if (nums[rootQ] > nums[rootP]) {
                std::swap(rootP, rootQ);
            }
            root[rootQ] = rootP;
        };
        std::stack<int> stack;
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[i] < nums[stack.top()]) {
                connect(i, stack.top());
                stack.pop();
            }
            stack.push(find(i));
        }
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = nums[find(i)];
        }
        return result;
    }
};
