#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

class Solution {
public:
    std::vector<double> medianSlidingWindow(std::vector<int>& nums, int k)
    {
        return approach2(nums, k);
    }

private:
    std::vector<double> approach2(const std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::multiset<long long> set(nums.begin(), nums.begin() + k);
        auto mid = std::next(set.begin(), k / 2);
        std::vector<double> result;
        result.reserve(n - k + 1);
        result.push_back(k % 2 ? *mid : 0.5 * (*mid + *std::prev(mid)));
        for (int i = k; i < n; ++i) {
            set.insert(nums[i]);
            if (nums[i] < *mid) {
                mid--;
            }
            if (nums[i - k] <= *mid) {
                mid++;
            }
            set.erase(set.lower_bound(nums[i - k])); // set.find(x) may return any element=x
            result.push_back(k % 2 ? *mid : 0.5 * (*mid + *std::prev(mid)));
        }
        return result;
    }

    std::vector<double> approach1(const std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::unordered_map<int, int> remove;
        std::priority_queue<long long> left;
        std::priority_queue<long long, std::vector<long long>, std::greater<>> right;
        for (int i = 0; i < k; ++i) {
            left.push(nums[i]);
        }
        for (int i = 0; i < k / 2; ++i) {
            right.push(left.top());
            left.pop();
        }
        std::vector<double> result(n - k + 1);
        result[0] = k % 2 ? left.top() : 0.5 * (left.top() + right.top());
        for (int i = 1; i + k - 1 < n; ++i) {
            remove[nums[i - 1]]++;
            const bool removeFromLeft = nums[i - 1] <= left.top();
            if (nums[i + k - 1] <= left.top()) {
                left.push(nums[i + k - 1]);
                if (!removeFromLeft) {
                    right.push(left.top());
                    left.pop();
                }
            } else {
                right.push(nums[i + k - 1]);
                if (removeFromLeft) {
                    left.push(right.top());
                    right.pop();
                }
            }
            while (!left.empty() && remove[left.top()] > 0) {
                remove[left.top()]--;
                left.pop();
            }
            while (!right.empty() && remove[right.top()]) {
                remove[right.top()]--;
                right.pop();
            }
            result[i] = k % 2 ? left.top() : 0.5 * (left.top() + right.top());
        }
        return result;
    }
};