#include <algorithm>
#include <vector>

/**
 * You are given an integer mass, which represents the original mass of a planet. You are further given an integer array
 * asteroids, where asteroids[i] is the mass of the ith asteroid.
 *
 * You can arrange for the planet to collide with the asteroids in any arbitrary order. If the mass of the planet is
 * greater than or equal to the mass of the asteroid, the asteroid, is destroyed and the planet gains the mass of the
 * asteroid. Otherwise, the planet is destroyed.
 *
 * Return true if all asteroids can be destroyed. Otherwise, return false.
 *
 * ! 1 <= mass <= 10^5
 * ! 1 <= asteroids.length <= 10^5
 * ! 1 <= asteroids[i] <= 10^5
 */

class Solution {
public:
    bool asteroidsDestroyed(int mass, std::vector<int>& asteroids)
    {
        std::sort(asteroids.begin(), asteroids.end());
        long long planet = mass;
        for (const auto& val : asteroids) {
            if (planet < val)
                return false;

            planet += val;
        }
        return true;
    }
};
