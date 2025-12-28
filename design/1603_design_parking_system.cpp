#include <vector>

/**
 * Design a parking system for a parking lot. The parking lot has three kinds of parking spaces:
 * big, medium, and small, with a fixed number of slots for each size.
 *
 * Implement the ParkingSystem class:
 *
 * - ParkingSystem(int big, int medium, int small) Initializes object of the ParkingSystem class.
 * The number of slots for each parking space are given as part of the constructor.
 *
 * - bool addCar(int carType) Checks whether there is a parking space of carType for the car that
 * wants to get into the parking lot. carType can be of three kinds: big, medium, or small, which
 * are represented by 1, 2, and 3 respectively. A car can only park in a parking space of its
 * carType. If there is no space available, return false, else park the car in that size space and
 * return true.
 *
 * ! 0 <= big, medium, small <= 1000
 * ! carType is 1, 2, or 3
 * ! At most 1000 calls will be made to addCar
 */

class ParkingSystem {
public:
    ParkingSystem(int big, int medium, int small) : m_spaces({big, medium, small}) {}

    // 1 for big, 2 for medium, 3 for small
    bool addCar(int carType)
    {
        if (carType < 1 || carType > m_spaces.size())
            return false;

        if (m_spaces[carType - 1] == 0)
            return false;

        m_spaces[carType - 1]--;
        return true;
    }

private:
    std::vector<int> m_spaces;
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */