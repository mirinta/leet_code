#include <algorithm>

/**
 * Given two numbers, hour and minutes, return the smaller angle (in degrees) formed between the hour and the minute
 * hand.
 *
 * Answers within 10^-5 of the actual value will be accepted as correct.
 *
 * ! 1 <= hour <= 12
 * ! 0 <= minutes <= 59
 */

class Solution {
public:
    double angleClock(int hour, int minutes)
    {
        // minute hand: 6 degrees per minute
        // hour hand: 30 degrees per hour
        const double minuteAngle = minutes * 6;
        const double hourAngle = (hour % 12 + minutes / 60.0) * 30;
        const double diff = std::abs(minuteAngle - hourAngle);
        return std::min(diff, 360.0 - diff);
    }
};