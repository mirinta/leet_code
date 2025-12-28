/**
 * There are numBottles water bottles that are initially full of water. You can exchange numExchange
 * empty water bottles from the market with one full water bottle.
 *
 * The operation of drinking a full water bottle turns it into an empty bottle.
 *
 * Given the two integers numBottles and numExchange, return the maximum number of water bottles you
 * can drink.
 *
 * ! 1 <= numBottles <= 100
 * ! 2 <= numExchange <= 100
 */

class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange)
    {
        int empty = numBottles;
        int drink = numBottles;
        while (empty >= numExchange) {
            const int full = empty / numExchange;
            drink += full;
            empty = empty % numExchange + full;
        }
        return drink;
    }
};