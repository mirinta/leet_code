#include <string>
#include <unordered_map>
#include <vector>

/**
 * Design a time-based key-value data structure that can store multiple values for the same key at
 * different time stamps and retrieve the key's value at a certain timestamp.
 *
 * Implement the TimeMap class:
 *
 * - TimeMap() Initializes the object of the data structure.
 *
 * - void set(String key, String value, int timestamp) Stores the key key with the value value at
 * the given time timestamp.
 *
 * - String get(String key, int timestamp) Returns a value such that set was called previously, with
 * timestamp_prev <= timestamp. If there are multiple such values, it returns the value associated
 * with the largest timestamp_prev. If there are no values, it returns "".
 *
 * ! 1 <= key.length, value.length <= 100
 * ! key and value consist of lowercase English letters and digits.
 * ! 1 <= timestamp <= 10^7
 * ! All the timestamps timestamp of set are strictly increasing.
 * ! At most 2 * 10^5 calls will be made to set and get.
 */

class TimeMap {
public:
    TimeMap() = default;

    void set(const std::string& key, const std::string& value, int timestamp)
    {
        map[key].emplace_back(value, timestamp);
    }

    std::string get(const std::string& key, int timestamp)
    {
        if (!map.count(key))
            return {};

        const int index = find(timestamp, map[key]);
        if (index < 0)
            return {};

        return map[key][index].first;
    }

private:
    // according to the constraints: "all the timestamps are strictly increasing"
    int find(int timestamp, const std::vector<std::pair<std::string, int>>& data)
    {
        int lo = 0;
        int hi = data.size() - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (data[mid].second > timestamp) {
                hi = mid - 1;
            } else if (data[mid].second < timestamp) {
                lo = mid + 1;
            } else {
                return mid;
            }
        } // the loop is terminated when lo = hi + 1
        // lo is the insertion position, we want lo - 1 which is hi
        return hi < 0 ? -1 : hi;
    }

private:
    // key => <value, timestamp>
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> map;
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
