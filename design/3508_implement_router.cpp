#include <algorithm>
#include <bitset>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Design a data structure that can efficiently manage data packets in a network router. Each data
 * packet consists of the following attributes:
 *
 * - source: A unique identifier for the machine that generated the packet.
 *
 * - destination: A unique identifier for the target machine.
 *
 * - timestamp: The time at which the packet arrived at the router.
 *
 * Implement the Router class:
 *
 * Router(int memoryLimit): Initializes the Router object with a fixed memory limit.
 *
 * - memoryLimit is the maximum number of packets the router can store at any given time.
 *
 * - If adding a new packet would exceed this limit, the oldest packet must be removed to free up
 * space.
 *
 * bool addPacket(int source, int destination, int timestamp): Adds a packet with the given
 * attributes to the router.
 *
 * - A packet is considered a duplicate if another packet with the same source, destination, and
 * timestamp already exists in the router.
 *
 * - Return true if the packet is successfully added (i.e., it is not a duplicate); otherwise return
 * false.
 *
 * int[] forwardPacket(): Forwards the next packet in FIFO (First In First Out) order.
 *
 * - Remove the packet from storage.
 *
 * - Return the packet as an array [source, destination, timestamp].
 *
 * - If there are no packets to forward, return an empty array.
 *
 * int getCount(int destination, int startTime, int endTime):
 *
 * - Returns the number of packets currently stored in the router (i.e., not yet forwarded) that
 * have the specified destination and have timestamps in the inclusive range [startTime, endTime].
 *
 * Note that queries for addPacket will be made in increasing order of timestamp.
 *
 * ! 2 <= memoryLimit <= 10^5
 * ! 1 <= source, destination <= 2 * 10^5
 * ! 1 <= timestamp <= 10^9
 * ! 1 <= startTime <= endTime <= 10^9
 * ! At most 10^5 calls will be made to addPacket, forwardPacket, and getCount methods altogether.
 * ! queries for addPacket will be made in increasing order of timestamp.
 */

class Router
{
public:
    Router(int memoryLimit) : capacity(memoryLimit) {}

    bool addPacket(int source, int destination, int timestamp)
    {
        if (!set.insert(encode(source, destination, timestamp)).second)
            return false;

        if (queue.size() == capacity) {
            forwardPacket();
        }
        queue.emplace(source, destination, timestamp);
        map[destination].emplace_back(timestamp);
        return true;
    }

    std::vector<int> forwardPacket()
    {
        if (queue.empty())
            return {};

        const auto [source, destination, timestamp] = queue.front();
        queue.pop();
        set.erase(encode(source, destination, timestamp));
        map[destination].erase(
            std::lower_bound(map[destination].begin(), map[destination].end(), timestamp));
        return {source, destination, timestamp};
    }

    int getCount(int destination, int startTime, int endTime)
    {
        if (!map.count(destination))
            return 0;

        const auto lower =
            std::lower_bound(map[destination].begin(), map[destination].end(), startTime);
        const auto upper =
            std::upper_bound(map[destination].begin(), map[destination].end(), endTime);
        return upper - lower;
    }

private:
    std::bitset<66> encode(int source, int destination, int timestamp)
    {
        std::bitset<66> result{};
        result |= std::bitset<66>(source) << 48;
        result |= std::bitset<66>(destination) << 30;
        result |= std::bitset<66>(timestamp);
        return result;
    };

    std::tuple<int, int, int> decode(const std::bitset<66>& bitset)
    {
        const int source = (bitset >> 48 & std::bitset<66>((1 << 18) - 1)).to_ullong();
        const int destination = (bitset >> 30 & std::bitset<66>((1 << 18) - 1)).to_ullong();
        const int timestamp = (bitset & std::bitset<66>((1 << 30) - 1)).to_ullong();
        return {source, destination, timestamp};
    }

    std::queue<std::tuple<int, int, int>> queue;
    std::unordered_set<std::bitset<66>> set;
    std::unordered_map<int, std::vector<int>> map;
    int capacity;
};

/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */