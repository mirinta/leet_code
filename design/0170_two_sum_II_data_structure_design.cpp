#include <unordered_map>

/**
 * Design a data structure that accepts a stream of integers and checks if it has a pair of integers
 * that sum up to a particular value.
 *
 * Implement the TwoSum class:
 *
 * - TwoSum() Initializes the TwoSum object, with an empty array initially.
 *
 * - void add(int number) Adds number to the data structure.
 *
 * - boolean find(int value) Returns true if there exists any pair of numbers whose sum is equal to
 * value, otherwise, it returns false.
 *
 * ! -10^5 <= number <= 10^5
 * ! -2^31 <= value <= 2^31 - 1
 * ! At most 104 calls will be made to add and find.
 */

class TwoSum {
public:
    TwoSum() {}

    void add(int number)
    {
        map[number]++;
    }

    bool find(int value)
    {
        for (const auto& [val, freq] : map) {
            const long long target = static_cast<long long>(value) - val;
            if (target == val && map[val] > 1)
                return true;

            if (target != val && map.count(target))
                return true;
        }
        return false;
    }

private:
    std::unordered_map<long long, int> map;
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum* obj = new TwoSum();
 * obj->add(number);
 * bool param_2 = obj->find(value);
 */