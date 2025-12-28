#include <vector>

/**
 * At a lemonade stand, each lemonade costs $5. Customers are standing in a queue to buy from you
 * and order one at a time (in the order specified by bills). Each customer will only buy one
 * lemonade and pay with either a $5, $10, or $20 bill. You must provide the correct change to each
 * customer so that the net transaction is that the customer pays $5. Note that you do not have any
 * change in hand at first.
 *
 * Given an integer array bills where bills[i] is the bill the ith customer pays, return true if you
 * can provide every customer with the correct change, or false otherwise.
 *
 * ! 1 <= bills.length <= 10^5
 * ! bills[i] is either 5, 10, or 20.
 */

class Solution {
public:
    bool lemonadeChange(std::vector<int>& bills)
    {
        int fiveBills = 0;
        int tenBills = 0;
        for (const auto& val : bills) {
            if (val == 5) {
                fiveBills++;
            } else if (val == 10) {
                if (fiveBills < 1)
                    return false;

                fiveBills--;
                tenBills++;
            } else if (val == 20) {
                if (tenBills > 0 && fiveBills > 0) {
                    tenBills--;
                    fiveBills--;
                } else if (fiveBills >= 3) {
                    fiveBills -= 3;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};
