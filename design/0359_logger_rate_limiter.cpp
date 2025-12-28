#include <string>
#include <unordered_map>

/**
 * Design a logger system that receives a stream of messages along with their timestamps. Each
 * unique message should only be printed at most every 10 seconds (i.e. a message printed at
 * timestamp t will prevent other identical messages from being printed until timestamp t + 10).
 *
 * All messages will come in chronological order. Several messages may arrive at the same timestamp.
 *
 * Implement the Logger class:
 *
 * - Logger() Initializes the logger object.
 *
 * - bool shouldPrintMessage(int timestamp, string message) Returns true if the message should be
 *   printed in the given timestamp, otherwise returns false.
 *
 * ! 0 <= timestamp <= 10^9
 * ! Every timestamp will be passed in non-decreasing order (chronological order).
 * ! 1 <= message.length <= 30
 * ! At most 10^4 calls will be made to shouldPrintMessage.
 */

class Logger {
public:
    Logger() {}

    bool shouldPrintMessage(int timestamp, std::string message)
    {
        if (map.count(message) && map[message] > timestamp)
            return false;

        map[message] = timestamp + 10;
        return true;
    }

private:
    std::unordered_map<std::string, int> map;
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */
