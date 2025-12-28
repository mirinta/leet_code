#include <unordered_map>

/**
 * Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.
 *
 * Implement the LRUCache class:
 *
 * - LRUCache(int capacity) initializes the LRU cache with positive size capacity.
 *
 * - int get(int key) returns the value of the key if the key exists, otherwise returns -1.
 *
 * - void put(int key, int value) updates the value of the key if the key exists. Otherwise, add the
 * key-value pair to the cache. If the number of keys exceeds the capacity from its operation, evict
 * the least recently used key.
 *
 * ! The functions get and put must each run in O(1) average time complexity.
 *
 * ! 1 <= capacity <= 3000
 * ! 0 <= key <= 10^4
 * ! 0 <= value <= 10^5
 * ! At most 2 * 10^5 calls will be made to get and put.
 */

class LRUCache {
public:
    explicit LRUCache(int capacity) : capacity(capacity) {}

    int get(int key)
    {
        if (!map.count(key))
            return -1;

        makeRecently(key);
        return cache.front().second;
    }

    void put(int key, int value)
    {
        if (map.count(key)) {
            makeRecently(key);
            cache.front().second = value;
            return;
        }
        if (cache.size() == capacity) {
            removeLeastRecently();
        }
        cache.emplace_front(key, value);
        map[key] = cache.begin();
    }

private:
    void makeRecently(int key)
    {
        if (!map.count(key))
            return;

        auto pair = *map[key];
        cache.erase(map[key]);
        cache.push_front(pair);
        map[key] = cache.begin();
    };

    void removeLeastRecently()
    {
        if (cache.empty() || map.empty())
            return;

        const int key = cache.back().first;
        cache.pop_back();
        map.erase(key);
    }

private:
    int capacity;
    // cache.front() is the recently used node
    // cache.back() is the least recently used node
    std::list<std::pair<int, int>> cache; // <key, value>
    using Iter = std::list<std::pair<int, int>>::iterator;
    std::unordered_map<int, Iter> map; // <key, Iter>
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

struct Node {
    int key;
    int val;
    Node* prev{nullptr};
    Node* next{nullptr};
    explicit Node(int key, int val) : key(key), val(val) {};
};

class DoublyLinkedList {
public:
    explicit DoublyLinkedList() : vHead(new Node(-1, -1)), vTail(new Node(-1, -1))
    {
        vHead->next = vTail;
        vTail->prev = vHead;
    };

    int size() const
    {
        return count;
    }

    void push_back(Node* node)
    {
        if (!node)
            return;

        vTail->prev->next = node;
        node->prev = vTail->prev;
        node->next = vTail;
        vTail->prev = node;
        count++;
    }

    void push_front(Node* node)
    {
        if (!node)
            return;

        vHead->next->prev = node;
        node->next = vHead->next;
        node->prev = vHead;
        vHead->next = node;
        count++;
    }

    void remove(Node* node)
    {
        if (!node)
            return;

        node->prev->next = node->next;
        node->next->prev = node->prev;
        count--;
    }

    Node* pop_back()
    {
        if (count == 0)
            return nullptr;

        auto* node = back();
        remove(node);
        return node;
    }

    Node* pop_front()
    {
        if (count == 0)
            return nullptr;

        auto* node = front();
        remove(node);
        return node;
    }

    Node* front()
    {
        if (count == 0)
            return nullptr;

        return vHead->next;
    }

    Node* back()
    {
        if (count == 0)
            return nullptr;

        return vTail->prev;
    }

private:
    int count{0};
    Node* vHead;
    Node* vTail;
};

class LRUCache2 {
public:
    explicit LRUCache2(int capacity) : capacity(capacity) {}

    int get(int key)
    {
        if (!map.count(key))
            return -1;

        makeRecently(key);
        return cache.front()->val;
    }

    void put(int key, int value)
    {
        if (map.count(key)) {
            makeRecently(key);
            cache.front()->val = value;
            return;
        }
        if (cache.size() == capacity) {
            removeLeastRecently();
        }
        cache.push_front(new Node(key, value));
        map[key] = cache.front();
    }

private:
    void makeRecently(int key)
    {
        if (!map.count(key))
            return;

        auto* node = map[key];
        cache.remove(node);
        cache.push_front(node);
    }

    void removeLeastRecently()
    {
        if (cache.size() == 0)
            return;

        const int key = cache.back()->key;
        map.erase(key);
        cache.pop_back();
    }

private:
    int capacity;
    // cache.front() is the recently used node
    // cache.back() is the least recently used node
    DoublyLinkedList cache;
    std::unordered_map<int, Node*> map; // <key, Node*>
};
