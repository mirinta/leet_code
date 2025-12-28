#include <cmath>
#include <vector>

/**
 * You are given a floating-point number hour, representing the amount of time you have to reach the
 * office. To commute to the office, you must take n trains in sequential order. You are also given
 * an integer array dist of length n, where dist[i] describes the distance (in kilometers) of the
 * ith train ride.
 *
 * Each train can only depart at an integer hour, so you may need to wait in between each train
 * ride.
 *
 * - For example, if the 1st train ride takes 1.5 hours, you must wait for an additional 0.5 hours
 * before you can depart on the 2nd train ride at the 2 hour mark.
 *
 * Return the minimum positive integer speed (in kilometers per hour) that all the trains must
 * travel at for you to reach the office on time, or -1 if it is impossible to be on time.
 *
 * Tests are generated such that the answer will not exceed 107 and hour will have at most two
 * digits after the decimal point.
 *
 * ! n == dist.length
 * ! 1 <= n <= 10^5
 * ! 1 <= dist[i] <= 10^5
 * ! 1 <= hour <= 10^9
 * ! There will be at most two digits after the decimal point in hour.
 */

class Solution {
public:
    int minSpeedOnTime(std::vector<int>& dist, double hour)
    {
        const int maxSpeed = getMaxSpeed(dist, hour);
        if (maxSpeed == -1)
            return -1;

        int min = 1;
        int max = maxSpeed;
        while (min < max) {
            const int speed = min + (max - min) / 2;
            if (isValid(speed, dist, hour)) {
                max = speed;
            } else {
                min = speed + 1;
            }
        }
        return min;
    }

private:
    int getMaxSpeed(const std::vector<int>& dist, double hour)
    {
        if (dist.empty() || dist.size() - 1 >= hour)
            return -1;

        int maxSpeed = std::ceil(dist.back() * 1.0 / (hour - dist.size() + 1));
        for (const auto& val : dist) {
            maxSpeed = std::max(maxSpeed, val);
        }
        return maxSpeed;
    }

    bool isValid(int speed, const std::vector<int>& dist, double hour)
    {
        double total = 0;
        for (int i = 0; i < dist.size(); ++i) {
            const double time = dist[i] * 1.0 / speed;
            total += i < dist.size() - 1 ? std::ceil(time) : time;
            if (total > hour)
                return false;
        }
        return true;
    }
};