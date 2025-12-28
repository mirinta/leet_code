#include <string>
#include <unordered_map>
#include <unordered_set>

/**
 * Design a data structure to store the strings' count with the ability to return the strings with
 * minimum and maximum counts.
 *
 * Implement the AllOne class:
 *
 * - AllOne() Initializes the object of the data structure.
 *
 * - inc(String key) Increments the count of the string key by 1. If key does not exist in the data
 * structure, insert it with count 1.
 *
 * - dec(String key) Decrements the count of the string key by 1. If the count of key is 0 after the
 * decrement, remove it from the data structure. It is guaranteed that key exists in the data
 * structure before the decrement.
 *
 * - getMaxKey() Returns one of the keys with the maximal count. If no element exists, return an
 * empty string "".
 *
 * - getMinKey() Returns one of the keys with the minimum count. If no element exists, return an
 * empty string "".
 *
 * Note that each function must run in O(1) average time complexity.
 *
 * ! 1 <= key.length <= 10
 * ! key consists of lowercase English letters.
 * ! It is guaranteed that for each call to dec, key is existing in the data structure.
 * ! At most 5 * 10^4 calls will be made to inc, dec, getMaxKey, and getMinKey.
 */

class AllOne {
public:
    AllOne() : head(new Node(0)), tail(new Node(0))
    {
        head->next = tail;
        tail->prev = head;
    }

    void inc(std::string key)
    {
        if (map.count(key)) {
            auto* node = map[key];
            node->keys.erase(key);
            auto* next = node->next;
            if (next == tail || next->count != node->count + 1) {
                auto* newNode = new Node(node->count + 1);
                newNode->keys.insert(key);
                newNode->prev = node;
                newNode->next = next;
                node->next = newNode;
                next->prev = newNode;
                map[key] = newNode;
            } else {
                next->keys.insert(key);
                map[key] = next;
            }
            if (node->keys.empty()) {
                deleteNode(node);
            }
        } else {
            auto* first = head->next;
            if (first == tail || first->count > 1) {
                auto* newNode = new Node(1);
                newNode->keys.insert(key);
                newNode->prev = head;
                newNode->next = first;
                head->next = newNode;
                first->prev = newNode;
                map[key] = newNode;
            } else {
                first->keys.insert(key);
                map[key] = first;
            }
        }
    }

    void dec(std::string key)
    {
        if (!map.count(key))
            return;

        auto* node = map[key];
        node->keys.erase(key);
        if (node->count == 1) {
            map.erase(key);
        } else {
            auto* prev = node->prev;
            if (prev == head || prev->count != node->count - 1) {
                auto* newNode = new Node(node->count - 1);
                newNode->keys.insert(key);
                newNode->prev = prev;
                newNode->next = node;
                prev->next = newNode;
                node->prev = newNode;
                map[key] = newNode;
            } else {
                prev->keys.insert(key);
                map[key] = prev;
            }
        }
        if (node->keys.empty()) {
            deleteNode(node);
        }
    }

    std::string getMaxKey()
    {
        if (tail->prev == head)
            return {};

        return *(tail->prev->keys.begin());
    }

    std::string getMinKey()
    {
        if (head->next == tail)
            return {};

        return *(head->next->keys.begin());
    }

private:
    struct Node {
        int count{0};
        Node* prev;
        Node* next;
        std::unordered_set<std::string> keys;

        explicit Node(int count) : count(count) {}
    };

    void deleteNode(Node* node)
    {
        auto* prev = node->prev;
        auto* next = node->next;
        prev->next = next;
        next->prev = prev;
        delete node;
    }

    Node* head;
    Node* tail;
    std::unordered_map<std::string, Node*> map;
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */