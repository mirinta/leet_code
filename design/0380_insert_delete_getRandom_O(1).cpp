#include <random>
#include <unordered_map>
#include <vector>

/**
 * Implement the "RandomizedSet" class:
 *
 * - "RandomizedSet()" initializes the "RandomizedSet" object.
 *
 * - "bool insert(int val)" inserts an item "val" into the set if not present. Returns "true" if the
 * item was not present, "false" otherwise.
 *
 * - "bool remove(int val)" removes an item "val" from the set if present. Returns "true" if the
 * item was present, "false" otherwise.
 *
 * - "int getRandom()" returns a random element from the current set of elements (it's guaranteed
 * that at least one element exists when this method is called). Each element must have the same
 * probability of being returned.
 *
 * You must implement the functions of the class such that each function works in average O(1) time
 * complexity.
 *
 * ! -2^31 <= val <= 2^31 - 1
 * ! At most 2 * 10^5 calls will be made to insert, remove, and getRandom.
 * ! There will be at least one element in the data structure when getRandom is called.
 */

class RandomizedSet {
public:
    RandomizedSet() : gen(rd()) {}

    bool insert(int val)
    {
        if (map.count(val))
            return false;

        map[val] = data.size();
        data.push_back(val);
        return true;
    }

    bool remove(int val)
    {
        if (!map.count(val))
            return false;

        const int index = map[val];
        map[data.back()] = index;
        map.erase(val);
        std::swap(data.back(), data[index]);
        data.pop_back();
        return true;
    }

    int getRandom()
    {
        std::uniform_int_distribution<> distrib(0, data.size() - 1);
        return data[distrib(gen)];
    }

private:
    std::random_device rd;
    std::mt19937 gen;
    std::vector<int> data;
    std::unordered_map<int, int> map; // value to index
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */