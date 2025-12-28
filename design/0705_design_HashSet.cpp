#include <vector>

/**
 * Design a HashSet without using any built-in hash table libraries.
 *
 * Implement MyHashSet class:
 *
 * - void add(key) Inserts the value key into the HashSet.
 *
 * - bool contains(key) Returns whether the value key exists in the HashSet or not.
 *
 * - void remove(key) Removes the value key in the HashSet. If key does not exist in the HashSet, do
 * nothing.
 *
 * ! 0 <= key <= 10^6
 * ! At most 10^4 calls will be made to "add", "remove", and "contains".
 */

class MyHashSet {
public:
    MyHashSet() {}

    void add(int key)
    {
        data[hash(key)] = true;
    }

    void remove(int key)
    {
        if (!contains(key))
            return;

        data[hash(key)] = false;
    }

    bool contains(int key)
    {
        return data[hash(key)];
    }

private:
    static constexpr int kSize = 1e6 + 1;

    int hash(int n)
    {
        return n % kSize;
    }

    bool data[kSize] = {false};
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */