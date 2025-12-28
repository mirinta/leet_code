#include <list>
#include <unordered_map>

/**
 * Design and implement a data structure for a Least Frequently Used cache.
 *
 * Implement the LFUCache class:
 *
 * - LFUCache(int capacity) initializes the object with the "capacity" of the data structure.
 *
 * - int get(int key) gets the value of the "key" if the "key" exists in the cache. Otherwise,
 * returns -1.
 *
 * - void put(int key, int value) updates the value of the "key" if present, or inserts the "key" if
 * not already present. When the cache reaches its "capacity", it should invalidate and remove the
 * least frequently used key before inserting a new item. For this problem, when there is a tie
 * (i.e., two or more keys with the same frequently), the least recently used "key" should be
 * invalidated.
 *
 * - To determine the least frequently used key, a use counter is maintained for each key in the
 * cache. The key with the smallest use counter is the least frequently used the key.
 *
 * When a key is first inserted into the cache, its use counter is set to 1 (due to the put
 * operation). The use counter for a key in the cache is incremented either a get or put operation
 * is called on it.
 *
 * The function get and put must each run in O(1) average time complexity.
 */

class LFUCache {
public:
    explicit LFUCache(int capacity) : m_capacity(capacity) {}

    int get(int key)
    {
        if (!m_keyToValAndFreq.count(key))
            return -1;

        increaseFreq(key);
        return m_keyToValAndFreq[key].first;
    }

    void put(int key, int value)
    {
        // if the key exists, update its value and increase its frequency
        if (m_keyToValAndFreq.count(key)) {
            increaseFreq(key);
            m_keyToValAndFreq[key].first = value;
            return;
        }
        // if the capacity is reached, remove the LFU key, or the LRU key if there are multiple LFU
        // keys
        if (m_keyToValAndFreq.size() == m_capacity) {
            removeLFUKey();
        }
        // insert a new key-value pair and set its frequency to 1
        m_keyToValAndFreq[key] = {value, 1};
        // update list of freq = 1, add the key at its back
        if (!m_freqToKeys.count(1)) {
            m_freqToKeys[1] = std::list<int>{};
        }
        m_freqToKeys[1].push_back(key);
        m_keyToIter[key] = --m_freqToKeys[1].end();
        // set the minFreq to 1
        m_minFreq = 1;
    }

private:
    void increaseFreq(int key)
    {
        auto& freq = m_keyToValAndFreq[key].second;
        // update current freq's list, remove it if it is empty
        m_freqToKeys[freq].erase(m_keyToIter[key]);
        if (m_freqToKeys[freq].empty()) {
            m_freqToKeys.erase(freq);
            // if the list is not empty, we must not update the minFreq,
            // because there exists key(s) with the same frequency,
            // the minFreq is used for those keys
            if (freq == m_minFreq) {
                m_minFreq++;
            }
        }
        // increase frequency
        freq += 1;
        // update new frequency's list
        if (!m_freqToKeys.count(freq)) {
            m_freqToKeys[freq] = std::list<int>{};
        }
        m_freqToKeys[freq].push_back(key);
        m_keyToIter[key] = --m_freqToKeys[freq].end();
    }

    void removeLFUKey()
    {
        // we have a list of keys with the same minFreq,
        // the LRU key is at the front, remove it
        auto& lruList = m_freqToKeys[m_minFreq];
        const auto key = lruList.front();
        lruList.erase(m_keyToIter[key]);
        // remove the list if it is empty
        if (lruList.empty()) {
            m_freqToKeys.erase(m_minFreq);
        }
        m_keyToValAndFreq.erase(key);
        m_keyToIter.erase(key);
    }

private:
    int m_capacity;
    int m_minFreq{0};
    std::unordered_map<int, std::pair<int, int>> m_keyToValAndFreq; // key = <val, freq>
    std::unordered_map<int, std::list<int>> m_freqToKeys;           // the LRU key is at the front
    // to remove any element in std::list in O(1) time complexity,
    // we store each element's iterator and use std::list::erase() instead of std::list::remove()
    std::unordered_map<int, std::list<int>::iterator> m_keyToIter; // iter to in m_freqToKeys[freq]
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
