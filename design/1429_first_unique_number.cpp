#include <queue>
#include <unordered_map>
#include <vector>

/**
 * You have a queue of integers, you need to retrieve the first unique integer in the queue.
 *
 * Implement the FirstUnique class:
 *
 * - FirstUnique(int[] nums) Initializes the object with the numbers in the queue.
 *
 * - int showFirstUnique() returns the value of the first unique integer of the queue, and returns
 * -1 if there is no such integer.
 *
 * - void add(int value) insert value to the queue.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^8
 * ! 1 <= value <= 10^8
 * ! At most 50000 calls will be made to showFirstUnique and add.
 */

class FirstUnique {
public:
    FirstUnique(std::vector<int>& nums)
    {
        for (const auto& val : nums) {
            map[val]++;
        }
        for (const auto& val : nums) {
            if (map[val] == 1) {
                queue.push(val);
            }
        }
    }

    int showFirstUnique()
    {
        while (!queue.empty() && map[queue.front()] > 1) {
            queue.pop();
        }
        return queue.empty() ? -1 : queue.front();
    }

    void add(int value)
    {
        if (!map.count(value)) {
            queue.push(value);
        }
        map[value]++;
    }

private:
    std::queue<int> queue;
    std::unordered_map<int, int> map;
};

/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */
