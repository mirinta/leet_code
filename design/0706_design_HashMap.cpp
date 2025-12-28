#include <list>
#include <vector>

/**
 * Design a HashMap without using any built-in hash table libraries.
 *
 * Implement the MyHashMap class:
 *
 * - MyHashMap() initializes the object with an empty map.
 *
 * - void put(int key, int value) inserts a (key, value) pair into the HashMap. If the key already
 * exists in the map, update the corresponding value.
 *
 * - int get(int key) returns the value to which the specified key is mapped, or -1 if this map
 * contains no mapping for the key.
 *
 * - void remove(key) removes the key and its corresponding value if the map contains the mapping
 * for the key.
 *
 * ! 0 <= key, value <= 106
 * ! At most 104 calls will be made to put, get, and remove.
 */

class MyHashMap {
public:
    MyHashMap()
    {
        std::memset(&data, -1, sizeof(data));
    }

    void put(int key, int value)
    {
        data[hash(key)] = value;
    }

    int get(int key)
    {
        return data[hash(key)];
    }

    void remove(int key)
    {
        data[hash(key)] = -1;
    }

private:
    static constexpr int kSize = 1e6 + 1;

    int hash(int n)
    {
        return n % kSize;
    }

    int data[kSize];
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
